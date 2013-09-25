/*
 *    Filename: lcd1602.c
 *
 * Description:
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 下午9:37:57
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */
#include <mcs51/8052.h>
#include "lcd1602.h"

/*
 * 功能:判断液晶模块忙碌状态
 * 返回值：result result=1, 忙碌； rusult=0，不忙；
 */

__bit busy_test(void)
{
    __bit result;
    RS = 0;
    RW = 1;
    E  = 1;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    result = BF;
    E   = 0;
    return result;
}

/*
 * 功能： 将模式设置指令或显示地址写入液晶模块
 * 入口参数：dictate
 */
void write_com(uchar dictate)
{
    while(1 == busy_test());
    RS = 0;
    RW = 0;
    E = 0;
    __asm nop __endasm;
    __asm nop __endasm;
    P0 = dictate;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    E = 1;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    E = 0;
}

/*
 * 函数功能：指定字符显示的实际地址
 * 入口参数：x
 */
void write_address(uchar x)
{
    write_com(x|0x80); //显示位置的确定方法规定为"80H+地址码x"
}

/*
 *函数功能：将数据(字符的标准ASCII码)写入液晶模块
 *入口参数：y(为字符常量)
 */
void write_data(uchar y)
{
    while(busy_test()==1);
    RS=1;           //RS为高电平，RW为低电平时，可以写入数据
    RW=0;
    E=0;            //E置低电平(写指令时，，
    // 就是让E从0到1发生正跳变，所以应先置"0"
    P0=y;           //将数据送入P0口，即将数据写入液晶模块
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;       //空操作四个机器周期，给硬件反应时间
    E=1;          //E置高电平
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;//空操作四个机器周期，给硬件反应时间
    E=0;            //当E由高电平跳变成低电平时，液晶模块开始执行命令
}

/*
 * 初始化LCD
 *
 */
void init_lcd(void)
{

    delay_ms(15);             //延时15ms，首次写指令时应给LCD一段较长的反应时间
    write_com(0x38);  //显示模式设置：16×2显示，5×7点阵，8位数据接口
    delay_ms(5);   //延时5ms
    write_com(0x38);
    delay_ms(5);
    write_com(0x38); //3次写 设置模式
    delay_ms(5);
    write_com(0x0F);  //显示模式设置：显示开，有光标，光标闪烁
    delay_ms(5);
    write_com(0x06);  //显示模式设置：光标右移，字符不移
    delay_ms(5);
    write_com(0x01);  //清屏幕指令，将以前的显示内容清除
    delay_ms(5);
}

/*
 * 功能：写入一个字符串
 */
void lcd_write_string(const char *str)
{
    while(*str != '\0')
        {
            write_data(*str++);
        }
}
/*
 * 功能：清屏幕
 *
 */
void clrscr(void)
{
    write_com(0x01);
    delay_ms(5);
}

/*
 * 功能：打开显示
 */

void enable_display(void)
{
    write_com(0x0c);
    delay_ms(5);
}

/*
 * 功能：关闭显示
 */
void disable_display(void)
{
    write_com(0x08);
    delay_ms(5);
}

/*
 * 功能：显示光标并闪烁
 */
void enable_flashcursor(void)
{
    write_com(0x0f);
    delay_ms(5);
}

/*
 *功能：显示光标不闪烁
 */
void disable_flashcursor(void)
{
    write_com(0x0e);
    delay_ms(5);
}
/*
 * 功能：当读或写一个字符后地址指针加一，且光标加一
 */

void input_cursor_right_shift(void)
{
    write_com(0x06);
    delay_ms(5);
}

/*
 * 功能：当读或写一个字符后地址指针减一，且光标减一
 */
void input_cursor_left_shift(void)
{
    write_com(0x04);
    delay_ms(5);
}

/*
 * 功能：当写一个字符时，整屏显示左移
 */
void input_screen_left_shift(void)
{
    write_com(0x07);
    delay_ms(5);
}

/*
 * 功能：当写一个字符时，整屏显示右移
 */
void input_screen_right_shift(void)
{
    write_com(0x05);
    delay_ms(5);
}

/*
 * 功能：在第X行第Y列写入字符
 * 参数：x=1或2 y=1～16
 */
void goToXY(uchar x, uchar y)
{
    if (1 == x)
        {
            write_address(y);
        }
    else
        {
            write_address(0x40+y);
        }
    delay_ms(5);
}

/*
 * 功能：光标，画面归位
 */
void reset(void)
{
    write_com(0x02);
    delay_ms(5);
}

/*
 * 画面左移一个字符位
 */
void screen_left_shift(void)
{
    write_com(0x18);
    delay_ms(5);
}
/*
 * 画面右移一个字符位
 */
void screen_right_shift(void)
{
    write_com(0x1a);
    delay_ms(5);
}

/*
 * 光标右移一个字符位
 */
void cursor_right_shift(void)
{
    write_com(0x14);
    delay_ms(5);
}
/*
 * 光标左移一个字符位
 */
void cursor_left_shift(void)
{
    write_com(0x10);
    delay_ms(5);
}
