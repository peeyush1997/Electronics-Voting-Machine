#include	<lpc214x.h>
#include	"lcdHeader.h"
#include	<string.h>

#define Buzzer	(1 << 25)
#define Row_all ((1 << 17)|(1 << 18)|(1 << 19)|(1 << 20))
#define Col_all	((1 << 21)|(1 << 22)|(1 << 23)|(1 << 24))

void row(void);
void count(void);
void ext_init(void)__irq;
void Interrupt_Init(void);

int BJP_Sarkar = 0;
int Congress_Party = 0;
int Aam_Aadmi_Party = 0;
int Samajwadi_Party = 0;

int main(){
	
	int c;
	//unsigned char str[] = "Welcome to Voating Machine";
	IODIR0 |= Buzzer;
	lcd_init();
	Interrupt_Init();
	lcd_str("Welcome to");
	lcd_cmd(0xc0);
	lcd_str("Voating Machine");
	delay(300);
	lcd_clr();
	
	while(1){
		
		IODIR0 |= Row_all;
		IOCLR0 |= Row_all;
		c = IOPIN1 & Col_all;
		if(c != Col_all){
			if(c == 0x01C00000){
				delay(100);
				row();
			}
			if(c == 0x1A00000){
				delay(100);
				count();
			}
		}
		
	}	
}

void row(){
	int r;
	char str1[] = "BJP Sarkar";
	char str2[] = "Congress Party";
	char str3[] = "Aam Aadmi Party";
	char str4[] = "Samajwadi Party";
	
	IODIR0 |= Col_all;
	IOCLR0 |= Col_all;
	r = IOPIN1 & Row_all;
	if(r != Row_all)
	{
		if(r == 0x001C0000)
		{
			lcd_cmd(0x80);
			lcd_str(str1);
			BJP_Sarkar++;
		}
		if(r == 0x001A0000)
		{
			lcd_cmd(0x80);
			lcd_str(str2);
			Congress_Party++;
		}
		if(r == 0x00160000)
		{
			lcd_cmd(0x80);
			lcd_str(str3);
			Aam_Aadmi_Party++;
		}
		if(r == 0x000E0000)
		{
			lcd_cmd(0x80);
			lcd_str(str4);
			Samajwadi_Party++;
		}
	}
	
}

void count(){
	char str1[] = "BJP Won";
	char str2[] = "Congress Party Won";
	char str3[] = "Aam Aadmi Party Won";
	char str4[] = "Samajwadi Party Won";
	char str5[] = " Tie";
	char str6[] = " Congratulation";
	
	lcd_clr();
	if((BJP_Sarkar>Congress_Party)&&(BJP_Sarkar>Aam_Aadmi_Party)&&(BJP_Sarkar>Samajwadi_Party)){
		lcd_cmd(0x80);
		lcd_str(str1);
		lcd_cmd(0xc0);
		lcd_str(str6);	
	}
	else if((Congress_Party>BJP_Sarkar)&&(Congress_Party>Aam_Aadmi_Party)&&(Congress_Party>Samajwadi_Party)){
		lcd_cmd(0x80);
		lcd_str(str2);
		lcd_cmd(0xc0);
		lcd_str(str6);	
	}
	else if((Aam_Aadmi_Party>Congress_Party)&&(Aam_Aadmi_Party>BJP_Sarkar)&&(Aam_Aadmi_Party>Samajwadi_Party)){
		lcd_cmd(0x80);
		lcd_str(str3);
		lcd_cmd(0xc0);
		lcd_str(str6);	
	}
	else if((Samajwadi_Party>Congress_Party)&&(Samajwadi_Party>Aam_Aadmi_Party)&&(Samajwadi_Party>BJP_Sarkar)){
		lcd_cmd(0x80);
		lcd_str(str4);
		lcd_cmd(0xc0);
		lcd_str(str6);	
	}
	else{
		lcd_cmd(0x80);
		lcd_str(str5);
	}
	
lcd_clr();
	
lcd_cmd(0x80);				//Set DDRAM address or coursor position on display(0x80 + Address)
lcd_str("BJP Sarkar : ");
lcd_data(BJP_Sarkar+0x30);
	
lcd_cmd(0xc0);
lcd_str("Congress Party : ");
lcd_data(Congress_Party+0x30);
	
lcd_cmd(0x88);
lcd_str("Aam Aadmi Party : ");
lcd_data(Aam_Aadmi_Party+0x30);
	
lcd_cmd(0xc8);
lcd_str("Samajwadi Party : ");
lcd_data(Samajwadi_Party+0x30);
		
}
void Interrupt_Init()
{
  
	PINSEL0 |= (1 << 29);
	PINSEL0 &= (1 << 28);	

	VICIntSelect &= (1 << 15); 	
	VICIntEnable = (1 << 15);	

	VICVectCntl0 = 15 | (1 << 5);
	VICVectAddr0 = (long)ext_init;

	EXTMODE = (1 << 1);		
	EXTPOLAR = (1 << 1);
}
void ext_init(void)__irq
{
	IOSET0 |= Buzzer;
 	delay(50);
 	IOCLR0 |= Buzzer;
 	delay(50);
 	EXTINT |= (1 << 1);
 	VICVectAddr = 0;
}
