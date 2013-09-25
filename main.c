/*
 *    Filename: main.c
 *
 * Description: 单片机计算器主程序
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 下午9:23:22
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
#include "calc.h"

void main(void)
{
    init_lcd();
    delay_ms(10);
    screen_left_shift();
    goToXY(1,1);
    while(1)
        {
            calc();
        }
}
