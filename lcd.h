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
#include "font8x8.h"

#define lcd_init_size 2
static const char lcd_init[] PROGMEM = {
	0x30,// Basic function set
	0x36 // Extended function set + graphic display on
};

static uint8_t lcd_buffer[64][16]; //(16*8)x64

#define LCD_CS_START() (PORTB |= (1<<PINB2))
#define LCD_CS_STOP() (PORTB &= ~(1<<PINB2))

inline void SPI_init() {
	/* SPI Master FCPU/32 setup falling and /SS, MOSI, SCK as out */
	DDRB = (1<<PINB2 | 1<<PINB3 | 1<<PINB5);
	SPCR = (1<<SPE | 1<<MSTR | 1<<CPHA | 1<<SPR1);
	SPSR = (1<<SPI2X);
}

inline void SPI_out(uint8_t byte) {
	SPDR = byte;
	while(!(SPSR & 1<<SPIF)) {}
}

typedef enum {LCD_TYPE_CMD = 0b11111000, LCD_TYPE_DATA = 0b11111010} LCD_packet;

void LCD_out(LCD_packet type, uint8_t byte) {
	SPI_out(type);
	SPI_out(byte & 0xF0);
	SPI_out(byte << 4);
	if(type == LCD_TYPE_CMD) _delay_us(30);
}

inline void LCD_cmd(uint8_t byte) {
	LCD_out(LCD_TYPE_CMD, byte);
}

inline void LCD_data(uint8_t byte) {
	LCD_out(LCD_TYPE_DATA, byte);
}

void LCD_init() {
	uint8_t counter = lcd_init_size;
	const char * PROGMEM buffer = lcd_init;
	LCD_CS_START();
	SPI_init();
	while(counter--) {
		LCD_cmd(pgm_read_byte(buffer++));
	}
	LCD_CS_STOP();
}

void LCD_clean(uint8_t byte) {
	for (uint8_t vstr = 0; vstr <= 63; ++vstr) {
		for (uint8_t hstr = 0; hstr <= 15; ++hstr) {
			lcd_buffer[vstr][hstr] = byte;
		}
	}
}

/* 128*64(X*Y) without check area */
void LCD_buffer_flash(uint8_t st_x, uint8_t st_y, uint8_t fn_x, uint8_t fn_y) {
	uint8_t max_y = (fn_y > 63) ? 63 : fn_y;
	uint8_t min_xh = (st_x>>4);
	uint8_t min_x =  (min_xh<<1); //(st_x>>3) & 0xFE; //0 2 4 6 8 10 12 14
	uint8_t max_x = (fn_x > 127) ? 0x0F : (fn_x>>3);
	LCD_CS_START();
	for (uint8_t vstr = st_y; vstr <= max_y; ++vstr) {
		LCD_cmd(0x80 | vstr % 32);
		LCD_cmd(0x80 | ((vstr < 32) ? 0 : 8) | min_xh );
		for (uint8_t hstr = min_x; hstr <= max_x; ++hstr) {
			LCD_data(lcd_buffer[vstr][hstr]);
#ifdef lcd_buffer_flash_debug
			_delay_ms(15);
#endif
		}
	}
	LCD_CS_STOP();
}

typedef union {
	uint16_t ch;
	struct {
		uint8_t chl;
		uint8_t chh;
	};
} uchar;

/* адресация экрана начинается с нуля, отсутствуют проверки count_chars, координат и высоты шрифта */
void print_char(uint8_t x_pos, uint8_t y_pos, uint8_t font_height, uint8_t count_chars, const char* str) {
	uint8_t offset = x_pos & 7; // получаем смещение кратное 8
	uint8_t x_min = x_pos >> 3;
	uint8_t x_max = x_min + count_chars;
	if (x_max > 127) x_max = 127;
	uint8_t y_max = y_pos + font_height;
	uint8_t ch_code;
	uchar ch_line;
	
	
	for (int x = x_min; x < x_max; ++x) {
		ch_code = *(str);
		for (int y = y_pos, yy = 0; y < y_max; ++y, ++yy) {
			ch_line.ch = 0;
			/* читаем новое значение + делаем смещение */
			ch_line.chh = pgm_read_byte(&(Font8x8Table[ch_code][yy]));
			ch_line.ch >>= offset;
			/* применяем новое значение */
			lcd_buffer[y][x] |= ch_line.chh;
			if(offset && (x + 1) < 16) { 
				lcd_buffer[y][x + 1] |= ch_line.chl;
			}
		}
		str++;
	}
}


#endif /* LCD_H_ */