/* Project: lcd
 * Author:   De Backer Simon
 * info:     4-bit
 * */
#ifndef _lcd_4bit_h__
#define _lcd_4bit_h__

#ifdef __cplusplus
extern "C"{
#endif

#define F_CPU 14745600UL // 14745600 Hz clock speed

#include <avr/io.h>
#ifdef F_CPU
#include <util/delay.h>
#else
#error no F_CPU include lcd_4bit.h
#endif
#include <stdlib.h>

#define LCD_rows    4   /*LCD_row 1, 2, 3 or 4 */

#define lcd_pin     PINA
#define lcd_DDR     DDRA
#define lcd_port    PORTA

/* LCD_RS 0 command / 1 write data */
#define LCD_RS     0x01 //pin 0

/* LCD_RW lees 1 / Write 0 */
#define LCD_RW     0x02 //pin 1

/* LCD_EN Starts data read/write. */
#define LCD_EN     0x04 //pin 2

#define Execution_time_cmd     500 //is in µs

/* TBA: Entry mode set */
#define LCD_left         0x04
#define LCD_left_diplay  0x05
#define LCD_right        0x06
#define LCD_right_diplay 0x07

void LCD_busy(void);
uint8_t LCD_is_not_busy(void);/* te testen */
void lcd_cmd (char cmd);
void lcd_reset(void);
void lcd_init (void);
// Function to display single Character
void lcd_data (unsigned char dat);
// Function to display a String
void lcd_puts(char *a);
void lcd_value_int(uint8_t var);
void lcd_setCursor(uint8_t LCD_row,uint8_t LCD_col);/* set DDRAM address */
void lcd_clear(); /* Clear screen */
void lcd_Return_home();/* Return home */
void lcd_shift_display(uint8_t mode);/* TBA: Entry mode set */
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
void LCD_build(unsigned char location, unsigned char *ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
