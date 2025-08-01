#ifndef SCREEN_H
#define SCREEN_H

#include "pixel.h"

typedef struct
{
	int				width;
	int				height;
	t_pixel **pixels;
} t_screen;

#endif
