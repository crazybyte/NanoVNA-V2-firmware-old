#pragma once

#include <stdint.h>

#define RGB565(b,r,g)     ( (((b)<<8)&0xfc00) | (((r)<<2)&0x03e0) | (((g)>>3)&0x001f) )

typedef struct {
	uint16_t width;
	uint16_t height;
	uint16_t scaley;
	uint16_t slide;
	const uint32_t *bitmap;
} font_t;

extern const font_t NF20x24;


extern uint16_t spi_buffer[1024];

void ili9341_init(void);
void ili9341_test(int mode);
void ili9341_bulk(int x, int y, int w, int h);
void ili9341_line(int, int, int, int, int);
void ili9341_fill(int x, int y, int w, int h, int color);
void ili9341_drawchar_5x7(uint8_t ch, int x, int y, uint16_t fg, uint16_t bg);
void ili9341_drawstring_5x7(const char *str, int x, int y, uint16_t fg, uint16_t bg);
void ili9341_drawchar_size(uint8_t ch, int x, int y, uint16_t fg, uint16_t bg, uint8_t size);
void ili9341_drawstring_size(const char *str, int x, int y, uint16_t fg, uint16_t bg, uint8_t size);
void ili9341_drawfont(uint8_t ch, const font_t *font, int x, int y, uint16_t fg, uint16_t bg);
void ili9341_read_memory(int x, int y, int w, int h, int len, uint16_t* out);
void ili9341_read_memory_continue(int len, uint16_t* out);
