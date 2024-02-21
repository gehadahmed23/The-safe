# The-safe

Safe project 🔒

I'm happy to share the latest project I worked on to determine if someone is in front of the safe to enter the password.

🔘Idea of project :

when first use, the password is set by the user and stored in EEPROM unit,If you restart it again, it will start to check direct , after that it is started to check whether the password that the user enters is correct or not.

🔘System cases :

-In the first case, if there is a person within 10 cm of the safe, a message will appear on the LCD to test the password using Ultrasonic :

1- if password is correct , message appears on the LCD.

2- If it takes 20 seconds to enter the password, the system will stop and wait 15 seconds until it is used again.

3- if password is incorrect and you continue to enter the password for 3 times with the error, the system will stop for 10 seconds until it restarts again. However, if he continues to enter the password incorrectly 3 more times, this indicates that he is not the owner of the safe, and it will be determined that he is a thief. This will appear on the LCD screen, and the buzzer will start making a warning sound. It starts at a distance of 20 cm and stops after 2 seconds.
      
-In the second case, If there is no person within 10 cm of the safe, a welcome message will appear on the LCD until someone comes.
      
🔘 Hardware:

-Ultrasonic sensor
-buzzer
-LCD 2*16
-Variable resistance << To control the lighting intensity
-Keypad "with internal pull up"
-AVR
-Atmega32A 


🔘 Software:

-Main Application Layer
-HAL Layer (LCD, EEPROM, Keypad, Ultrasonic).
-MCAL Layer (DIO, TIMER).

proteus design :

![image](https://github.com/gehadahmed23/The-safe/assets/123056355/685c58d5-9940-474b-994a-f00804e15bfb)
