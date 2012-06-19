#ifndef __LCD_H__
#define __LCD_H__
#include "lcd_config.h"

#ifndef LCD_PORT
	#error "LCD_PORT not defined!"
#endif

#ifndef LCD_DIR
	#error "LCD_DIR not defined!"
#endif

#ifndef LCD_RS
	#error "LCD_RS not defined!"
#endif

#ifndef LCD_EN
	#error "LCD_EN not defined!"
#endif

#ifndef LCD_D4
	#error "LCD_D4 not defined!"
#endif

#ifndef LCD_D5
	#error "LCD_D5 not defined!"
#endif

#ifndef LCD_D6
	#error "LCD_D6 not defined!"
#endif

#ifndef LCD_D7
	#error "LCD_D7 not defined!"
#endif

#ifndef LCD_COLUMNS
#define LCD_COLUMNS 16
#endif

#ifndef LCD_ROWS
#define LCD_ROWS 2
#endif

#define LCD_MODE_4 4

#ifndef LCD_MODE
#define LCD_MODE LCD_MODE_4
#endif

#define LCD_DATA_PINS LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7
#define LCD_CMD 0
#define LCD_DATA 1

#define LCD_HOME 0x80
#define LCD_LINE_1 LCD_HOME
#define LCD_LINE_2 LCD_HOME + 0x40
#define LCD_LINE_3 LCD_HOME + 0x60
#define LCD_LINE_4 LCD_HOME + 0x20

void lcd_init(void);
void lcd_writeln(const char *str);
uint8_t lcd_write(const char *str);
void lcd_go(uint8_t row, uint8_t col);
void lcd_go_line(uint8_t line);
void lcd_delay_ms(uint16_t t);
void lcd_delay_us(uint16_t t);
#endif // __LCD_H__
