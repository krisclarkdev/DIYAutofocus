# DIY Autofocus System for Cine Lenses 🎥🔧  

## 📜 Overview  
This project is a **DIY autofocus system** using a **NEMA 17 stepper motor, TMC2209 stepper driver, VL53L1X ToF sensor, and Arduino (or ESP32)**.  
It automatically adjusts the focus of a cine lens based on the **distance to the subject**, providing smooth and accurate focus control.

Note: I haven't even built this thing to begin to test it, just getting my thoughts down to build and test later

---

## 🔩 Hardware Requirements  
### **📦 Required Components**
| Component | Description |
|-----------|-------------|
| **Arduino Nano Every / ESP32** | Main controller |
| **TMC2209 Stepper Driver** | Controls the NEMA 17 motor |
| **NEMA 17 Stepper Motor** | Moves the focus ring |
| **VL53L1X Time-of-Flight Sensor** | Measures subject distance |
| **MOSFET (IRLZ34N or IRF520)** | Controls motor power |
| **10kΩ Resistor** | Pull-down resistor for MOSFET |
| **4.7kΩ Resistors (x2)** | I2C pull-ups for VL53L1X |
| **100µF Capacitor** | Stabilizes TMC2209 logic voltage |
| **470µF Capacitor** | Prevents power fluctuations |
| **Schottky Diode (1N5819)** | Protects against back-EMF |

---

## 🛠 Wiring Guide  

### **✅ TMC2209 to Arduino**
| **TMC2209 Pin** | **Arduino Pin** |
|---------------|--------------|
| **VCC** | **5V** |
| **GND** | **GND** |
| **DIR** | **D5** |
| **STEP** | **D6** |
| **EN (Enable)** | **GND** |
| **M1A** | **NEMA 17 Red Wire** |
| **M1B** | **NEMA 17 Blue Wire** |
| **M2A** | **NEMA 17 Green Wire** |
| **M2B** | **NEMA 17 Black Wire** |
| **V_Motor** | **12V via MOSFET Drain** |

### **✅ MOSFET Connections (IRLZ34N)**
| **MOSFET Pin** | **Connect To** |
|--------------|----------------|
| **Gate (G)** | **Arduino D9 (PWM Control)** |
| **Drain (D)** | **TMC2209 V_Motor (12V Input)** |
| **Source (S)** | **12V Power Supply GND** |

### **✅ VL53L1X (I2C) with Level Shifters**
| **VL53L1X Pin** | **Arduino Pin** | **Additional Components** |
|--------------|--------------|----------------|
| **VCC** | **5V** | Power supply |
| **GND** | **GND** | Common ground |
| **SDA** | **Low Side of MOSFET 1** | Level-shifted |
| **SCL** | **Low Side of MOSFET 2** | Level-shifted |

### **✅ Stability Components**
| **Component** | **Connection** | **Purpose** |
|--------------|----------------|-------------|
| **10kΩ Resistor** | **MOSFET Gate → GND** | Prevents floating MOSFET Gate |
| **Schottky Diode (1N5819)** | **12V (V_Motor) → GND** | Prevents back-EMF damage |
| **100µF Capacitor** | **TMC2209 VCC → GND** | Stabilizes logic power |
| **470µF Capacitor** | **12V Power → GND** | Smooths power fluctuations |

---

## ⚙️ Installation & Setup  
### **1️⃣ Clone the Repository**
```sh
git clone https://github.com/YOUR_USERNAME/DIY-Autofocus-System.git
cd DIY-Autofocus-System
```

### **2️⃣ Install Dependencies**
Install the required **Arduino libraries**:
```sh
pip install pyserial
```
Or in Arduino IDE, install:
- `VL53L1X`
- `AccelStepper`

---

## 🚀 Usage  

### **✅ Upload the Code**
1. Open `autofocus.ino` in Arduino IDE.  
2. Select the correct **board and port**.  
3. Click **Upload**.

### **✅ Adjusting Autofocus Range**
Modify the following lines in `autofocus.ino`:
```cpp
#define NEAR_DISTANCE 300  // mm (Closest focus)
#define FAR_DISTANCE 2000  // mm (Farthest focus)
#define FOCUS_STEPS 400  // Motor steps per full focus travel
```
- Adjust `NEAR_DISTANCE` and `FAR_DISTANCE` to match your lens.
- `FOCUS_STEPS` defines the number of steps for a **full focus range**.

---

## 🔧 Troubleshooting  
### **❌ Stepper Motor Not Moving?**
1. Check **TMC2209 wiring** (V_Motor should get 12V).  
2. Ensure **MOSFET is switching power properly**.  
3. Try reversing **M1A/M1B or M2A/M2B wires** (some motors need swapping).  

### **❌ VL53L1X Not Detecting Distance?**
1. Confirm **SDA/SCL connections** with MOSFET level shifters.  
2. Use an **I2C scanner** script to detect the sensor.  
3. Make sure **pull-up resistors (4.7kΩ) are properly wired**.  

---

## 🛠 Future Improvements  
✅ Add a **manual focus override** using a rotary encoder  
✅ Implement **PID-based focus tracking**  
✅ Optimize **motor speed for different lenses**  

---

## 🤝 Contributing  
Pull requests are welcome! If you have improvements, feel free to fork the repo and submit a PR.

---

## 📜 License  
This project is licensed under **MIT License**.

---

🔥 **Enjoy smooth autofocus control for your cine lenses!** 🎥🚀
