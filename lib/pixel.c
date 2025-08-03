#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pixel.h"

// INITIALIZE FUNCTIONS
int makeBrightness(t_brightness *brightness, t_dpoint vision, char *scale)
{
	if (!scale || vision.x < 0 || vision.y < 0)
	{
		memset(brightness, 0, sizeof(*brightness));
		return 0;
	}
	brightness->vision = vision;
	brightness->range = strlen(scale);
	brightness->scale = scale;
	return 0;
}

t_brightness createBrightness(t_dpoint vision, char *scale)
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
int getBrightness(int luminosity, t_brightness brightness, t_ray ray)
{
	if (!brightness.scale)
		return ' ';
	if (ray.dist.dir == HORIZ)
		luminosity = round((double) brightness.vision.x / ray.len * luminosity);
	else
		luminosity = round((double) brightness.vision.y / ray.len * luminosity);
	if (luminosity >= brightness.range)
		luminosity = brightness.range-1;
	else if (luminosity < 0)
		luminosity = 0;
	return brightness.scale[luminosity];
}
