import serial
import serial.tools.list_ports
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
import threading
import sys
import time


PORT       = ""         
BAUD       = 115200
MAX_POINTS = 200
SETPOINT   = 300


speed_data  = deque([0.0] * MAX_POINTS, maxlen=MAX_POINTS)
error_data  = deque([0.0] * MAX_POINTS, maxlen=MAX_POINTS)
output_data = deque([0.0] * MAX_POINTS, maxlen=MAX_POINTS)
lock = threading.Lock()
ser  = None

def find_port():
    ports = list(serial.tools.list_ports.comports())
    if not ports:
        print("No serial ports found.")
        sys.exit(1)
    if len(ports) == 1:
        print(f"Auto-detected port: {ports[0].device}")
        return ports[0].device
    print("Available ports:")
    for i, p in enumerate(ports):
        print(f"  [{i}] {p.device}  —  {p.description}")
    idx = int(input("Select port number: "))
    return ports[idx].device

def serial_reader():
    global ser
    port = PORT if PORT else find_port()  
    try:
        ser = serial.Serial(port, BAUD, timeout=1)
    except serial.SerialException as e:
        print(f"Failed to open port: {e}")
        sys.exit(1)

    print(f"Connected to {port} @ {BAUD} baud")
    print('Waiting for data...  (expected: "RPM: x, SP: y, OUT: z")')

    while True:
        try:
            raw = ser.readline()
            if not raw:
                continue
            line = raw.decode("utf-8", errors="ignore").strip()
            if not line:
                continue
            print(line)   

            
            parts = [p.strip() for p in line.split(",")]   
            if len(parts) != 3:
                continue

            rpm_part, sp_part, out_part = parts
            if not (rpm_part.upper().startswith("RPM") and
                    sp_part.upper().startswith("SP") and
                    out_part.upper().startswith("OUT")):
                continue   

            spd = float(rpm_part.split(":")[1].strip())
            sp  = float(sp_part.split(":")[1].strip())
            out = float(out_part.split(":")[1].strip())
            err = sp - spd

            with lock:
                speed_data.append(spd)
                error_data.append(err)
                output_data.append(out)

        except (ValueError, UnicodeDecodeError):
            continue
        except serial.SerialException as e:
            print(f"Serial error: {e}")
            break


fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 7), sharex=True)
fig.patch.set_facecolor("#1e1e2e")
for ax in (ax1, ax2, ax3):
    ax.set_facecolor("#1e1e2e")
    ax.tick_params(colors="#cdd6f4")
    for spine in ax.spines.values():
        spine.set_color("#45475a")

line1, = ax1.plot([], [], color="#89b4fa", linewidth=1.5, label="RPM")
ax1.axhline(SETPOINT, color="#a6e3a1", linewidth=1.0, linestyle="--", label=f"setpoint ({int(SETPOINT)})")
ax1.set_ylabel("RPM", color="#cdd6f4")
ax1.legend(loc="lower right", facecolor="#313244", labelcolor="#cdd6f4", fontsize=9)
ax1.set_title("Speed (RPM)", color="#cdd6f4", fontsize=10)

line2, = ax2.plot([], [], color="#fab387", linewidth=1.5, label="error")
ax2.axhline(0, color="#585b70", linewidth=0.8, linestyle="--")
ax2.set_ylabel("error", color="#cdd6f4")
ax2.legend(loc="lower right", facecolor="#313244", labelcolor="#cdd6f4", fontsize=9)
ax2.set_title("Error  (setpoint − RPM)", color="#cdd6f4", fontsize=10)

line3, = ax3.plot([], [], color="#cba6f7", linewidth=1.5, label="output")
ax3.set_ylabel("PWM CCR1", color="#cdd6f4")
ax3.set_xlabel("samples", color="#cdd6f4")
ax3.legend(loc="lower right", facecolor="#313244", labelcolor="#cdd6f4", fontsize=9)
ax3.set_title("PID Output (PWM duty)", color="#cdd6f4", fontsize=10)

fig.suptitle("PID Live Monitor", color="#cdd6f4", fontsize=13, fontweight="bold")
fig.tight_layout(rect=[0, 0, 1, 0.96])

def animate(_frame):
    with lock:
        s = list(speed_data)
        e = list(error_data)
        o = list(output_data)
    x = list(range(len(s)))
    line1.set_data(x, s)
    line2.set_data(x, e)
    line3.set_data(x, o)

    for ax, data, include_sp in ((ax1, s, True), (ax2, e, False), (ax3, o, False)):
        ax.set_xlim(0, MAX_POINTS)
        lo, hi = min(data), max(data)
        if include_sp:
            lo = min(lo, SETPOINT)
            hi = max(hi, SETPOINT)
        pad = max(abs(hi - lo) * 0.15, 10)
        ax.set_ylim(lo - pad, hi + pad)

    fig.canvas.draw_idle()   
    return line1, line2, line3

if __name__ == "__main__":
    t = threading.Thread(target=serial_reader, daemon=True)
    t.start()
    time.sleep(0.5)
    ani = animation.FuncAnimation(fig, animate, interval=100,
                                  blit=False, cache_frame_data=False)
    plt.show()
    if ser and ser.is_open:
        ser.close()