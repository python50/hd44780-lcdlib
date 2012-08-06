/* 
 * File:   hd44780-lcdlib.c
 * Author: Jason White <Jason@JSWhite.net>
 * License: Modified BSD License
 *
 *  Version: 1.0
 *  Release Date: 08/06/2012
 *  Copyright 2012 (C) Jason White <Jason@JSWhite.net> 
 *  White Waters Software
 *
 *  http://www.github.com/python50/hd44780-lcdlib
 *
 * Created on July 19, 2012, 2:52 PM
 */

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "hd44780-lcdlib.h"

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

void lcd_init()
{
    LCD_RS=0;
    lcd_command(0x30);
    lcd_command(0x30);
    lcd_command(0x30);
    lcd_command(0x38);
    lcd_command(0x10);
    lcd_command(0x0C);
    lcd_command(0x06);

    lcd_command(LCDCMD_CLEAR);
    lcd_command(LCDCMD_HOME);

    LCD_BACKLIGHT=1;

    lcd_init_char();
}

void lcd_init_char()
{
    lcd_command(0x40);
    LCD_RS=1;

    /*char database at http://www.quinapalus.com/hd44780udg.html*/
    lcd_command(0x0); //char0 - up
    lcd_command(0x0);
    lcd_command(0x4);
    lcd_command(0xe);
    lcd_command(0x1f);
    lcd_command(0x0);
    lcd_command(0x0);
    lcd_command(0x0);

    lcd_command(0x0); //char1 - down
    lcd_command(0x0);
    lcd_command(0x1f);
    lcd_command(0xe);
    lcd_command(0x4);
    lcd_command(0x0);
    lcd_command(0x0);
    lcd_command(0x0);

    lcd_command(0x2); //char2 - left
    lcd_command(0x6);
    lcd_command(0xa);
    lcd_command(0x12);
    lcd_command(0xa);
    lcd_command(0x6);
    lcd_command(0x2);
    lcd_command(0x0);

    lcd_command(0x8); //char3 - right
    lcd_command(0xc);
    lcd_command(0xa);
    lcd_command(0x9);
    lcd_command(0xa);
    lcd_command(0xc);
    lcd_command(0x8);
    lcd_command(0x0);

    lcd_command(0x0); //char4 - X
    lcd_command(0x1b);
    lcd_command(0xe);
    lcd_command(0x4);
    lcd_command(0xe);
    lcd_command(0x1b);
    lcd_command(0x0);
    lcd_command(0x0);

    lcd_command(0x0); //char5 - Check
    lcd_command(0x2);
    lcd_command(0x3);
    lcd_command(0x16);
    lcd_command(0x1c);
    lcd_command(0x8);
    lcd_command(0x0);
    lcd_command(0x0);

    lcd_command(0x1); //char6 - Speaker
    lcd_command(0x3);
    lcd_command(0xf);
    lcd_command(0xf);
    lcd_command(0xf);
    lcd_command(0x3);
    lcd_command(0x1);
    lcd_command(0x0);
    
    lcd_command(0x2); //char7 - Music note
    lcd_command(0x3);
    lcd_command(0x2);
    lcd_command(0x2);
    lcd_command(0xe);
    lcd_command(0x1e);
    lcd_command(0xc);
    lcd_command(0x0);
    LCD_RS=0;
}

void lcd_delay()
{
   for(char i=1;i!=0;i++);
}

void lcd_command(const char data)
{
    LCD_RW=0;

#ifdef LCD_USE_PORT
    LCD_PORT=data;
    asm("nop");
    LCD_EN=1;
    lcd_delay();
    LCD_EN=0;
#endif

#ifdef LCD_USE_PINS
    LCD_EN=0;
    LCD_D0=0;
    LCD_D1=0;
    LCD_D2=0;
    LCD_D3=0;
    LCD_D4=0;
    LCD_D5=0;
    LCD_D6=0;
    LCD_D7=0;

    if (data&0x1)
        LCD_D0=1;
    if (data&0x2)
        LCD_D1=1;
    if (data&0x4)
        LCD_D2=1;
    if (data&0x8)
        LCD_D3=1;
    if (data&0x10)
        LCD_D4=1;
    if (data&0x20)
        LCD_D5=1;
    if (data&0x40)
        LCD_D6=1;
    if (data&0x80)
        LCD_D7=1;
    asm("nop");
    LCD_EN=1;
    lcd_delay();
    LCD_EN=0;
#endif
}

void lcd_address(const char address)
{
    lcd_command(LCDCMD_ADDRESS+address);
}

void lcd_write(char position, const char * s)
{
    lcd_address(position);
    lcd_puts(s,0);
}

void lcd_write_len(char position, const char * s, char length)
{
    lcd_address(position);
    for(char i=0;i!=length;i++)
    {
        lcd_put(*s);
        s++;
    }
}

void lcd_puts(const char * s,char endchar)
{
    LCD_RS=1;

    while (*s!=endchar)
    {
        lcd_command(*s++);
    }

    LCD_RS=0;
}

void lcd_put(const char s)
{
    LCD_RS=1;

    lcd_command(s);

    LCD_RS=0;
}

void lcd_pos_clear(char position, char length)
{
    lcd_address(position);
    for (char i=0;i < length;i++)
        lcd_put(' ');
}
