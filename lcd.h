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

#define LCD_CS_START() (PORTB |= (1<<PINB2))
#define LCD_CS_STOP() (PORTB &= ~(1<<PINB2))

typedef enum {LCD_CMD = 0b11111000, LCD_DATA = 0b11111010} LCD_packet;

void SPI_init() {
	/* SPI Master FCPU/32 setup falling and /SS, MOSI, SCK as out */
	DDRB = (1<<PINB2 | 1<<PINB3 | 1<<PINB5);
	SPCR = (1<<SPE | 1<<MSTR | 1<<CPHA | 1<<SPR1);
	SPSR = (1<<SPI2X);
}

void SPI_out(char byte) {
	SPDR = byte;
	while(!(SPSR & 1<<SPIF)) {}
}

void LCD_send(LCD_packet type, const char* PROGMEM buffer , uint16_t buffer_count) {
	register uint8_t tmp;
	LCD_CS_START();
	do {
 		tmp = pgm_read_byte(buffer);
		SPI_out(type);
		SPI_out(tmp & 0xF0);
		SPI_out(tmp << 4);
		buffer++;
		_delay_us(30);
	} while (--buffer_count);
	LCD_CS_STOP();
}

// void LCD_clean() {
// 	for(int i=0; i < ) {
// 	}
// }


#endif /* LCD_H_ */