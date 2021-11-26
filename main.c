/*
 * atmel_gcc_lcd_st7920_spi_hw.c
 *
 * Created: 11.11.2021 16:18:50
 * Author : Dmitry
 */ 
#include "config.h"
#include "lcd.h"

//#define lcd_buffer_flash_debug 1

int main(void) {
	LCD_init();
	while (1) {
// 		/* Test 1 */
// 		for (uint8_t vstr = 0; vstr <= 63; ++vstr) {
// 			for (uint8_t hstr = 0; hstr <= 15; ++hstr) {
// 				if((vstr+hstr)&0x01) lcd_buffer[vstr][hstr] = 0;
// 				else lcd_buffer[vstr][hstr] = 0xff;
// 			}
// 		}
// 		LCD_buffer_flash(0,0,128,64);
		//_delay_ms(1000);
		/* Test 2 */
// 		for (uint8_t vstr = 0; vstr <= 63; ++vstr) {
// 			for (uint8_t hstr = 0; hstr <= 15; ++hstr) {
// 				if((vstr+hstr)&0x01) lcd_buffer[vstr][hstr] = 0xff;
// 				else lcd_buffer[vstr][hstr] = 0;
// 			}
// 		}
// 		LCD_buffer_flash(0,0,128,64);
// 		_delay_ms(1000);
// 		/* Test 3 */
// 		LCD_clean(0xff);
// 		LCD_buffer_flash(0,0,128,64);
// 		_delay_ms(1000);
// 		/* Test 4 */
// 		LCD_clean(0);
// 		LCD_buffer_flash(0,0,31,31);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(32,32,63,63);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(64,0,95,31);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(96,32,127,63);
// 		_delay_ms(1000);
// 		/* Test 5 */
// 		LCD_buffer_flash(0, 0, 128, 64);
// 		LCD_clean(0xff);
// 		LCD_buffer_flash(0,0,31,31);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(32,32,63,63);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(64,0,95,31);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(96,32,127,63);
// 		_delay_ms(1000);


// 		/* Test 6 */
// 		LCD_clean(0);
// 		LCD_buffer_flash(0,0,128,64);
// 		_delay_ms(1000);
// 		LCD_clean(0xff);
// 		/* first  - обновление первого байта в паре, второй не затрагивает */
// 		LCD_buffer_flash(0,0,1,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(16,0,17,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(32,0,33,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(48,0,49,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(64,0,65,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(80,0,81,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(96,0,97,7);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(112,0,114,7);
// 		_delay_ms(1000);
// 		/* second - обновление второго байта в паре вызывает обновление первого и второго байта */
// 		LCD_buffer_flash(8,16,15,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(24,16,25,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(40,16,44,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(56,16,60,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(72,16,73,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(88,16,89,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(104,16,110,23);
// 		_delay_ms(1000);
// 		LCD_buffer_flash(120,16,127,23);
// 		_delay_ms(1000);
	
		for(int i=0; i < 32; i+=2) {
			LCD_clean(0);
			print_char(i, i, 8, 5, "¬низ!");
			LCD_buffer_flash(0,0,128,64);
			_delay_ms(500);		
		}
		for(int i=31; i >= 0; i-=2) {
			LCD_clean(0);
			print_char(i, i, 8, 5, "¬верх!");
			LCD_buffer_flash(0,0,128,64);
			_delay_ms(500);
		}
    }
}
