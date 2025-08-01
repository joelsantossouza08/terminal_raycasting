#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int makeScreen(t_screen *screen, unsigned int width, unsigned int height, double fov, t_brightness brightness)
{
	screen->width = width;
	screen->height = height;
	screen->planeDist = width / 2 / tan(fov);
	screen->brightness = brightness;
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

t_screen createScreen(unsigned int width, unsigned int height, double fov, t_brightness brightness)
{
	t_screen screen;

	makeScreen(&screen, width, height, fov, brightness);
	return screen;
}

// UTILS
int inScreenLimit(t_point point, t_screen screen)
{
	return point.x >= 0 && point.x < screen.width && point.y >= 0 && point.y < screen.height;
}

// INTERACT WITH SCREEN
void putPixel(t_point point, t_screen screen, t_pixel pixel)
{
	if (screen.pixels && inScreenLimit(point, screen))
		screen.pixels[point.x][point.y] = pixel;
	return;
}

void clrPixel(t_point point, t_screen screen)
{
	if (screen.pixels && inScreenLimit(point, screen))
	{
		screen.pixels[point.x][point.y].color = NOCOLOR;
		screen.pixels[point.x][point.y].luminosity = ' ';
	}
	return;
}

void putPixelLine(t_point p1, t_point p2, t_screen screen, t_pixel pixel)
{
	t_vector dir;
	t_dpoint step;
	double angle;
	int len;
	int i;

	if (!screen.pixels)
		return;
	dir = createVector(p1, p2);
	angle = atan2(dir.y, dir.x);
	step = createDPoint(cos(angle), sin(angle));
	len = sqrt(SQUARE(dir.y) + SQUARE(dir.x));
	i = -1;
	while (++i < len)
	{
		p2.x = p1.x + step.x * i;
		p2.y = p1.y + step.y * i;
		putPixel(p2, screen, pixel);
	}
	return;
}

void clrScreen(t_screen screen)
{
	t_point p;

	p.y = screen.height;
	while (--p.y >= 0 && (p.x = -1))
		while (++p.x < screen.width)
			clrPixel(p, screen);
	return;
}

// RENDER 3D MAP
void make3DVision(t_camera camera, t_screen screen, unsigned int wallHeight, int luminosity)
{
	t_point line;
	t_point p1;
	t_point p2;
	t_pixel pixel;
	int i;

	if (!screen.pixels || !camera.rays || camera.nrays > screen.width)
		return;
	clrScreen(screen);
	line.x = screen.width / camera.nrays;
	while (camera.nrays--)
	{
		line.y = round((double) wallHeight / camera.rays[camera.nrays].len * screen.planeDist);
		pixel = createPixel(BLUE, getBrightness(luminosity, screen.brightness, camera.rays[camera.nrays].len));
		p1.y = screen.height / 2 - line.y / 2;
		p2.y = p1.y + line.y;
		i = -1;
		while (++i < line.x)
		{
			p1.x = p2.x = screen.width--;
			putPixelLine(p1, p2, screen, pixel);
		}
	}
	return;
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
