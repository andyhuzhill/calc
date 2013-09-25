/*
 *    Filename: lcd1602.c
 *
 * Description:
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 ����9:37:57
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
 * ����:�ж�Һ��ģ��æµ״̬
 * ����ֵ��result result=1, æµ�� rusult=0����æ��
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
 * ���ܣ� ��ģʽ����ָ�����ʾ��ַд��Һ��ģ��
 * ��ڲ�����dictate
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
 * �������ܣ�ָ���ַ���ʾ��ʵ�ʵ�ַ
 * ��ڲ�����x
 */
void write_address(uchar x)
{
    write_com(x|0x80); //��ʾλ�õ�ȷ�������涨Ϊ"80H+��ַ��x"
}

/*
 *�������ܣ�������(�ַ��ı�׼ASCII��)д��Һ��ģ��
 *��ڲ�����y(Ϊ�ַ�����)
 */
void write_data(uchar y)
{
    while(busy_test()==1);
    RS=1;           //RSΪ�ߵ�ƽ��RWΪ�͵�ƽʱ������д������
    RW=0;
    E=0;            //E�õ͵�ƽ(дָ��ʱ����
    // ������E��0��1���������䣬����Ӧ����"0"
    P0=y;           //����������P0�ڣ���������д��Һ��ģ��
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;       //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
    E=1;          //E�øߵ�ƽ
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;
    __asm nop __endasm;//�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
    E=0;            //��E�ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ�鿪ʼִ������
}

/*
 * ��ʼ��LCD
 *
 */
void init_lcd(void)
{

    delay_ms(15);             //��ʱ15ms���״�дָ��ʱӦ��LCDһ�νϳ��ķ�Ӧʱ��
    write_com(0x38);  //��ʾģʽ���ã�16��2��ʾ��5��7����8λ���ݽӿ�
    delay_ms(5);   //��ʱ5ms
    write_com(0x38);
    delay_ms(5);
    write_com(0x38); //3��д ����ģʽ
    delay_ms(5);
    write_com(0x0F);  //��ʾģʽ���ã���ʾ�����й�꣬�����˸
    delay_ms(5);
    write_com(0x06);  //��ʾģʽ���ã�������ƣ��ַ�����
    delay_ms(5);
    write_com(0x01);  //����Ļָ�����ǰ����ʾ�������
    delay_ms(5);
}

/*
 * ���ܣ�д��һ���ַ���
 */
void lcd_write_string(const char *str)
{
    while(*str != '\0')
        {
            write_data(*str++);
        }
}
/*
 * ���ܣ�����Ļ
 *
 */
void clrscr(void)
{
    write_com(0x01);
    delay_ms(5);
}

/*
 * ���ܣ�����ʾ
 */

void enable_display(void)
{
    write_com(0x0c);
    delay_ms(5);
}

/*
 * ���ܣ��ر���ʾ
 */
void disable_display(void)
{
    write_com(0x08);
    delay_ms(5);
}

/*
 * ���ܣ���ʾ��겢��˸
 */
void enable_flashcursor(void)
{
    write_com(0x0f);
    delay_ms(5);
}

/*
 *���ܣ���ʾ��겻��˸
 */
void disable_flashcursor(void)
{
    write_com(0x0e);
    delay_ms(5);
}
/*
 * ���ܣ�������дһ���ַ����ַָ���һ���ҹ���һ
 */

void input_cursor_right_shift(void)
{
    write_com(0x06);
    delay_ms(5);
}

/*
 * ���ܣ�������дһ���ַ����ַָ���һ���ҹ���һ
 */
void input_cursor_left_shift(void)
{
    write_com(0x04);
    delay_ms(5);
}

/*
 * ���ܣ���дһ���ַ�ʱ��������ʾ����
 */
void input_screen_left_shift(void)
{
    write_com(0x07);
    delay_ms(5);
}

/*
 * ���ܣ���дһ���ַ�ʱ��������ʾ����
 */
void input_screen_right_shift(void)
{
    write_com(0x05);
    delay_ms(5);
}

/*
 * ���ܣ��ڵ�X�е�Y��д���ַ�
 * ������x=1��2 y=1��16
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
 * ���ܣ���꣬�����λ
 */
void reset(void)
{
    write_com(0x02);
    delay_ms(5);
}

/*
 * ��������һ���ַ�λ
 */
void screen_left_shift(void)
{
    write_com(0x18);
    delay_ms(5);
}
/*
 * ��������һ���ַ�λ
 */
void screen_right_shift(void)
{
    write_com(0x1a);
    delay_ms(5);
}

/*
 * �������һ���ַ�λ
 */
void cursor_right_shift(void)
{
    write_com(0x14);
    delay_ms(5);
}
/*
 * �������һ���ַ�λ
 */
void cursor_left_shift(void)
{
    write_com(0x10);
    delay_ms(5);
}
