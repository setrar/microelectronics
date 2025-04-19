# Digital Buble Level

## TTL

The **SN74HC595N** is a classic **8-bit serial-in, parallel-out shift register** from the 74HCxx logic family (High-speed CMOS, TTL-compatible). It’s extremely popular in electronics for expanding output pins — especially in microcontroller and FPGA projects.

---

### **Quick Summary:**

| Feature           | Description                          |
|------------------|--------------------------------------|
| Function          | 8-bit shift register with storage latch |
| Family            | 74HC — High-Speed CMOS               |
| Package           | DIP-16 (for the `N` variant)         |
| Logic Level       | 2V–6V operation (TTL-compatible)     |
| Max Clock         | ~100+ MHz (at 5V)                    |
| Common Use        | Driving LEDs, 7-segments, relays    |

---

### **Pinout (Top View):**

```
      +---+--+---+
  Q1  |1      16| Vcc
  Q2  |2      15| Q0
  Q3  |3      14| SER (Serial Input)
  Q4  |4      13| OE̅ (Output Enable)
  Q5  |5      12| RCLK (Latch Clock)
  Q6  |6      11| SRCLK (Shift Clock)
  Q7  |7      10| SRCLR̅ (Shift Register Clear)
 GND |8       9| Q7' (Cascade Output)
      +--------+
```

---

### **How It Works:**

1. **Shift Clock (SRCLK)**:
   - On rising edge, data from `SER` is shifted into the internal register
2. **Latch Clock (RCLK)**:
   - On rising edge, the register's contents are copied to the output latches
3. **Output Enable (OE̅)**:
   - Active LOW. Drives outputs when LOW
4. **Cascade (Q7')**:
   - Used to chain multiple 595s together for more outputs

---

### **Typical Use Case:**

You can control **8 outputs** using just **3 pins** (SER, SRCLK, RCLK) from a microcontroller or FPGA.

#### Example: Driving 8 LEDs
```plaintext
[MCU] ---SER---> 595
      ---SRCLK--> 595
      ---RCLK---> 595
```
- Shift in 8 bits serially
- Toggle latch to output
- Repeat as needed

You can **daisy-chain** multiple chips to drive **16, 24, 32...** outputs.

---

### **Use Cases:**
- LED matrix drivers
- 7-segment displays
- Multiplexed data buses
- Relay banks
- Expanding I/O for Arduino, Raspberry Pi, FPGAs

## Application

<img src=images/IMG_0555.png width='' height='' > </img>

|||
|-|-|
| | <img src=images/Scope_X-Backward.png width='' height='' > </img> |
| | <img src=images/Scope_X-Center.png width='' height='' > </img> |
| | <img src=images/Scope_X-Forward.png width='' height='' > </img> |
| | <img src=images/Scope_Y-Backward.png width='' height='' > </img> |
| | <img src=images/Scope_Y-Forward.png width='' height='' > </img> |

```python
import machine
from machine import I2C, Pin
import time
import math
from imu import MPU6050


### mpu6050
i2c = I2C(1, sda=Pin(6), scl=Pin(7), freq=400000)
mpu = MPU6050(i2c)

# get rotary angle
def dist(a,b):
    return math.sqrt((a*a)+(b*b))

def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)

def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)

def get_angle():
    y_angle=get_y_rotation(mpu.accel.x, mpu.accel.y, mpu.accel.z)
    x_angle=get_x_rotation(mpu.accel.x, mpu.accel.y, mpu.accel.z)
    return x_angle,y_angle

### led matrix display
sdi = machine.Pin(18,machine.Pin.OUT)
rclk = machine.Pin(19,machine.Pin.OUT)
srclk = machine.Pin(20,machine.Pin.OUT)

def hc595_in(dat):
    for bit in range(7,-1, -1):
        srclk.low()
        time.sleep_us(30)
        sdi.value(1 & (dat >> bit))
        time.sleep_us(30)
        srclk.high()

def hc595_out():
    rclk.high()
    time.sleep_us(200)
    rclk.low()

def display(glyph):
    for i in range(0,8):
        hc595_in(glyph[i])
        hc595_in(0x80>>i)
        hc595_out()

# data transformation
def matrix_2_glyph(matrix):
    glyph= [0 for i in range(8)] # glyph code for display()
    for i in range(8):
        for j in range(8):
            glyph[i]+=matrix[i][j]<<j
    return glyph

def clamp_number(val, min, max):
    return min if val < min else max if val > max else val

def interval_mapping(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# Calculate the position of the bubble
sensitivity=4          # The higher the number, the more sensitive
matrix_range=7         # The size of the matrix is 8, so the coordinate range is 0~7
point_range=matrix_range-1     # The x, y value of the bubble's marker point (upper left point) should be between 0-6
def bubble_position():
    x,y=get_angle()
    x=int(clamp_number(interval_mapping(x,-90,90,0-sensitivity,point_range+sensitivity),0,point_range))
    y=int(clamp_number(interval_mapping(y,-90,90,point_range+sensitivity,0-sensitivity),0,point_range))
    return [x,y]

# Drop the bubble into empty matrix
def drop_bubble(matrix,bubble):
    matrix[bubble[0]][bubble[1]]=0
    matrix[bubble[0]+1][bubble[1]]=0
    matrix[bubble[0]][bubble[1]+1]=0
    matrix[bubble[0]+1][bubble[1]+1]=0
    return matrix

while True:
    matrix= [[1 for i in range(8)] for j in range(8)]  # empty matrix
    bubble=bubble_position() # bubble coordinate
    matrix=drop_bubble(matrix,bubble) # drop the bubble into empty matrix
    display(matrix_2_glyph(matrix)) # show matrix
```

# References

- [ ] [7.12 Digital Bubble Level](https://docs.sunfounder.com/projects/euler-kit/en/latest/pyproject/py_digital_bubble_level.html)
