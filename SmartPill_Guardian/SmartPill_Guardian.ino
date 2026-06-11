#include <Wire.h>
#include <RTClib.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

#define TRIG_PIN_CUP 22
#define ECHO_PIN_CUP 23

#define TRIG_PIN_DROP 24
#define ECHO_PIN_DROP 25

#define STEPPER_IN1 26
#define STEPPER_IN2 27
#define STEPPER_IN3 28
#define STEPPER_IN4 29

#define BUZZER 30

#define YP A1 //Touch Y+
#define XM A2 //Touch X-
#define YM 7 //Touch Y-
#define XP 6 //Touch X+

MCUFRIEND_kbv tft;
RTC_DS3231 rtc;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int remainingPills[6] = {42, 35, 28, 40, 30, 25};
int dailyDose[6] = {2, 2, 1, 2, 1, 2};

unsigned long lastUpdate = 0;

void drawHomeScreen();
void updateTimeDisplay();
void checkLowStock();
void dispenseMedication(int compartment, int quantity);
void rotateToCompartment(int comp);
void stepMotor(long steps);
void showWarning(String msg);
void triggerReminder();
long readUltrasonicDistance(int trigPin, int echoPin);

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN_CUP, OUTPUT);
  pinMode(ECHO_PIN_CUP, INPUT);
  pinMode(TRIG_PIN_DROP, OUTPUT);
  pinMode(ECHO_PIN_DROP, INPUT);

  for(int i=22; i<=25; i++) {
    pinMode(i, OUTPUT); 
  }

  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(0x0000);

  if(!rtc.begin()) {
    Serial.println("RTC not found");
  }

  Serial.println("SmartPill Guardian Started");
  drawHomeScreen();
}

void loop() {
  if (millis() - lastUpdate > 1000) {
    updateTimeDisplay();
    checkLowStock();
    lastUpdate = millis();
  }

  DateTime now = rtc.now();
  if ((now.hour() == 8 || now.hour() == 14 || now.hour() == 20) && now.minute() == 0) {
    dispenseMedication(0, 2);
  }

  TSPoint p = ts.getPoint();
  if (p.z > 20) {
    tone(BUZZER, 1000, 100);
  }

  delay(50);
}

void drawHomeScreen() {
  tft.fillScreen(0x0000);
  tft.setTextColor(0xFFFF;
  tft.setTextSize(3);
  tft.setCursor(20, 20);
  tft.println("SmartPill");
  tft.setCursor(20, 60);
  tft.println("Guardian");
}

void updateTimeDisplay() {
  DateTime now = rtc.now();
  tft.fillRect(20, 120, 250, 40, 0x0000);

  tft.setTextSize(4);
  tft.setTextColor(0x07E0);
  tft.setCursor(40, 130);
  char buf[6];
  sprintf(buf, "%02d:%02d", now.hour(), now.minute());
  tft.print(buf);
}

void showWarning(String msg) {
  tft.fillRect(20, 200, 300, 60, 0xF800);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(2);
  tft.setCursor(30, 220);
  tft.print(msg);
}

void dispenseMedication(int compartment, int quantity) {
  showWarning("Dispensing...");

  long cupDistance = readUltrasonicDistance(TRIG_PIN_CUP, ECHO_PIN_CUP);
  if (cupDistance > 10) {
    showWarning("Error: Place Cup!");
    triggerReminder();
    return;
  }

  rotateToCompartment(compartment);

  int count = 0;
  unsigned long startWait = millis();

  while (count < quantity) {
    stepMotor(40);

    long dropDistance = readUltrasonicDistance(TRIG_PIN_DROP, ECHO_PIN_DROP);
    if (dropDistance < 5) {
      count++;
      delay(300);
    }

    if (millis() - startWait > 15000) {
      showWarning("Dispenser Jammed!");
      triggerReminder();
      return;
    }
  }

  remainingPills[compartment] -= quantity;
  showWarning("Take Medicine Now");
  triggerReminder();
}

void rotateToCompartment(int comp) {
  long steps = comp * 341L;
  stepMotor(steps);
}

void stepMotor(long steps) {
  for (long i = 0; i < abs(steps); i++) {
    digitalWrite(STEPPER_IN1, HIGH); delay(3);
    digitalWrite(STEPPER_IN1, LOW);
    digitalWrite(STEPPER_IN2, HIGH); delay(3);
    digitalWrite(STEPPER_IN2, LOW);
    digitalWrite(STEPPER_IN3, HIGH); delay(3);
    digitalWrite(STEPPER_IN3, LOW); 
    digitalWrite(STEPPER_IN4, HIGH); delay(3);
    digitalWrite(STEPPER_IN4, LOW); 
  }
}

void triggerReminder() {
  for (int i = 0; i < 5; i++) {
    tone(BUZZER, 1500, 300);
    delay(500);
  }
}

void checkLowStock() {
  for (int i = 0; i < 6; i++) {
    float daysLeft = (float)remainingPills[i] / dailyDose [i];
    if (daysLeft <= 7.0) {
      showWarning("Low Stock! Refill Soon");
      triggerReminder();
      return;
    }
  }
}

long readUltrasonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;
  return (distance == 0) ? 999 : distance;
}