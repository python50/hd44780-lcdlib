/* 
 * File:   hd44780-lcdlib.h
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
 * Created on July 19, 2012, 2:51 PM
 */

#ifndef LCD_HD44780_H
#define	LCD_HD44780_H

/*This library will work for most displays, its just a matter of addressing*/

//Commands
#define LCDCMD_CLEAR (0x01)
#define LCDCMD_HOME (0x02)

#define LCDCMD_ADDRESS (0x80)

//Addresses
#define LCDADDR_LINE1 (0x00)
#define LCDADDR_LINE2 (0x40)

#define LCDADDR_UP      (LCDADDR_LINE1+15)
#define LCDADDR_DOWN    (LCDADDR_LINE2+15)
#define LCDADDR_POS1    (LCDADDR_LINE1+2)
#define LCDADDR_POS2    (LCDADDR_LINE2+2)

//Method of communication, Perhaps include serial some day ...
//#define LCD_USE_PORT //Use a 8bit port for data transfer
//OR
#define LCD_USE_PINS //use 8 IO pins for data transfer

//For use with LCD_USE_PORT
#define LCD_PORT (PORTB)

//For use with LCD_USE_PINS
#define LCD_D0 (RB7)
#define LCD_D1 (RB6)
#define LCD_D2 (RB5)
#define LCD_D3 (RB4)
#define LCD_D4 (RB3)
#define LCD_D5 (RB2)
#define LCD_D6 (RB1)
#define LCD_D7 (RB0)

//lcd control lines
#define LCD_EN (RC4)
#define LCD_RW (RC5)
#define LCD_RS (RC6)
#define LCD_BACKLIGHT (RC7)

void lcd_init();
void lcd_init_char();
void lcd_delay();
void lcd_command(const char data);
void lcd_address(const char address);
void lcd_write(char position, const char * s);
void lcd_write_len(char position, const char * s, char length);
void lcd_puts(const char * s,char endchar);
void lcd_put(const char s);
void lcd_pos_clear(char position, char length);

#ifdef LCD_USE_PORT
#ifdef LCD_USE_PINS
    #error "lcd-44780.h - You cannot have both 'LCD_USE_PORT' and 'LCD_USE_PINS' defined"
#endif
#endif

#ifndef LCD_USE_PORT
    #ifndef LCD_USE_PINS
        #define LCD_USE_PINS
    #endif
#endif

#ifndef LCD_USE_PINS
    #ifndef LCD_USE_PORT
        #define LCD_USE_PORT
    #endif
#endif

#endif	/* LCD_HD44780_H */

