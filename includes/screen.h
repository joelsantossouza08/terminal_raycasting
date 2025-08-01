#ifndef SCREEN_H
#define SCREEN_H

#include "pixel.h"
#include "point.h"

typedef struct
{
	int				width;
	int				height;
	t_pixel **pixels;
} t_screen;

void			freeScreen(t_screen screen);
int				makeScreen(t_screen *screen, unsigned int width, unsigned int height);
t_screen	createScreen(unsigned int width, unsigned int height);

void			printScreen(t_screen screen);

#endif
