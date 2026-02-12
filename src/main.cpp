/*
 * opg1_ny_F22.c
 *
 * Created: 01-09-2020 14:34:13
 *updated 7-02-22
 * Author : victo
 */ 

#define F_CPU 16000000UL
#define btn_pin 4
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdbool.h>

#include "setup/I2C.h"  //include library for i2c driver
#include "setup/ssd1306.h" //include display driver
void init(){
	DDRK |=0x00;
  PORTK|=0xFF;
	DDRG |=0b00100000;  //D4 as output PG5
  DDRE |=(1<<btn_pin);
  PORTE |=(1<<btn_pin);
	
}

int main(void)
{  
	init();
	
  _i2c_address = 0X78; // write address for i2c interface
  
  I2C_Init();  //initialize i2c interface to display
  InitializeDisplay(); //initialize  display
  
   print_fonts();  //for test and then exclude the  clear_display(); call
   char text[]="S256068"; //string declared before use it in sendStrXY - 15 chars long incl spaces
   clear_display();   //use this before writing you own text
  while (1)
  {      
   bool btn_state = (PINE & (1 << btn_pin)) >> btn_pin;

   unsigned char in = PINK;
   char hex_tal[3];

  /*clear_display(); */
  sprintf(hex_tal, "%02X", in);

	sendStrXY(hex_tal,4,7);  //one char  - X is line number - from 0 -7 and Y number position of the char an the line - 15 chars 
	sendStrXY(text,0,0); //line 0  -print the line of text
  
  if ((PINE & (1 << btn_pin)) == 0 ) {
    PORTG |= (1<<PG5);
  } else {
    PORTG &= ~(1<<PG5);
  }
  _delay_ms(10);
   
	  
	  }

	
  

}

