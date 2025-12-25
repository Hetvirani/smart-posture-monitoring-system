#define BLYNK_TEMPLATE_ID "TMPL3Dk8tWFlr"
#define BLYNK_TEMPLATE_NAME "IIIT first"
#define BLYNK_AUTH_TOKEN "hFRu-SpucvtZ_m4t6Hvpdrm7tD09rsLk"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Dilon_motorola";
char pass[] = "Dilon1103";

// FLEX SENSOR — using your exact logic
const int flexPin = 34; // ADC1 pin on ESP32 (e.g. GPIO 32-39)
const int numFlexReadings = 5;
int flexReadings[numFlexReadings];
int flexIndex = 0;
int flexTotal = 0;
int flexCount = 0;
int flexAverage = 0;
float sensorReading = 0; // final (145 - average)

// ULTRASONIC
const int trigPin1 = 19;
const int echoPin1 = 18;
const int trigPin2 = 5;
const int echoPin2 = 17;

// Smoothing for ultrasonic
const int numUSReadings = 5;
float us1Readings[numUSReadings] = {0};
float us2Readings[numUSReadings] = {0};
int usIndex = 0;
float us1Total = 0;
float us2Total = 0;
int usCount = 0;

BlynkTimer timer;

// -------- Read Distance (cm) --------
float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 40000); // 40ms timeout
  float dist = (duration == 0) ? 0.0 : (duration * 0.0343) / 2.0;
  return dist;
}

// -------- Decision Tree --------
int decision_tree(float flexSensorReading, float difference) {
  // Based on your tree:
  if (flexSensorReading <= 13.5) {
    return 0;
  } else {
    if (flexSensorReading <= 15.5) {
      return 0;
    } else {
      if (difference <= 5.005) {
        return 1; // BAD posture
      } else {
        return 0;
      }
    }
  }
}

// -------- Main Monitoring Function --------
void checkPostureAndNotify() {
  //---------------- FLEX SENSOR LOGIC (YOUR CODE) ----------------//
  flexTotal -= flexReadings[flexIndex];
  int newFlex = analogRead(flexPin);
  flexReadings[flexIndex] = newFlex;
  flexTotal += newFlex;
  flexIndex = (flexIndex + 1) % numFlexReadings;
  if (flexCount < numFlexReadings) flexCount++;
  flexAverage = flexTotal / flexCount;
  sensorReading = 145.0 - flexAverage; // EXACTLY FROM YOUR CODE

  //---------------- ULTRASONIC SENSORS ----------------//
  float us1 = readDistance(trigPin1, echoPin1);
  float us2 = readDistance(trigPin2, echoPin2);

  us1Total -= us1Readings[usIndex];
  us2Total -= us2Readings[usIndex];

  us1Readings[usIndex] = us1;
  us2Readings[usIndex] = us2;

  us1Total += us1;
  us2Total += us2;

  usIndex = (usIndex + 1) % numUSReadings;
  if (usCount < numUSReadings) usCount++;

  float us1Avg = us1Total / usCount;
  float us2Avg = us2Total / usCount;
  float difference = abs(us1Avg - us2Avg);

  //---------------- DECISION TREE & BLYNK NOTIFY ----------------//
  Serial.print("Flex mapped (sensorReading): ");
  Serial.print(sensorReading, 2);
  Serial.print(" | US1: ");
  Serial.print(us1Avg, 2);
  Serial.print(" | US2: ");
  Serial.print(us2Avg, 2);
  Serial.print(" | Diff: ");
  Serial.println(difference, 2);

  int result = decision_tree(sensorReading, difference);

  if (result == 1) {
    Blynk.logEvent("bad_posture", "⚠ Bad posture detected! Please adjust.");
    Serial.println("ALERT: Bad posture detected!");
  } else {
    Serial.println("✅ Good posture.");
  }

  Serial.println("==========================");
}

void setup() {
  Serial.begin(9600);
  pinMode(flexPin, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);

  // Initialize arrays
  for (int i = 0; i < numFlexReadings; i++) {
    flexReadings[i] = 0;
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, checkPostureAndNotify); // Every 1 second
}

void loop() {
  Blynk.run();
  timer.run();
}