/*
 * atmel_gcc_lcd_st7920_spi_hw.c
 *
 * Created: 11.11.2021 16:18:50
 * Author : Dmitry
 */ 
#include "config.h"
#include "lcd.h"

static const char string_init[] PROGMEM = {
	//0b00110110,	// Extended function set + graphic display on
	0b00000110,		// Entry mode set, increased cursor	0b0000_01{I/D}{S}
	//0b00000001,		// Display clear
	0b00000010,		// Display home
	0b00001100		// Display on, cursor on and blink off 0b0000_1{d}{c}{b}
};

static const char string_family[] PROGMEM = "Ksusha and Dima!";
static const char string_hello[] PROGMEM =  "Hello world!-_-";

int main(void) {
	CPU_init();
	SPI_init();
	LCD_send(LCD_CMD, string_init, 3);
	LCD_send(LCD_DATA, string_family, 16);
	LCD_send(LCD_DATA, string_hello, 15);
		
    while (1) { _delay_us(1); }
}
