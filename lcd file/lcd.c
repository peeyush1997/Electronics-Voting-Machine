#include	<lpc214x.h>
#include	"lcdHeader.h"

void lcd_init(void)
{
	IODIR0 = LCD;
	lcd_cmd(0x38);		// 8-bit, 2Line
	lcd_cmd(0x0e);		//Display	on , Cursor ON	
	lcd_cmd(0x01);		// Clear LCD
	lcd_cmd(0x80);		//Set cursor to 1st line 1st pos
}
void lcd_cmd(char c)
{
	//IOPIN0 = (c << 15);
	IOPIN0 = ((IOPIN0 & 0xff807fff) | (c << 15));
	IOCLR0 = RS;
	IOCLR0 = RW;
	IOSET0 = EN;
	delay(50);
	IOCLR0 = EN;
}
void lcd_str(char *s)
{
	while(*s != '\0')
	{
		lcd_data(*s);
		s++;
	}
}
void lcd_data(char c)
{
	//IOPIN0 = (c << 15);
	IOPIN0 = ((IOPIN0 & 0xff807fff) | (c << 15));
	IOSET0 = RS;
	IOCLR0 = RW;
	IOSET0 = EN;
	delay(50);
	IOCLR0 = EN;
}

void lcd_num(unsigned int n)
{
	if(n)
	{
		lcd_num(n / 10);
		lcd_data((n % 10) + 0x30);
	}
}	 


void delay(int ct)
{
	int i , j;
	for(i = 0; i < 5000; i++)
	{
		for(j = 0; j < ct; j++)
		{
		}
	}
}

void lcd_clr(  )
{
	lcd_cmd(0x01);
}
