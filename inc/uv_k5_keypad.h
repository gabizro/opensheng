#ifndef __UV_K5_KEYPAD_
#define __UV_K5_KEYPAD_

#include "uv_k5_pinout.h"

/*
Keypad
	GND		A10		A11		A12		A13

A3	23(fnup)10(menu)11 (up)	12 (dn)	13 (Exit)

A4	22(fndn)1		2		3		14

A5			4		5		6		0

A6			7		8		9		15


C5	PTT		21
*/

#define KEYPAD_KEY_0		0
#define KEYPAD_KEY_1		1
#define KEYPAD_KEY_2		2
#define KEYPAD_KEY_3		3
#define KEYPAD_KEY_4		4
#define KEYPAD_KEY_5		5
#define KEYPAD_KEY_6		6
#define KEYPAD_KEY_7		7
#define KEYPAD_KEY_8		8
#define KEYPAD_KEY_9		9
#define KEYPAD_KEY_MENU		10
#define KEYPAD_KEY_UP		11
#define KEYPAD_KEY_DOWN		12
#define KEYPAD_KEY_EXIT		13
#define KEYPAD_KEY_ASTERISK	14
#define KEYPAD_KEY_F		15
#define KEYPAD_KEY_PTT		21
#define KEYPAD_KEY_F2		21
#define KEYPAD_KEY_F1		23

const PROGMEM int8_t[] UVK5_KEYPAD_COL_PINS = {-1, UVK5_KEYPAD_COL_0_PIN, UVK5_KEYPAD_COL_1_PIN, UVK5_KEYPAD_COL_2_PIN, UVK5_KEYPAD_COL_3_PIN};
const PROGMEM int8_t[] UVK5_KEYPAD_ROW_PINS = {UVK5_KEYPAD_ROW_0_PIN, UVK5_KEYPAD_ROW_1_PIN, UVK5_KEYPAD_ROW_2_PIN, UVK5_KEYPAD_ROW_3_PIN};

#endif
