#ifndef PIXEL_H
#define PIXEL_H

#define MAX_SCALE 100

#define RESET		"\e[0m"
#define WHITE 	"\e[0;37m"
#define BLACK 	"\e[0;30m"
#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"
#define YELLOW	"\e[0;33m"
#define BLUE		"\e[0;34m"
#define PURPLE	"\e[0;35m"
#define CYAN		"\e[0;36m"

typedef struct
{
	int 	vision;
	int		size;
	char	scale[MAX_SCALE];
} t_brightness;

typedef struct
{
	char *color;
	char luminosity;
} t_pixel;

int						makeBrightness(t_brightness *brightness, unsigned int vision, char *scale);
t_brightness	createBrightness(unsigned int vision, char *scale);

void					makePixel(t_pixel *pixel, char *color, char luminosity);
t_pixel				createPixel(char *color, char luminosity);

void					printPixel(t_pixel pixel);

#endif
