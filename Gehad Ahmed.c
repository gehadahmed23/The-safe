
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
#include "LCD.h"
#include "std_macros.h"
#include "ultrasonic.h"
#include "keypad_driver.h"
#include "Timer.h"
#include <avr/interrupt.h>
#include "EEPROM.h"
#include <math.h>
#include <stdio.h>
#define  EEPROM_STATUS_LOCATION 0x40
#define  EEPROM_PASSWORD_LOCATION1 0x41
#define  EEPROM_PASSWORD_LOCATION2 0x42
#define  EEPROM_PASSWORD_LOCATION3 0x43
#define  EEPROM_PASSWORD_LOCATION4 0x44
#define MAX_TRIES 3
#define Repeat_process 1
volatile unsigned short counter = 0, flag = 0, flag2 = 0, counter2 = 0, distance, time =  10;
char arr[4];
char value=NOTPRESSED, i, tries=MAX_TRIES, repeat = Repeat_process;
int main(void)
{
	
	keypad_vInit();
	LCD_vInit();
	timer_CTC_init_interrupt();
	DIO_vsetPINDir('D', 3, 1);
	DIO_vsetPINDir('C', 0, 1);
	
	if(EEPROM_read(EEPROM_STATUS_LOCATION) == NOTPRESSED){
		LCD_vSend_string("set password : ");
		LCD_movecursor(2,4);
		for (i = 0; i < 4; i++){
			do
			{
				value = keypad_u8check_press();
				
			} while (value == NOTPRESSED);
			LCD_vSend_char(value);
			_delay_ms(500);
			LCD_movecursor(2,4+i);
			LCD_vSend_char('*');
			_delay_ms(10);
			EEPROM_write(EEPROM_PASSWORD_LOCATION1 + i, value);
		}
		EEPROM_write(EEPROM_STATUS_LOCATION, 0x00);
	}
	
	LCD_clearscreen();
	LCD_vSend_string("Welcome to the");
	LCD_movecursor(2, 5);
	LCD_vSend_string("safe");

	while (1)
	{
		
	  distance = ultrasonic_distance(distance);
	  if(distance <= 10){
		  label_repeat:
		  label_repeat2:
		  LCD_clearscreen();
		  arr[0] = arr[1] = arr[2] = arr[3] = NOTPRESSED;
		  LCD_vSend_string("Check password :");
		  LCD_movecursor(2, 2);
		  
		  for (i = 0; i < 4; i++){
			  counter = 0;
			  do
			  {
				  if(counter >= 2000){
					  flag = 1;
				  }
				  arr[i] = keypad_u8check_press();
				  
			  } while (arr[i] == NOTPRESSED && flag == 0);
			  LCD_vSend_char(arr[i]);
			  _delay_ms(500);
			  LCD_movecursor(2,2+i);
			  LCD_vSend_char('*');
			  _delay_ms(10);
			  if(flag == 1){
				  LCD_clearscreen();
				  LCD_vSend_string("Time exceed");
				  _delay_ms(1000);
				  LCD_clearscreen();
				  LCD_vSend_string("System Off");
				  _delay_ms(3000);
				  time = 15;
				  LCD_clearscreen();
				  LCD_vSend_string("Wait 15 seconds");
				  LCD_movecursor(2, 4);
				  LCD_vSend_string("to repeat");
				  while (time > 0)
				  {
					  if(counter >= 100){
						  LCD_clearscreen();
						  LCD_vSend_string("Left ");
						  char buf[2];
						  LCD_sendFloat(--time, buf, 0);
						  LCD_vSend_string(buf);
						  LCD_vSend_string(" seconds");
						  counter = 0;
					  }
				  }
				   time = 10, tries = MAX_TRIES;
				   flag = 0; 
				  goto label_repeat;
			  }
		  }
		  if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
		  {
			  LCD_clearscreen();
			  LCD_movecursor(1, 3);
			  LCD_vSend_string("Right password");
			  LCD_movecursor(2,3);
			  LCD_vSend_string("safe opened");
			  _delay_ms(5000);
			   LCD_clearscreen();
			   LCD_vSend_string("Welcome to the");
			   LCD_movecursor(2, 5);
			   LCD_vSend_string("safe");
		  }
		  else
		  {
			  tries=tries-1;
			  if (tries>0)
			  {
				  LCD_clearscreen();
				  LCD_vSend_string("Wrong password");
				  _delay_ms(1000);
				  LCD_clearscreen();
				  LCD_vSend_string("tries left:");
				  LCD_vSend_char(tries+48);
				  _delay_ms(1000);
				  goto label_repeat;
				  
			  }
			  else
			  {
				  if(repeat > 0){
					  LCD_clearscreen();
					  LCD_vSend_string("Wrong password");
					  _delay_ms(1000);
					  LCD_clearscreen();
					  LCD_vSend_string("Wait 10 seconds");
					  LCD_movecursor(2, 4);
					  LCD_vSend_string("to repeat");
					  counter = 0, time = 10;
					  while (time > 0)
					  {
						  if(counter >= 100){
							  LCD_clearscreen();
							  LCD_vSend_string("Left ");
							  LCD_vSend_char(--time + '0');
							  LCD_vSend_string(" seconds");
							  counter = 0;
						  }
					  }
					  repeat--, time = 10, tries = MAX_TRIES;
					  goto label_repeat2;
				  }
				  else {
					  LCD_clearscreen();
					  LCD_vSend_string("There are thiefs");
					  DIO_write('C', 0, 1);
					  do
					  {
						  distance = ultrasonic_distance(distance);
						  
					  } while (distance <= 20);
					  _delay_ms(2000);
					  DIO_write('C', 0, 0);
					  repeat = 2;
					  LCD_clearscreen();
					  LCD_vSend_string("Welcome to the");
					  LCD_movecursor(2, 5);
					  LCD_vSend_string("safe");
					  time = 10, tries = MAX_TRIES;
				  }
				  
			  }
		  } 
		  
	  }
}
 }

 ISR(TIMER0_COMP_vect){
	 counter++;
 }






