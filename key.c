/*
 *    Filename: key.c
 *
 * Description: ����ɨ�����
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 ����9:24:38
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */


#include "key.h"
/*
 * ����ɨ���Ӻ���
 */
uchar scanKey()
{
    unsigned char temp;
#ifndef DEBUG
    if (0 == KEY_A)
        {
            delay_ms(15);
            if (0 == KEY_A)
                {
                    while(!KEY_A);
                    return 16;
                }
        }
    if (0 == KEY_B)
        {
            delay_ms(15);
            if (0 == KEY_B)
                {
                    while(!KEY_B);
                    return 17;
                }
        }

    if (0 == KEY_C)
        {
            delay_ms(15);
            if (0 == KEY_C)
                {
                    while(!KEY_C);
                    return 18;
                }
        }

    if (0 == KEY_D)
        {
            delay_ms(15);
            if (0 == KEY_D)
                {
                    while(!KEY_D);
                    return 19;
                }
        }
    //    �ȼ���������
#endif

KEY_PORT=0xff; //����P1��д1���˿ڶ�״̬
KEY_PORT=0xf0;

temp=KEY_PORT;
if(temp!=0xf0)
    {
        delay_ms(15);
        if(temp!=0xf0)
            {
                KEY_PORT=0xfe;
                temp=KEY_PORT;
                switch(temp)
                {
                    case(0xee):while(KEY_PORT == temp);return(0);break;
                    case(0xde):while(KEY_PORT == temp);return(1);break;
                    case(0xbe):while(KEY_PORT == temp);return(2);break;
                    case(0x7e):while(KEY_PORT == temp);return(3);break;
                    default:
                                         break;
                }

                KEY_PORT=0xfd;
                temp=KEY_PORT;
                switch(temp)
                {
                    case(0xed):while(KEY_PORT == temp);return(4);break;
                    case(0xdd):while(KEY_PORT == temp);return(5);break;
                    case(0xbd):while(KEY_PORT == temp);return(6);break;
                    case(0x7d):while(KEY_PORT == temp);return(7);break;
                    default:
                                         break;
                }

                KEY_PORT=0xfb;
                temp=KEY_PORT;
                switch(temp)
                {
                    case(0xeb):while(KEY_PORT == temp);return(8);break;
                    case(0xdb):while(KEY_PORT == temp);return(9);break;
                    case(0xbb):while(KEY_PORT == temp);return(10);break;
                    case(0x7b):while(KEY_PORT == temp);return(11);break;
                    default:
                                         break;
                }

                KEY_PORT=0xf7;
                temp=KEY_PORT;
                switch(temp)
                {
                    case(0xe7):while(KEY_PORT == temp);return(12);break;
                    case(0xd7):while(KEY_PORT == temp);return(13);break;
                    case(0xb7):while(KEY_PORT == temp);return(14);break;
                    case(0x77):while(KEY_PORT == temp);return(15);break;
                    default:
                        break;
                }
            }
    }
else
    return NO_KEY_PRESSED;
}

/*
 * ���ܣ� ������ת��Ϊʵ������
 */
uchar  scanKeyToInt()
{
    unsigned char key;
    key = scanKey();
    if (NO_KEY_PRESSED == key) return NO_KEY_PRESSED;
    switch(key)
    {
        case 0: return DIVID; break;
        case 1: return MULTI; break;
        case 2: return MINUS; break;
        case 3: return PLUS;  break;
        case 4: return 9; break;
        case 5: return 6; break;
        case 6: return 3; break;
        case 7: return EQUAL; break;
        case 8: return 8; break;
        case 9: return 5; break;
        case 10: return 2; break;
        case 11: return 0; break;
        case 12: return 7; break;
        case 13: return 4; break;
        case 14: return 1; break;
        case 15: return CE; break;
        case 16: return SQR; break;
        case 17: return SIN; break;
        case 18: return COS; break;
        case 19: return CE; break;
        default:
            return NAN; break;
    }
}
