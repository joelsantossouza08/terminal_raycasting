#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

// INITIALIZE FUNCTIONS
void freeScreen(t_screen screen)
{
	if (!screen.pixels)
		return;
	while (screen.width--)
		if (screen.pixels[screen.width] != 0)
		{
			free(screen.pixels[screen.width]);
			screen.pixels[screen.width] = 0;
		}
	free(screen.pixels);
	screen.pixels = 0;
	return;
}

int makeScreen(t_screen *screen, unsigned int width, unsigned int height)
{
	screen->width = width;
	screen->height = height;
	screen->pixels = width ? calloc(width, sizeof(t_pixel*)) : 0;
	if (!screen->pixels)
		return 0;
	if (height)
		while (width--)
		{
			screen->pixels[width] = calloc(height, sizeof(t_pixel));
			if (!screen->pixels[width])
			{
				freeScreen(*screen);
				return 0;
			}
		}
	return 1;
}

t_screen createScreen(unsigned int width, unsigned int height)
{
	t_screen screen;

	makeScreen(&screen, width, height);
	return screen;
}

// DISPLAY
void printScreen(t_screen screen)
{
	t_point p;

	if (!screen.pixels)
		return;
	system("clear");
	p.y = screen.height;
	while (--p.y >= 0 && (p.x = -1))
	{
		while (++p.x < screen.width)
			printPixel(screen.pixels[p.x][p.y]);
		printf("\n");
	}
	return;
}
