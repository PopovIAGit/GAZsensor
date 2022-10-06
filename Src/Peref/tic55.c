#include "peref.h"
#include "main.h"
                  
unsigned int Buffer[8] = {0,0,0,0,0,0,0,0}; 

unsigned int code[] = 
{ 
   444,         //  0 
   12,          //  1 
   472,         //  2 
   348,         //  3 
   108,         //  4 
   372,         //  5 
   500,         //  6 
   28,          //  7 
   508,         //  8 
   380,         //  9 
   0,           //  10 blank 
   252,         //  A     
   484,         //  b
   432,         //  C
   460,         //  d
   496,         //  E
   240,         //  F
   436,         //  G
   236,         //  H 
   160,	        //  I
   268,         //  J
   244,         //  K
   416,         //  L
   148,         // M
   196,	        // n
   248,		// P
   124,		// q
   192,         // r 
   372,		// S
   480,		// t
   428,		// U
   388,		// u
   296,		// W
   364,		// Y
   408,		// Z
   188,		// P (Rus)
   120,         //  "*"
   64,          //  -
   452,         //  o
   2,           // .
   
}; 

void tic_control_on(){
	HAL_GPIO_WritePin (LCD_SPI_MOSI_GPIO_Port, LCD_SPI_MOSI_Pin, 0);
	HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 0);
	HAL_GPIO_WritePin (LCD_LOAD_GPIO_Port, LCD_LOAD_Pin, 0);
}

void tic_control_off(){
	HAL_GPIO_WritePin (LCD_SPI_MOSI_GPIO_Port, LCD_SPI_MOSI_Pin, 1);
	HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 1);
	HAL_GPIO_WritePin (LCD_LOAD_GPIO_Port, LCD_LOAD_Pin, 1);
}
void tic_print_symbol(int Data, unsigned char Pos)
{
        Buffer[Pos] = Data; 
        tic_send();
}

void tic_print_num (unsigned int Num, unsigned char Pos, char dot, char set)
{
  char i = 0;
 if  (dot) i = i+1;
 if  (set) i = i+2;
  
        Buffer[Pos] = code[Num]+i; 
        tic_send();
} 

unsigned char num[8];
unsigned char  i = 0;

void tic_print_numful (unsigned int Num, unsigned char Pos)
{
  do
  {
    num[i]=Num%10;
    i++;
    Num /= 10;
  }
  while (Num != 0);
  while(i!=0)
  {
  //  tic_print_num(num[i-1], Pos++,0,0);
    Buffer[Pos++] = code[num[i-1]];
    i--;
  }
  tic_send();
} 

void tic_print_time (void)
{

  Buffer[0] = 480; //d
  Buffer[1] = 0;
  Buffer[2] = code[Time.Hours/10]; 
  Buffer[3] = code[Time.Hours%10]+1; 
  Buffer[4] = code[Time.Minutes/10]; 
  Buffer[5] = code[Time.Minutes%10]+1; 
  Buffer[6] = code[Time.Seconds/10]; 
  Buffer[7] = code[Time.Seconds%10]; 
    
  tic_send();
}

void tic_print_date (RTC_DateTypeDef *date)
{
  Buffer[0] = 460; //t
  Buffer[1] = 0;
  Buffer[2] = code[date->Date/10]; 
  Buffer[3] = code[date->Date%10]+1; 
  Buffer[4] = code[date->Month/10]; 
  Buffer[5] = code[date->Month%10]+1; 
  Buffer[6] = code[date->Year/10]; 
  Buffer[7] = code[date->Year%10]; 
  
  tic_send();
}

void tic_print_char(unsigned char Char, unsigned char Pos, char dot, char set)
{
	tic_set_char(Char, Pos, dot, set);
	tic_send();
}

void tic_clear(void)
{
	unsigned char c;
	for (c=0;c<9;c++)Buffer[c] = 0;
	tic_send();
}         

void tic_set_char(unsigned char Data, unsigned char Pos, char dot, char set) 
{
    char i = 0;
 if  (dot) i = i+1;
 if  (set) i = i+2;
  
    // Buffer[Pos] = code[Data - 54];  
    Buffer[Pos] = code[Data-54]+i;  
}

      


void tic_send(void)
{   
char b, c;  
for (c=0;c<9;c++)
    { 
		HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 1);
		
		HAL_GPIO_WritePin (LCD_SPI_MOSI_GPIO_Port, LCD_SPI_MOSI_Pin, 0);
		
		HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 1);
		
		//HAL_Delay (1);
			
		HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 0);

    }       
for (b=9;b>0;b--)
    {  
    for (c=0;c<9;c++)
        { 
				HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 1);	
					
                                HAL_GPIO_WritePin (LCD_SPI_MOSI_GPIO_Port, LCD_SPI_MOSI_Pin, 0x01 & (Buffer[b-1] >> c));

				HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 1);
		
				//HAL_Delay (1);
			
				HAL_GPIO_WritePin (LCD_SPI_SCK_GPIO_Port, LCD_SPI_SCK_Pin, 0);
        } 
    }     
				HAL_GPIO_WritePin (LCD_LOAD_GPIO_Port, LCD_LOAD_Pin, 1);
		
				//HAL_Delay (1);
			
				HAL_GPIO_WritePin (LCD_LOAD_GPIO_Port, LCD_LOAD_Pin, 0);
}
/*-------------------------------*/
