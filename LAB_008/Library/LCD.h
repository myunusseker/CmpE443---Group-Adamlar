#ifndef LCD_H
#define LCD_H

#include "GPIO.h"
#include "Wait.h"

#define RS_PORT			PORT0
#define RS_MASK			((uint32_t) 1 << 8)

#define RW_PORT			PORT0
#define RW_MASK			((uint32_t) 1 << 6)

#define EN_PORT			PORT0
#define EN_MASK			((uint32_t) 1 << 7)

#define DATA0_PORT	PORT0
#define DATA0_MASK	((uint32_t) 1 << 24)

#define DATA1_PORT	PORT0
#define DATA1_MASK	((uint32_t) 1 << 25)

#define DATA2_PORT	PORT0
#define DATA2_MASK	((uint32_t) 1 << 26)

#define DATA3_PORT	PORT1
#define DATA3_MASK	((uint32_t) 1 << 30)

void LCD_Init(void);

void LCD_command(uint8_t data);

void LCD_data(uint8_t data);
void LCD_write(char* data);

void LCD_toogle(void);

void LCD_clearDisplay(void);
void LCD_clearDisplayWithoutRAM(void);
void LCD_cursorON(void);
void LCD_cursorOFF(void);
void LCD_cursorBlinking(void);
void LCD_cursorAutoIncrement(void);
void LCD_shiftLeft(void);
void LCD_shiftRight(void);
void LCD_moveCursorLeft(void);
void LCD_moveCursorRight(void);
void LCD_setCursorHome(void);

void LCD_setCursorPositionFirstLine(uint8_t position);
void LCD_setCursorPositionSecondLine(uint8_t position);

#endif
