/*
 *    Filename: delay.c
 *
 * Description: ÑÓÊ±º¯Êý
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 ÏÂÎç9:42:30
*      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */
#include "delay.h"

void delay1ms(void)
{
    uchar i,j;
    for(i = 10; i > 0; i--)
        for(j=33; j > 0; j--);
}

void delay_ms(uchar n)
{
    uchar i;
    for(i = 0; i < n; i++)
        delay1ms();
}


