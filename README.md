# 🧼 Microcontroller-Based Automated Hand Sanitation Dispenser with IoT Monitoring  
> A Smart Contactless Sanitation System 

![Arduino](https://img.shields.io/badge/built%20with-Arduino-00979D?style=flat-square&logo=arduino)
![ESP32](https://img.shields.io/badge/microcontroller-ESP32-blue?style=flat-square)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)
![IoT Cloud](https://img.shields.io/badge/cloud-Arduino_Cloud-orange?style=flat-square&logo=cloudflare)
![Status](https://img.shields.io/badge/status-working-success?style=flat-square)
![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen?style=flat-square&logo=github)
![Arduino IDE](https://img.shields.io/badge/Software-Arduino_IDE-00979D?style=flat-square&logo=arduino)
![Arduino Cloud](https://img.shields.io/badge/Platform-Arduino_Cloud-orange?style=flat-square&logo=cloudflare)

---

## 📌 Project Overview

This project presents a **microcontroller-based, contactless alcohol dispenser** enhanced with a **real-time IoT monitoring system** to track alcohol levels, send email alerts, and log usage history. It’s designed for **public safety and operational efficiency** in educational institutions 

---

## 🎯 Specific Objectives

- Automate hand sanitation using **IR and ultrasonic sensors**.
- Display live system and alcohol status via **TFT LCD**.
- Track usage data over 1, 3, 7, and 15-day intervals via **Arduino IoT Cloud**.
- Indicate alcohol level with **RGB LED (Full, Medium, Low)**.
- Send **refill alerts via email** when the alcohol level falls below 20%.
- Detect tampering and activate buzzer through **vibration sensor security**.

---

## ⚠️ Limitations

- 💧 **Manual refill only** – no automatic refill system.
- ⚡ **Requires continuous power** to operate.
- 🌍 Currently scoped to **Emilio Aguinaldo College – Manila Building 7**.
- 📧 Notification method is **email only**.
- 📱 Works with **ESP32 DevKitC only**, not Uno/Nano.

---

## 🧠 Hardware & Software Concept

### 🧩 Hardware Components

| Component                            | Purpose                                 |
| ------------------------------------ | --------------------------------------- |
| ESP32 DevKitC                        | Core microcontroller (Wi-Fi + Cloud)    |
| IR Obstacle Sensor                   | Detects hand presence                   |
| Ultrasonic Distance Sensor (HC-SR04) | Monitors alcohol level                  |
| Automatic Gearbox Dispenser          | Dispenses alcohol                       |
| SW-420 Vibration Sensor              | Detects tampering or movement           |
| Active Buzzer                        | Alerts when tampering is detected       |
| KY-016 RGB LED                       | Shows alcohol level (Full, Medium, Low) |
| TFT 4-inch SPI Display               | Displays system and alcohol status      |
| Multi-Voltage Level Converter        | Ensures 3.3V/5V logic compatibility     |
| ESP32 38-pin Expansion Board         | Organizes all GPIO connections          |

### 💻 Software Stack

- **Arduino IDE** – for local sketch development
- **Arduino Cloud** – real-time monitoring & dashboard
- **Arduino Cloud Agent** – sync between local IDE and IoT dashboard
- `thingsProperties.h` – maps variables from IoT Cloud
- `arduino_secrets.h` – stores Wi-Fi + IoT credentials

---
## 🧪 Methodology
<details>
<summary> <strong>Prototyping Model</strong></summary>

<img width="663" height="348" alt="image" src="https://github.com/user-attachments/assets/7645804c-3381-4496-9482-5ab733e2d734" />

<div align="justify">
The Prototyping Model is an iterative system development process that emphasizes ongoing improvement through feedback from the users. The model deviates from the linear methods, which instead enable an early development of a working prototype that is tested and refined according to user interactions. This method ensures the eventual delivery of a system that meets the users' requirements and reduces the risks and expense of changes in subsequent stages. The Prototyping Model has six main stages: Planning, Analysis, Design, System Prototype, Implementation, and System Maintenance
</div>

</details>

---

## 🔌 System Architecture

<details>
<summary> <strong> 🧱 Block Diagram</strong></summary>

<img width="891" height="712" alt="image" src="https://github.com/user-attachments/assets/beca3e5e-c001-4b08-b45e-41e213e392ad" />

<div align="justify">
As indicated from the block diagram, it is centered on the ESP32 microcontroller, which acts as the central unit controlling all the modules. The system is powered by a dedicated power supply that will run continuously. The contactless sanitizing module identifies and releases alcohol to sanitize hands without direct contact. The front-end information module, through the LCD display, shows real-time alcohol levels and system status to users. On the other hand, the back-end monitoring module tracks the system’s operational data—specifically alcohol levels—and uses Internet of Things (IoT) to send this information to the cloud via Arduino Cloud; the backend also displays usage data on a chart, showcasing how many times the sensor has detected an object—i.e., how many times it has dispensed sanitizer—over selectable timeframes such as 1 day, 3 days, 7 days, and 15 days. An LED indicator system provides a visual representation of the alcohol level status: a green LED lights up when the tank is full, yellow when it's at a medium level, and red when the level is critically low. This color-coded indication allows users and maintenance staff to easily identify the alcohol status at a glance and take timely action. The system also features a security module, which provides secure access and anti-tampering capability; the module detects physical enclosure integrity using sensors and can trigger alarms or remotely lock the system in case of unauthorized activity, thereby providing the reliability and security of the device.
</div>

</details>

<details>
<summary> <strong>🔁 IPO Diagram</strong></summary>

<img width="868" height="601" alt="image" src="https://github.com/user-attachments/assets/3e46026c-f7c0-4197-8ea4-7853b76f3fc4" />

<div align="justify">
The IPO (Input-Process-Output) model depicts the functional process of the automatic hand sanitizing system. Sensor activation and power supply, and presence of user, are initiators of the system in the Input stage. The system moves to the process stage upon activation of the sensor by the user, initiating the hand sanitizing using an alcohol dispenser. Simultaneously, the system sends operational information updates such as alcohol levels and system status to the Arduino Cloud via IoT for remote access and monitoring; the backend also displays usage data on a chart, showcasing how many times the sensor has detected an object—i.e., how many times it has dispensed sanitizer—over selectable timeframes such as 1 day, 3 days, 7 days, and 15 days. Finally, the Output stage shows real-time data on the LCD indicating current alcohol levels and system operation as well as cleaned hands to the user, thus offering both user hygiene and maintenance. An LED indicator is also included in the output, showing red, yellow, or green lights to visually represent low, medium, and full alcohol levels respectively.   
</div>

</details>

---

## 🏗️ Project Design

<details>
<summary> <strong> Solid and Cutaway View</strong></summary>
  
![Solid View](https://github.com/user-attachments/assets/ab7a522c-b4eb-43ab-8e9a-fcf26ae7afde)

*Solid View*

![Cutaway View](https://github.com/user-attachments/assets/97c08330-ea99-41b0-95c5-8f88b0f37acc)

*Cutaway View*

<div align="justify">
The model showcases the design of the microcontroller-based automatic hand sanitation dispenser that is compact and efficient for Emilio Aguinaldo College - Manila Building 7. The system incorporates major components such as an ESP32 microcontroller for IoT an IR sensor for automatic hand detection, a water pump for regulated alcohol dispensing, and an ultrasonic sensor to check the level of the alcohol container. A TFT display integrated to provide information on the present alcohol content and the system's status. Additionally, an LED indicator is positioned on the front of the dispenser to provide a quick visual cue of the alcohol level status: green for full, yellow for half, and red for empty. This combination of digital and visual feedback ensures user convenience and supports efficient system maintenance.
</div>

</details>

---

## 📐 Circuit & Schematic Diagrams

<details>
<summary> <strong>🔋 Circuit Diagram</strong></summary>

![Circuit Diagram](https://github.com/user-attachments/assets/7f9f556d-3927-462e-9fa0-4c9eb9c7d62e)

<div align="justify">
The circuit diagram illustrates the core electronic layout of the microcontroller-based automated hand sanitation dispenser, integrating an ESP32 with various sensors (IR, ultrasonic), a buzzer, motor, and a TFT display. This setup enables real-time detection, automatic dispensing, and remote monitoring via IoT.
</div>

</details>


<details>
<summary> <strong>🖥️ Schematic Diagram</strong></summary>

![Schematic](https://github.com/user-attachments/assets/683d0076-4bb3-4a9a-9227-3d4f7e680669)

<div align="justify">
The schematic diagram illustrates the interconnection of various electronic components such as the ESP32 microcontroller, ultrasonic and IR sensors, TFT display, LED indicator, active buzzer, and vibration sensor—used to create a Microcontroller-Based Automated Hand Sanitation Dispenser with Monitoring System. 
</div>

</details>

---

## 🖼️ Front-End System (TFT UI)

<p align="center">
  <img src="https://github.com/user-attachments/assets/524d290a-4644-4609-bc31-91e6106fe26b"  />
  &nbsp; &nbsp;
  <img src="https://github.com/user-attachments/assets/574bc571-71f6-42fb-8a81-b1f81316b6ff" />
</p>
<p align="center">
  <img src="https://github.com/user-attachments/assets/66bc3262-1553-45a1-b613-b7acd9fb5f61"  />
</p>


---

## 🧠 How to Run the System

### 🧰 Prerequisites

```bash
✅ Arduino IDE
✅ Arduino IoT Cloud Account
✅ ESP32 DevKitC
✅ USB Cable & Wi-Fi Access
✅ Arduino Cloud Agent Installed
```

### ⚙️ Setup Instructions (Step-by-Step)

1. **Clone the Repository**

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
```

2. **Create an Arduino IoT Cloud Account**\
   👉 [https://cloud.arduino.cc](https://cloud.arduino.cc)

3. **Set Up a New Thing**

   - Create a new **Thing**
   - Add your ESP32 device
   - Define cloud variables like:
     ```text
     alcohol_level (int)
     system_status (bool)
     alert_status (bool)
     usage_count (int)
     ```

4. **Edit Configuration Files**

   - In `arduino_secrets.h`:
     ```cpp
     #define SECRET_SSID "YourWiFiName"
     #define SECRET_PASS "YourWiFiPassword"
     ```
   - In `thingProperties.h`: Add your Thing ID, Device ID, and credentials.

5. **Remote Connection to Arduino IDE**

   - In the Arduino Cloud, go to your **Thing**
   - Under "Sketch" tab, click **Open full editor** to load the code into the online IDE
   - Then, click the **Open in Arduino IDE** button to remotely connect the Cloud Sketch to your local Arduino IDE
   - This allows you to run and upload the Cloud-connected code via USB from your computer

6. **Modify TFT\_eSPI Library Pins (Important!)**

   - Go to your Arduino libraries folder: `Documents > Arduino > libraries > TFT_eSPI > User_Setups`
   - Edit the appropriate setup file or `User_Setup.h`
   - Ensure the SPI pins match your ESP32 wiring (MISO, MOSI, CLK, CS, DC, RST)

7. **Install Required Libraries**

- ArduinoIoTCloud
- Arduino\_ConnectionHandler
- TFT\_eSPI
- NewPing

8. **Upload the Sketch**

```bash
Verify ✅ → Upload 🔼
```

9. **Set Up Dashboard Widgets**
   - Gauge: alcohol\_level
   - Switch: system\_status
   - Chart: usage\_count (1, 3, 7, 15d)
   - Alert: email when alert\_status == true

---

## 📬 Email Notification Format

```text
Subject: [ALERT] Refill Needed!
Body: Alcohol level is now below 20%. Please refill the dispenser to maintain sanitation availability.
```

---

## 📍 Component Pinout Reference

```md
| Component        | ESP32 Pin |
|------------------|-----------|
| IR Sensor        | D27       |
| Ultrasonic TRIG  | D13       |
| Ultrasonic ECHO  | D12       |
| Gear Motor       | D33       |
| RGB LED          | D25       |
| TFT LCD          | SPI Pins  |
| Buzzer           | D26       |
| Vibration Sensor | D14       |
```

---

## 📊 Dashboard Preview

```md
![Mobile Dashboard](images/dashboard-mobile.png)
![Desktop Dashboard](images/dashboard-desktop.png)
```

---

## 🔧 Troubleshooting

| Issue                   | Solution                                                |
| ----------------------- | ------------------------------------------------------- |
| Device not connecting   | Check Wi-Fi credentials and Thing ID                    |
| No alcohol data showing | Verify ultrasonic sensor wiring and cloud variable link |
| Email alert not sending | Confirm webhook is mapped to alert\_status              |
| TFT screen blank        | Check SPI config and TFT\_eSPI settings                 |

---

## 📜 License

This project is licensed under the **MIT License**.\
See the [LICENSE](LICENSE) file for details.

---

## 👥 Developers

- **Alvarina, Jake Erico O.**
- **Matola, Aallijah Nic T.**
- **Santos, Jacob S.**
- **Villamor, LL Skynrd A.**

📍 *Bachelor of Science in Computer Engineering – EAC Manila*\
👨‍🏫 Adviser: Engr. Elizier L. Obamos

---

## 🌟 Support This Project

If this helped you, please consider giving it a ⭐, sharing it, or citing it in your own work!\
Let’s build safer, smarter spaces together. 🛡️💡🌐

