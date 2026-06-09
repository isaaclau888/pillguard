#include <Wire.h>
#include <RTClib.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit.GFX.h>
#include <TouchScreen.h>

#define STEPPER_IN1 22
#define STEPPER_IN2 23
#define STEPPER_IN3 24
#define STEPPER_IN4 25
#define IR_PILL 10
#define IR_CUP 11
#define BUZZER 12

#define YP A1 //Touch Y+
#define XM A2 //Touch X-
#define YM 7 //Touch Y-
#define XP 6 //Touch X+

MCUFRIEND_kbv tft;
RTC_DS3231 rtc;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int remainingPills[6] = {42, 35, 28, 40, 30, 25};
int dailyDose[6] = {2, 2, 1, 2, 1, 2};

unsigned long lastupdate = 0;

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(IR_PILL, INPUT_PULLUP);
  pinMode(IR_CUP, INPUT_PULLUP);

  for(int i=22; i<=25; i++) pinMode(i, OUTPUT);

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

    TSPoint p = ts.getpoint();
    if (p.z > 20) {
      tone(BUZZER, 1000, 100);
    }

    delay(50);
  }
}

void drawHomeScreen() {
  tft.fillScreen(0x0000);
  tft.serTextColor(0xFFFF;
  tft.setTextSize(3);
  tft.setCursor(20, 20);
  tft.println("SmartPill");
  tft.setCursor(20, 60);
  tft.println("Guardian");
}

void updateTimeDisplay() {
  DateTime now = rtc.now();
  tft.fillRect(20. 120, 250, 40, 0x0000);

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

  rotateToCompartment(compartment);

  int count = 0;
  while (count < quantity) {
    stepMotor(40);
    if (digitalRead(IR_PILL) == LOW) {
      count++;
      delay(300);
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