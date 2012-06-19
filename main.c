#include <msp430.h>
#include <stdint.h>
#include "lcd.h"

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;
	DCOCTL = CALDCO_8MHZ;
	BCSCTL1 = CALBC1_8MHZ;

  lcd_init();
  lcd_go_line(1);
  lcd_writeln("Hello");
  lcd_go_line(2);
  lcd_writeln("World");
  _BIS_SR(LPM3_bits);
	while (1) {}
	return 0;
}
