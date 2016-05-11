/* Project: lcd
 * Author:   De Backer Simon
 * info:     4-bit
 * */
#ifndef _lcd_h__
#define _lcd_h__

#ifdef __cplusplus
extern "C"{
#endif

#define F_CPU 14745600UL // 14745600 Hz clock speed

#include <avr/io.h>
#ifdef F_CPU
#include <util/delay.h>
#endif
#include <stdlib.h>

#define LCD_4x20   //LCD_4x20 or LCD_2x20_16

#define lcd_pin   PINA //LCD connected to PORTB as shown above
#define lcd_DDR   DDRA //LCD connected to PORTB as shown above
#define lcd_port   PORTA //LCD connected to PORTB as shown above
//LCD_RS 0 command / 1 write data
#define LCD_RS     0x01 //pin 0
//LCD_RW lees 1 / Write 0
#define LCD_RW     0x02 //pin 1
#define LCD_EN     0x04 //pin 2
#define Execution_time_clear_display     2 //is in ms
#define Execution_time_cmd     100 //is in µs

void LCD_busy(void);
void lcd_cmd (char cmd);
void lcd_reset(void);
void lcd_init (void);
// Function to display single Character
void lcd_data (unsigned char dat);
// Function to display a String
void lcd_puts(char *a);//ok
void lcd_value_int(uint8_t var);
void lcd_setCursor(uint8_t LCD_row,uint8_t LCD_col);//ok
void lcd_clear();//ok
//Input:
//     location: location where you want to store
//               0,1,2,....7
//     ptr: Pointer to pattern data
//
//Usage:
//     pattern[8]={0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
//     LCD_build(1,pattern);
//
//LCD Ports are same as discussed in previous sections
void LCD_build(unsigned char location, unsigned char *ptr);// ok

#ifdef __cplusplus
} // extern "C"
#endif

#endif
