#ifndef SCREEN_H
#define SCREEN_H

#include "pixel.h"
#include "point.h"
#include "camera.h"

typedef struct
{
	int						width;
	int						height;
	int 					planeDist;
	t_pixel				**pixels;
	t_brightness	brightness;
} t_screen;

void			freeScreen(t_screen screen);
int				makeScreen(t_screen *screen, unsigned int width, unsigned int height, double fov, t_brightness brightness);
t_screen	createScreen(unsigned int width, unsigned int height, double fov, t_brightness brightness);

void			putPixel(t_point point, t_screen screen, t_pixel pixel);
void			clrPixel(t_point point, t_screen screen);
void			putPixelLine(t_point p1, t_point p2, t_screen screen, t_pixel pixel);

void			make3DVision(t_camera camera, t_screen screen, unsigned int wallHeight, int luminosity);

void			printScreen(t_screen screen);

#endif
