/*
 *    Filename: calc.c
 *
 * Description:
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-19 下午6:55:18
 *      Author: 胡震宇
 *   CopyRight: GPL v3
 *    Revision:
 *
 */
#include "calc.h"
#include "key.h"

long INPUTA, INPUTB, RESULT; //两个输入，一个输出
unsigned char fuhao = 0, flag = 0; //fuhao表示按下的运算符类型，flag表示是否有运算符按下

const char *DBZ = "Divided by zero!";
const char *ERR = "Error!";

//
///****************************************
//
//功能：求正弦值
//角度: 4096 <==> 360度
// ****************************************/
//#define GUI_90DEG   1024
///***************************************
//
//正弦表（0～90度）
//角度 : 90度16等分  数值  : 放大1024倍
// ****************************************/
//
//__code const unsigned int aSin[] = {
//
//        0,       /* 1/16 *90? */
//
//        100,     /* 1/16 *90? */
//
//        200,     /* 2/16 *90? */
//
//        297,     /* 3/16 *90? */
//
//        392,     /* 4/16 *90? */
//
//        483,     /* 5/16 *90? */
//
//        569,     /* 6/16 *90? */
//
//        650,     /* 7/16 *90? */
//
//        724,     /* 8/16 *90? */
//
//        792,     /* 9/16 *90? */
//
//        851,     /* 10/16 *90?*/
//
//        903,     /* 11/16 *90?*/
//
//        946,     /* 12/16 *90?*/
//
//        980,     /* 13/16 *90?*/
//
//        1004,    /* 14/16 *90?*/
//
//        1019,    /* 15/16 *90?*/
//
//        1024     /* 16/16 *90?*/
//
//};
//
//
//
//
//
//int GUI_sin(int angle) {
//    char IsNeg =0;
//    int i;
//    unsigned int Faktor;
//    unsigned long  t;
//    angle &= ((1<<12)-1);  /* reduce to 0-360 degrees */
//
//    if (angle> 2* GUI_90DEG) {
//            angle -= 2* GUI_90DEG;
//            IsNeg =1;
//    }
//    if (angle> GUI_90DEG) {  /* between 90-180 */
//            angle = 2*GUI_90DEG-angle;   /* use sine symetry */
//    }
//
//    /* 通过以上工作把 angle 转到 0～90度（0～1024）*/
//
//    i = angle>>6;         //<==>i = angle/64 ,64 = 1024/16
//    {
//        Faktor = (unsigned int )((1<<6)-(angle&((1<<6)-1)));//<==>Faktor = 64-(angle-(angle/64)*64);
//        t = aSin*(unsigned long)Faktor;
//        if (Faktor !=(1<<6)) {
//                t += aSin[i+1]*((1<<6)-Faktor);
//        }
//    }
//
//    t = (t+(1<<5)) >>6;   /* divide,incl. rounding */
//    return (IsNeg) ? 0-t : t;
//}
//
//
//

/*
 * 功能：初始化计算器变量
 */

void
calc_init(void)
{
    INPUTA = INPUTB = RESULT = 0;
    flag = 0;
    fuhao = 0;
    goToXY(1, 1);
}

void
calc(void)
{
    uchar key, i = 0;
    key = scanKeyToInt();
    if (key == NO_KEY_PRESSED)
        return; //如果没有按键按下，直接返回
    if (key == CE)
        {
            clrscr();
            calc_init();
            return;
        } // 当按下清零键
    if (key == SQR)
        {
            if (flag != 1)
                {
                    RESULT = INPUTA * INPUTA;
                    write_data('^');
                    write_data('2');
                    goToXY(2, 15);
                    input_cursor_left_shift();
                    while (RESULT != 0)
                        {
                            write_data(0x30 + RESULT % 10);
                            RESULT /= 10;
                        }
                    write_data('=');
                    calc_init();
                }
            else
                {
                    clrscr();
                    goToXY(1, 1);
                    lcd_write_string(ERR);
                    calc_init();
                    return;
                }
        } //按下平方键

    //        if (key == SIN)
    //            {
    //                if(flag != 1)
    //                    {
    //                        clrscr();
    //                        screen_left_shift();
    //                        lcd_write_string("sin(");
    //                        while(INPUTA != 0)
    //                            {
    //                                write_data(0x30 + INPUTA %10);
    //                                INPUTA /= 10;
    //                            }
    //                        write_data(')');
    //
    //                        RESULT = (long) sinf((float) INPUTA);
    //
    //                        while(RESULT != 0)
    //                            {
    //
    //                                write_data(0x30 + RESULT %10);
    //                                RESULT /= 10;
    //                            }
    //                        write_data('=');
    //                        calc_init();
    //                        return ;
    //                    }
    //                else
    //                    {
    //                        clrscr();
    //                        goToXY(1,1);
    //                        lcd_write_string(ERR);
    //                        calc_init();
    //                        return;
    //                    }
    //            }

    if (key == PLUS)
        {
            if (flag != 1)
                {
                    fuhao = PLUS;
                    write_data('+');
                    flag = 1;
                    return;
                }
            else
                {
                    clrscr();
                    goToXY(1, 1);
                    lcd_write_string(ERR);
                    calc_init();
                    return;
                }
        } //当按下加号
    if (key == MINUS)
        {
            if (flag != 1)
                {
                    fuhao = MINUS;
                    write_data('-');
                    flag = 1;
                    return;
                }
            else
                {
                    clrscr();
                    goToXY(1, 1);
                    lcd_write_string(ERR);
                    calc_init();
                    return;
                }
        } // 当按下减号
    if (key == MULTI)
        {
            if (flag != 1)
                {
                    fuhao = MULTI;
                    write_data('*');
                    flag = 1;
                    return;
                }
            else
                {
                    clrscr();
                    goToXY(1, 1);
                    lcd_write_string(ERR);
                    calc_init();
                    return;
                }
        } // 当按下乘号
    if (key == DIVID)
        {
            fuhao = DIVID;
            write_data('/');
            flag = 1;
            return;
        }  //当按下除号
    if (key == EQUAL)
        {
            if (flag != 1)
                {
                    goToXY(2, 15);
                    input_cursor_left_shift();
                    while (INPUTA != 0)
                        {
                            write_data(0x30 + INPUTA % 10);
                            INPUTA /= 10;
                        }
                    write_data('=');
                } //如果之前没有按过运算符，则输出第一个数
            switch (fuhao)
                {
                case PLUS:
                    input_cursor_left_shift();
                    goToXY(2, 15);
                    RESULT = INPUTA + INPUTB;

                    while (RESULT != 0)
                        {

                            write_data(0x30 + RESULT % 10);
                            RESULT /= 10;
                        }
                    write_data('=');
                    calc_init();
                    goToXY(1, 1);
                    break;
                case MINUS:

                    if ((INPUTA - INPUTB) > 0)
                        RESULT = INPUTA - INPUTB;
                    else
                        RESULT = INPUTB - INPUTA;

                    input_cursor_left_shift();
                    goToXY(2, 15);
                    while (RESULT != 0)
                        {

                            write_data(0x30 + RESULT % 10);
                            RESULT /= 10;
                        }
                    if ((INPUTA - INPUTB) < 0)
                        write_data('-');
                    write_data('=');
                    calc_init();
                    goToXY(1, 1);
                    break;
                case MULTI:
                    RESULT = INPUTA * INPUTB;
                    goToXY(2, 15);
                    input_cursor_left_shift();
                    while (RESULT != 0)
                        {
                            write_data(0x30 + RESULT % 10);
                            RESULT /= 10;
                        }
                    write_data('=');
                    calc_init();
                    goToXY(1, 1);
                    break;
                case DIVID:
                    if (0 == INPUTB)
                        {
                            clrscr();
                            goToXY(1, 1);
                            lcd_write_string(DBZ);
                            calc_init();
                            return;
                        } //  如果除数为0 ，报错

                    RESULT = (long) (((float) INPUTA / INPUTB) * 1000);

                    goToXY(2, 15);
                    input_cursor_left_shift();
                    while (RESULT != 0)
                        {

                            write_data(0x30 + RESULT % 10);
                            RESULT /= 10;
                            i++;
                            if (3 == i)
                                write_data('.');
                        }

                    if ((INPUTA / INPUTB) <= 0)
                        write_data('0');
                    write_data('=');
                    calc_init();
                    break;
                } // 判断运算符类型，计算结果并输出结果
            flag = 0;

            return;
        } // 按下等号键

    if (flag == 0)
        {
            INPUTA = INPUTA * 10 + key;
        }
    if (1 == flag)
        {
            INPUTB = INPUTB * 10 + key;
        }

    switch (key)
        {
        case 0:
            write_data('0');
            break;
        case 1:
            write_data('1');
            break;
        case 2:
            write_data('2');
            break;
        case 3:
            write_data('3');
            break;
        case 4:
            write_data('4');
            break;
        case 5:
            write_data('5');
            break;
        case 6:
            write_data('6');
            break;
        case 7:
            write_data('7');
            break;
        case 8:
            write_data('8');
            break;
        case 9:
            write_data('9');
            break;
        }
}
