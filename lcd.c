#include <msp430.h>
#include <stdint.h>
#include "lcd_config.h"
#include "lcd.h"

#if LCD_FCPU == 8000000
	#define LCD_US_DELAY_CYCLES 8
	#define LCD_MS_DELAY_CYCLES 8000
#elif LCD_FCPU == 16000000
	#define LCD_US_DELAY_CYCLES 16
	#define LCD_MS_DELAY_CYCLES 16000
#else
	#define LCD_US_DELAY_CYCLES 1
	#define LCD_MS_DELAY_CYCLES 1000
#endif

uint8_t lcd_pins[4] = {LCD_D4, LCD_D5, LCD_D6, LCD_D7};

void lcd_delay_ms(uint16_t t) {
  uint16_t i;
	for (i = 0; i < t; i++) {
		__delay_cycles(LCD_MS_DELAY_CYCLES);
	}
}

void lcd_delay_us(uint16_t t) {
  uint16_t i;
	for (i = 0; i < t; i++){
		__delay_cycles(LCD_US_DELAY_CYCLES);
	}
}

void lcd_send4(uint8_t data) {
	uint8_t i;
  LCD_PORT |= LCD_EN;
	for (i = 0; i < 4; i++) {
		if (data & (1 << i)){
			LCD_PORT |= lcd_pins[i];
		} else {
			LCD_PORT &= ~lcd_pins[i];
		}
	}
  lcd_delay_us(1);
  LCD_PORT &= ~LCD_EN;
  LCD_PORT &= ~(LCD_DATA_PINS);
  lcd_delay_us(1);
}

void lcd_send(uint8_t cmd, uint8_t data) {
  LCD_PORT &= ~(LCD_RS | LCD_EN | LCD_DATA_PINS);

  if (cmd & LCD_DATA) {
    LCD_PORT |= LCD_RS;
  }

  lcd_send4(data >> 4);

  if (cmd & LCD_CMD) {
    lcd_delay_ms(5);
  } else {
    lcd_delay_us(1);
  }

  lcd_send4(data & 0x0F);

  if (cmd & LCD_DATA) {
    LCD_PORT &= ~LCD_RS;
  }

  lcd_delay_us(200);
}

void lcd_char(uint8_t data) {
  lcd_send(LCD_DATA, data);
}

void lcd_cmd(uint8_t data) {
  lcd_send(LCD_CMD, data);
}

uint8_t lcd_write(const char *str) {
  uint8_t i = 0;
  while (*str) {
    lcd_char(*str++);
    i++;
  }
  return i;
}

void lcd_writeln(const char *str) {
  uint8_t i = lcd_write(str);
	while(i++ < LCD_COLUMNS) {
		lcd_char(' ');
	}
}

void lcd_init(void) {
  LCD_DIR |= LCD_RS | LCD_EN | LCD_DATA_PINS;
  LCD_PORT &= ~(LCD_RS | LCD_EN | LCD_DATA_PINS);

  lcd_delay_ms(20); // give lcd time to startup

  lcd_send4(0x03);
  lcd_delay_ms(5);

  if (LCD_MODE == LCD_MODE_4) {
    lcd_send4(0x02);
    lcd_delay_us(37);
  }

  lcd_cmd(0x28);
  lcd_cmd(0x01);
  lcd_cmd(0x06);
  lcd_delay_us(1200);
  lcd_cmd(0x0C);
}

void lcd_go(uint8_t row, uint8_t col) {
  if (row == 4) {
    lcd_cmd(LCD_LINE_4 + col);
	} else if (row == 3) {
    lcd_cmd(LCD_LINE_3 + col);
	} else if (row == 2) {
    lcd_cmd(LCD_LINE_2 + col);
	} else {
    lcd_cmd(LCD_LINE_1 + col);
  }
}

void lcd_go_line(uint8_t line) {
  lcd_go(line, 0);
}

