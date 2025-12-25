# Smart Posture Monitoring System

An IoT-based intelligent posture detection system using ESP32, Flex Sensor, Ultrasonic Sensors and Machine Learning (Decision Tree) to detect bad sitting posture and send real-time alerts via Blynk.

---

## 🔍 Overview
This system continuously monitors a user’s sitting posture using:
- Flex sensor to detect spinal bending
- Two ultrasonic sensors to detect back-to-chair distance

A trained Decision Tree model is used to derive posture classification rules, which are embedded into ESP32 firmware for real-time inference.

---

## 🛠 Hardware Used
- ESP32
- Flex Sensor
- 2× HC-SR04 Ultrasonic Sensors
- Breadboard, Jumper wires
- Power Bank / USB power

---

## 📡 Working
1. ESP32 reads flex sensor and ultrasonic distances.
2. Data is smoothed using moving average.
3. Difference between ultrasonic sensors is calculated.
4. Decision Tree rule is applied.
5. If posture is bad → Blynk notification sent to mobile.

---

## 🤖 Machine Learning
We used a Decision Tree classifier trained on 200 samples:
- Features: Flex value, Ultrasonic difference
- Labels: 0 = Good posture, 1 = Bad posture

Trained in Python using scikit-learn.

---

## 📂 Repository Structure
- esp32_code → Arduino firmware
- machine_learning → Dataset + Decision Tree training
- report → Project report & PPT
- images → Hardware photos, block diagram, flowchart, graphs

---

## 📱 IoT Platform
Blynk IoT is used to send real-time mobile alerts when bad posture is detected.

---

## 👨‍💻 Authors
- Het Virani (22BIT252D)
- Dilon Brahmbhatt (22BIT236D)

Under guidance of Dr. Amit G Kumar & Dr. V Vikas
Pandit Deendayal Energy University
