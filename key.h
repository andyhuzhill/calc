/*
 *    Filename: key.h
 *
 * Description: ����ɨ�����
 *     Version: 1.0
 *    Compiler: sdcc
 *     Created: 2012-5-18 ����9:46:46
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */

#ifndef KEY_H_
#define KEY_H_

#include <mcs51/8052.h>
#include "delay.h"

#define KEY_PORT P2  //������̽���P2��

/*
 * ����20������
 * ������4����������
 * 4X4�����󰴼� P2��
 */

// �ĸ����������ֱ����P1.3��P1.4��P1.5,P1.6��
__sbit __at(0x93) KEY_A;
__sbit __at(0x94) KEY_B;
__sbit __at(0x95) KEY_C;
__sbit __at(0x96) KEY_D;

#define NO_KEY_PRESSED 55

#define PLUS  56
#define MINUS 57
#define MULTI 58
#define DIVID 59
#define EQUAL 60
#define CE    61

#define SIN 62
#define COS 63
#define SQR 64
#define POINT 65

#define NAN   99

uchar scanKey();
uchar scanKeyToInt();

#endif /* KEY_H_ */
