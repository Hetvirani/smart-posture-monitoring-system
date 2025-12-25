#  Smart Posture Monitoring System

An **IoT-based intelligent posture detection system** built using **ESP32, Flex Sensor, Ultrasonic Sensors and Machine Learning (Decision Tree)** to monitor sitting posture in real-time and send **instant alerts** to the user via **Blynk mobile app**.

This system helps students and office workers avoid long-term back and neck problems caused by poor sitting habits.

---

##  Project Overview

Poor sitting posture leads to back pain, neck strain and spinal issues, especially for people who sit for long hours. Most existing solutions are either expensive, uncomfortable, or do not provide real-time correction.

This project provides a **low-cost, privacy-safe and portable** solution that:

* Detects posture using sensors mounted on the chair
* Processes data using ESP32
* Uses a **machine learning decision tree** for classification
* Sends **real-time alerts** to the user’s phone

---

##  Key Features

* Real-time posture monitoring
* Machine learning based posture classification
* Instant mobile alerts using Blynk
* No camera or wearable required
* Low-cost and portable design
* Noise-filtered and accurate sensor readings

---

##  Hardware Components

* ESP32 Microcontroller
* Flex Sensor
* 2 × HC-SR04 Ultrasonic Sensors
* Breadboard & Jumper Wires
* Power Bank / USB Supply

---

##  Software & Tools

* Arduino IDE (ESP32 firmware)
* Python (Machine Learning)
* Scikit-learn (Decision Tree)
* Pandas & Matplotlib
* Blynk IoT Platform

---

##  System Working (Detailed)

### 1. Sensor Data Acquisition

* The **flex sensor** is attached to the user’s upper spine and measures how much the back bends.
* Two **ultrasonic sensors** are mounted on the chair back to measure the distance between the user and the chair at two heights.

When the user slouches, the flex sensor bends more and the ultrasonic distances decrease.

---

### 2. Signal Smoothing

Raw sensor readings contain noise.
ESP32 uses **moving average filtering** to smooth flex and ultrasonic values, making the system stable and reliable.

---

### 3. Feature Calculation

ESP32 computes:

* **Flex_Mapped = 145 − Flex_ADC_Average**
* **Difference = |Ultrasonic_1 − Ultrasonic_2|**

These two values represent the posture condition.

---

### 4. Machine Learning Decision Tree

A Decision Tree was trained using real posture data collected in three states:

* Straight
* Slight lean
* Slouched

From this model, logical thresholds were extracted and implemented into ESP32 firmware.

---

### 5. Real-Time Classification

ESP32 checks posture every second:

* Reads sensors
* Computes features
* Applies Decision Tree logic
* Classifies posture as **Good** or **Bad**

---

### 6. IoT Alert System

If **Bad posture** is detected:

* ESP32 sends an event to **Blynk Cloud**
* User receives instant mobile notification
  *“Bad posture detected! Please sit straight.”*

---

### 7. Continuous Feedback

Once the user corrects posture, sensor values return to normal and alerts stop automatically.

---

##  Machine Learning

* Dataset collected from real sitting postures
* Features:

  * Flex sensor value
  * Ultrasonic distance difference
* Model: Decision Tree Classifier
* Used to determine posture classification rules

These rules were converted into ESP32 code for real-time use.

---

##  Repository Structure

```
Smart-Posture-Monitoring-System/
│
├── esp32_code/
│   └── posture_monitor.ino
│
├── machine_learning/
│   ├── decision_tree.py
│   ├── Flex_ultrasonic_data_labeled.csv
│   └── decision_tree.png
│
├── report/
│   ├── Minor_Project_Report.pdf
│   └── Presentation.pptx
│
├── images/
│   ├── block_diagram.png
│   ├── flowchart.png
│   ├── chair.jpg
│   └── result_graph.png
│
└── README.md
```

---

##  IoT Platform

The project uses **Blynk IoT** for:

* Real-time alerts
* Mobile notifications
* Cloud connectivity

---

##  Applications

* Students studying for long hours
* Office professionals
* Online learners
* Work-from-home users
* Ergonomic research

---

##  Future Enhancements

* Add IMU (MPU6050) for full body posture
* Cloud-based posture analytics
* Mobile dashboard with graphs
* Personalized ML model per user
* Wearable integration

---

##  Authors

**Het Virani (22BIT252D)**

**Dilon Brahmbhatt (22BIT236D)**

Under the guidance of
**Dr. Amit G Kumar**
**Dr. V Vikas**

Pandit Deendayal Energy University, Gandhinagar
