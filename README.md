# Robotic-Chase-Game

For this project, I worked in a group to create a robotic chase game using C++ code and Arduinos. Each member of the group had to use an Arduino that works along with 2 different devices. The devices ranged from an LCD to ulltrasonic sensors to servo motors. I ended up learning a lot about coding hardware and using the Arduino IDE. We collaborated as a group and did our best to follow a timeline which would allow us to complete the project.

We made the Arduinos communicate with each other using serial communication, more specifically serial chaining. We had to use the TX and RX pins in a specific pattern(connecting the Arduinos with wires) because the Arduinos would not communicate if the wiring was done out of order. We connected the TX pin to the RX pin of the other Arduino and followed the pattern through. Otherwise, there would be no communication occurring even if the wiring is right.

# Materials

1. Arduino Uno R3
2. 2 Arduino Uno R4 Wifi
3. I2C LCD
4. Couple of 220 Ohms resistors
5. Couple of 10k Ohms resistors
6. 3 LEDs
7. Ultrasonic Sensor
8. Buzzer
9. Servo Motor
10. Button
11. Wires

# Refreences

Here are a list of refrences we used in order to understand how communication occurs and how to wire some parts as we used parts that we did not have experience using:

https://docs.arduino.cc/learn/electronics/servo-motors/ 
https://www.instructables.com/Arduino-Servo-Motors/
https://docs.arduino.cc/built-in-examples/digital/toneMelody/ 
https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/ 
https://www.arduino.cc/reference/tr/language/functions/communication/serial/available/
