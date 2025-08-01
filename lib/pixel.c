#include <stdio.h>
#include <string.h>
#include "pixel.h"

// INITIALIZE FUNCTIONS
int makeBrightness(t_brightness *brightness, unsigned int vision, char *scale)
{
	if (!scale)
	{
		memset(brightness, 0, sizeof(*brightness));
		return 0;
	}
	brightness->vision = vision;
	brightness->range = strlen(scale);
	brightness->scale = scale;
	return 0;
}

t_brightness createBrightness(unsigned int vision, char *scale)
{
	t_brightness brightness;

	makeBrightness(&brightness, vision, scale);
	return brightness;
}

void makePixel(t_pixel *pixel, char *color, char luminosity)
{
	pixel->color = color;
	pixel->luminosity = luminosity;
	return;
}

t_pixel createPixel(char *color, char luminosity)
{
	t_pixel pixel;

	makePixel(&pixel, color, luminosity);
	return pixel;
}

// DISPLAY
void printPixel(t_pixel pixel)
{
	printf("%s%c%s", pixel.color, pixel.luminosity, RESET);
	return;
}

// GET
int getBrightness(int luminosity, t_brightness brightness, int dist)
{
	if (!brightness.scale)
		return ' ';
	luminosity *= brightness.vision / dist;	
	if (luminosity >= brightness.range)
		luminosity = brightness.range-1;
	else if (luminosity < 0)
		luminosity = 0;
	return brightness.scale[luminosity];
}
