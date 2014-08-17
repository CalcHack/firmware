#ifndef GFX_2D_H
#define GFX_2D_H

#include "linkport.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"

typedef struct{
uint8_t width;
uint8_t height;
uint8_t chardata[130][5];
}font_5x7; 






typedef struct {
float x;
float y;
}point;




void gfx_2d_clear(void);
void gfx_2d_pixel(int x, int y, int color);
void gfx_2d_character(int character, int x, int y, int textcolor, int backgroundcolor);
void gfx_2d_string(char string[], int length, int x, int y, int textcolor, int backgroundcolor);
void gfx_2d_line(int x0, int y0, int x1, int y1, int color);
void gfx_2d_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);
void gfx_2d_rectangle(int x0, int y0, int x1, int y1, int color);
void gfx_2d_fill_rectangle(int x0, int y0, int x1, int y1, int color);
void gfx_2d_fill_triangle(point point1, point point2, point point3, int color);



#endif