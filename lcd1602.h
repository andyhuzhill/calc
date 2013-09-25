/*
 *    Filename: lcd1602.h
 *
 * Description: 显示器控制程序
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 下午9:47:14
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */

#ifndef LCD1602_H_
#define LCD1602_H_

#include "delay.h"

//#define DEBUG

/*
 * lcd1602接在单片机的P0口
 * 三根控制线 RS接在 P1.0 R/W接在P1.1 E 接在P1.2
 * P0.7定义为忙碌标志位
 */

__sbit __at(0x90) RS;
__sbit __at(0x91) RW;
__sbit __at(0x92) E;
__sbit __at(0x87) BF;

__bit busy_test(void);
void write_com(uchar dictate);
void write_address(uchar x);
void write_data(uchar y);
void init_lcd(void);

void lcd_write_string(char *str);

void clrscr(void);
void enable_display(void);
void disable_display(void);
void enable_flashcursor(void);
void disable_flashcursor(void);
void cursor_left_shift(void);
void cursor_right_shift(void);
void screen_left_shift(void);
void screen_right_shift(void);
void input_cursor_left_shift(void);
void input_cursor_right_shift(void);
void input_screen_right_shift(void);
void input_screen_left_shift(void);

void goToXY(uchar x, uchar y);

#endif /* LCD1602_H_ */
