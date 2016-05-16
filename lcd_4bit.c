/* Project: lcd
 * Author:   De Backer Simon
 * info:     4-bit
 * */
#ifndef _lcd_4bit_c__
#define _lcd_4bit_c__

#ifdef __cplusplus
extern "C"{
#endif

#include <lcd_4bit.h>

/*read busy flag
 * is blijkbaar 26µs-33µs vareert
*/
void LCD_busy(void){
    lcd_DDR &= 0x0F;//set data als ingang
    lcd_port = LCD_EN|LCD_RW;
    asm ("nop");/* plaats in commend als er data verwerkt word ipv wachten */
    asm ("nop");
    /* wacht op 0b0xxx xxxx
     * men kan iets verwerken ondertussen
     * */
    do {} while ((lcd_pin&0x80));
    lcd_port =0x00;
    lcd_DDR |= 0xf0;//set data als uitgang
}
uint8_t LCD_is_not_busy(void)
{
    lcd_DDR &= 0x0F;//set data als ingang
    lcd_port = LCD_EN|LCD_RW;
    asm ("nop");
    asm ("nop");
    if(lcd_pin&0x80)
    {
        lcd_port =0x00;
        lcd_DDR |= 0xf0;//set data als uitgang

        return 0;/* busy */
    }
    lcd_port =0x00;
    lcd_DDR |= 0xf0;//set data als uitgang

    return 1;/* not busy */
}

void lcd_cmd (char cmd)
{
    lcd_port = (cmd & 0xF0)|LCD_EN;
    lcd_port = (cmd & 0xF0);
    lcd_port = ((cmd << 4) & 0xF0)|LCD_EN;
    lcd_port = ((cmd << 4) & 0xF0);
    LCD_busy();
}

void lcd_reset(void)
{
    /* set DDR */
    lcd_DDR |= 0xf0|LCD_EN|LCD_RW|LCD_RS;
    /* set PORT */
    lcd_port |= 0xf0|LCD_EN|LCD_RW|LCD_RS;
    _delay_ms(20);
    /* Initialization for 4-bit operation */
    lcd_port = 0x30+LCD_EN;
    lcd_port = 0x30;
    _delay_us(Execution_time_cmd);
    lcd_port = 0x30+LCD_EN;
    lcd_port = 0x30;
    _delay_us(Execution_time_cmd);
    lcd_port = 0x30+LCD_EN;
    lcd_port = 0x30;
    _delay_us(Execution_time_cmd);
    /* Enable 4-Bit Mode */
    lcd_port = 0x20+LCD_EN;
    lcd_port = 0x20;
    _delay_us(Execution_time_cmd);
}

void lcd_init (void)
{
    lcd_reset();         // Call LCD reset lcd_cmd(0×28);

    /* poll the Busy Flag => ok */

    // 4-bit mode – 2 line – 5×7 font.
    lcd_cmd(0x0C);       // Display no cursor – no blink.
    lcd_cmd(0x06);       // Automatic Increment – No Display shift.
    lcd_cmd(0x80);       // Address DDRAM with 0 offset 80h.
}

// Function to display single Character
void lcd_data (unsigned char dat)
{
    lcd_port = ((dat & 0xF0)|LCD_EN|LCD_RS);
    lcd_port = ((dat & 0xF0)|LCD_RS);
    lcd_port = (((dat << 4) & 0xF0)|LCD_EN|LCD_RS);
    lcd_port = (((dat << 4) & 0xF0)|LCD_RS);
    LCD_busy();
}
// Function to display a String
void lcd_puts(char *a)
{
    unsigned int i;
    for(i=0;a[i]!=0;i++)
        lcd_data(a[i]);
}
void lcd_value_int(uint8_t var)
{
    char temp[10];
    itoa(var,temp,10);
    lcd_puts(temp);
}

void lcd_setCursor(uint8_t LCD_row,uint8_t LCD_col)
{
#if(LCD_rows==4)
    static uint8_t LCD_row_offsets[4]= { 0x00, 0x40, 0x14, 0x54 };
#elif(LCD_rows==3)
    static uint8_t LCD_row_offsets[3]= { 0x00, 0x40, 0x14 };
#elif(LCD_rows==2)
    static uint8_t LCD_row_offsets[2]= { 0x00, 0x40 };
#elif(LCD_rows==1)
    static uint8_t LCD_row_offsets[1]= { 0x00 };
#else
#error no LCD_rows define
#endif
    lcd_cmd(0x80 | (LCD_col + LCD_row_offsets[LCD_row]));
}
void lcd_clear()
{
    lcd_cmd(0x01); // Clear screen
}
/* Input:
 *     location: location where you want to store
 *               0,1,2,....7
 *     ptr: Pointer to pattern data
 *
 * Usage:
 *     pattern[8]={0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
 *     LCD_build(1,pattern);
 *
 * LCD Ports are same as discussed in previous sections */
void LCD_build(unsigned char location, unsigned char *ptr)
{
      unsigned char i;
      if(location<8)
      {
          lcd_cmd(0x40+(location*8));
          for(i=0;i<8;i++)
             lcd_data(ptr[ i ]);
      }
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
