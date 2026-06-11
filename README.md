# PillGuard
Have you ever wanted to build a pill dispenser for yourself or your family?
For me, the answer is yes!

So here comes PillGuard, a pill dispenser that keeps track of and tells you when to take your pills. 
This is a completely open-source project. All the 3D parts and the BOM list are in the folders. You may customise my project. 

## How to build it
Please print all the 3D parts. <p>
<img width="552" height="542" alt="螢幕截圖 2026-06-11 下午5 09 00" src="https://github.com/user-attachments/assets/470ea0fd-2f6f-43b6-975f-0060920c16e2" /> <p>
First, try placing the bottom part with the HC‑SR04 sensor in it. <p>

<img width="617" height="586" alt="螢幕截圖 2026-06-11 下午5 09 55" src="https://github.com/user-attachments/assets/f5b31174-d639-4a9c-aa6d-57cd4635f433" /> <p>
Secondly, place the middle part with the 28BYJ-48 Stepper Motor + ULN2003 Driver and another HC‑SR04 sensor. <p>

<img width="704" height="579" alt="螢幕截圖 2026-06-11 下午5 10 14" src="https://github.com/user-attachments/assets/055d63ba-232e-4598-943a-1c07d0d22db6" /> <p>
Thirdly, place the spinning system above the 28BYJ-48 Stepper Motor. <p>

<img width="738" height="557" alt="螢幕截圖 2026-06-11 下午5 10 55" src="https://github.com/user-attachments/assets/215b6bfb-613b-46aa-801f-ae3c32337334" /> <p>
Last but not least, put the cover on top of the bottom part with the 3.5-inch screen and Arduino Mega 2560(The blue shaded place is where you place the screen and the Arduino Board).

# Wiring Diagram 
<img width="5000" height="2852" alt="PillGuard Wiring Diagram" src="https://github.com/user-attachments/assets/5a294efe-fa0a-44d8-9e1d-460cd1e3fa5a" />

Screen: Just follow the diagram. <p>
DS3231 RTC (Real-Time Clock): VCC -> Breadboard (+) Red Rail, GND -> Breadboard (-) Blue Rail, Trig -> Arduino Mega 2560 Pin 20, Echo -> Arduino Mega 2560 Pin 21 <p>
HC-SR04(Cup Sensor): VCC -> Breadboard (+) Red Rail, GND -> Breadboard (-) Blue Rail, Trig -> Arduino Mega 2560 Pin 22, Echo -> Arduino Mega 2560 Pin 23 <p>
HC-SR04(Pill Drop Sensor): VCC -> Breadboard (+) Red Rail, GND -> Breadboard (-) Blue Rail, Trig -> Arduino Mega 2560 Pin 24, Echo -> Arduino Mega 2560 Pin 25 <p>
ULN2003(Steeper Motor Driver): VCC -> Breadboard (+) Red Rail, GND -> Breadboard (-) Blue Rail, IN1 -> Arduino Mega 2560 Pin 26, IN2 -> Arduino Mega 2560 Pin 27, IN3 -> Arduino Mega 2560 Pin 28, IN4 -> Arduino Mega 2560 Pin 29 <p>
Buzzer: Positive(+) -> Arduino Mega 2560 Pin 30, Negative(-) -> Breadboard (-) Blue Rail 

## Why this project actually exists
The reason why this project exists is that the HKDSE 2026 DAT SBA required students to make a  device for medication management and facilitation of medication taking.

Design Problem:
Design and make a device for medication management and facilitation of medication taking.
This device must satisfy the following requirements:
(a) Store at least five different pills separately, allow patients to set different dosages and medication times for each pill, and automatically dispense the required quantity of pills at the right time, for a period of at least one week;
(b) Provide medication reminders to patients in a variety of ways at a predetermined time until the patient confirms that the medication has been taken;
(c) Include a function that automatically provides the right amount of water to drink when it is time to take the medicine;
(d) Add a function that provides practical value to the patients. (For example, properly preserving the medicine.)

But I removed the part (c) feature in this project.

## How I made it
Guess how I made it. I made it by using Fusion 360, which is a completely free CAD app for students. The reason why I made this is that I want to make people not hate taking medicine. By using the dispenser, you can interact with it, making it more fun when you're ill. 

<img width="1920" height="1080" alt="SBA_2026-Apr-05_04-36-30AM-000_CustomizedView2692837445_png" src="https://github.com/user-attachments/assets/dc42f173-fd3d-4094-821b-169f19203c84" />

## How to use it?
The question you may ask is how to use this pill dispenser. To use this dispenser, you must set a timer on the app and select which medicine you're taking. For example, at 1 pm, I need to take 2 Panadol Pills. Then it will follow your instructions and do the task at 1 pm.

## Fallout Zine
![PillGuard Fallout Zine](https://github.com/user-attachments/assets/303d7f12-3a6c-406c-90b4-af13834227f8)
