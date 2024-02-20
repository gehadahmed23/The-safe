/*
 * EEPROM.h
 *
 * Created: 11/6/2023 11:55:00 AM
 *  Author: Dell
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

	unsigned char EEPROM_read(const unsigned short address);
	void EEPROM_write(char data, unsigned short address);

#endif /* EEPROM_H_ */