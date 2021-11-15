/*
 * lcd.h
 *
 * Created: 11.11.2021 16:25:42
 *  Author: Dmitry
 */ 
#ifndef LCD_H_
#define LCD_H_

#include <util/delay.h>
#include <avr/pgmspace.h>

void SPI_init() {
	/* SPI Master FCPU/32 setup falling and /SS, MOSI, SCK as out */
	DDRB = (1<<PINB2 | 1<<PINB3 | 1<<PINB5);
	SPCR = (1<<SPE | 1<<MSTR | 1<<CPHA | 1<<SPR1);
	SPSR = (1<<SPI2X);
}

typedef enum {LCD_CMD = 0b11111000, LCD_DATA = 0b11111010} LCD_packet;
	
//inline void SPI_send_byte 

void SPI_send(LCD_packet type, const char* PROGMEM buffer , uint16_t buffer_count) {
	register uint8_t tmp;
	PORTB |= (1<<PINB2);
	do {
		tmp = pgm_read_byte(buffer);
		SPDR = type;
		while(!(SPSR & 1<<SPIF));
		SPDR = tmp & 0xF0;
		while(!(SPSR & 1<<SPIF));
		SPDR = tmp << 4;
		while(!(SPSR & 1<<SPIF));
		buffer++;
		_delay_us(30);
	} while (--buffer_count);
	PORTB &= ~(1<<PINB2);
}



#endif /* LCD_H_ */