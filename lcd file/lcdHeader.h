#ifndef		LCDH_H
#define 	LCDH_H

#define	EN		(1 << 10)
#define	RW		(1 << 12)
#define	RS		(1 << 13)
#define	DATA	(0xffff << 15)
#define LCD		EN | RW | RS | DATA

void lcd_init(void);
void lcd_cmd(char);
void lcd_data(char);
void lcd_str(char *);
void lcd_num(unsigned int);
void delay(int );
void lcd_clr(void);

#endif
