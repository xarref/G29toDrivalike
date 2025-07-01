# expressESLR F1 RC Demonstrator

Early-stage proof-of-concept of an FPV remotely controlled Formula 1 replica, using the **expressESLR** low-latency signaling protocol over ESP32.

This system was developed as a **technical demonstrator** and **investor pitch** for a startup project focused on remote-controlled high-performance vehicles. It integrates a 1:10 scale Formula 1 RC car, a Logitech G29 racing simulator, and a wireless transmission system for ultra-low-latency driving via FPV (first-person view).

> 🚧 **Note:** Details of the final prototype are not disclosed due to confidentiality and ongoing IP protection efforts.

---

## 🏁 Project Overview

- **Goal:** Demonstrate feasibility of expressESLR over ESP32 to control an RC Formula 1 car remotely with racing-grade feedback.
- **Hardware:**  
  - **Transmitter:** ESP32 connected to a Logitech G29 (via USB Host)  
  - **Receiver:** ESP32 onboard the RC car  
  - **Car:** 1:10 scale F1 replica with modified control system  
  - **Video:** FPV camera mounted on car; receiver used for real-time driver feedback
- **Protocol:** `expressESLR` – custom lightweight protocol optimized for sub-15ms end-to-end latency.
- **Interface:** G29 wheel and pedals were mapped to throttle, steering, and braking inputs.

---

## 🚗 Features

- ✅ Real-time wireless control of RC car using driving simulator input  
- ✅ Sub-20ms round-trip latency  
- ✅ Bi-directional communication (commands + feedback)  
- ✅ Modular architecture for upgrading components (e.g., simulator, vehicle, RF link)

---

## 🔧 Getting Started

### Requirements

- ESP32 Dev Kit (x2)
- Logitech G29 Racing Wheel
- 1:10 scale RC F1 car (PWM or servo-compatible)
- FPV camera + receiver (optional, for full experience)
- Arduino IDE or PlatformIO

### Basic Setup

1. Connect G29 to the ESP32 (requires USB host support or intermediary computer)
2. Flash `tx_esp32.ino` to transmitter ESP32
3. Flash `rx_esp32.ino` to receiver ESP32
4. Mount the receiver module and power it on the RC car
5. Power the G29 and the transmitter ESP32
6. Start driving remotely!

> ⚠️ Some components (like USB-to-Serial bridge for G29 input) may require custom firmware or middleware – see `/tools/usb_bridge/`.




## 🚀 Future Work

- Transition from G29 to custom-built simulator rig with force feedback and haptics
- Move to proprietary radio protocol for higher throughput and security
- Implement low-latency video feedback integration with expressESLR control stream
- Full-scale prototype

---

## 💼 Purpose

This project served as a **technical validation platform** for a startup concept in the field of remote and autonomous high-performance vehicle operation. The 1:10 scale demonstrator provided a compact and safe environment for real-time wireless driving experiments using consumer-grade and custom-built hardware.

---

## 📜 License

This repository is released under the MIT License for educational and research purposes. For commercial or derivative use, please contact the author.

---

