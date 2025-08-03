#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include "point.h"

#define EMPTY		0
#define WALL		1
#define PLAYER	2
#define CAMERA 	3
#define RAY			4
#define HORIZ_GRID	5
#define VERT_GRID		6
#define CORNER_GRID	7

#define CHR_EMPTY		'.'
#define CHR_WALL		'#'
#define CHR_PLAYER	'@'
#define CHR_CAMERA	'>'
#define CHR_RAY			'*'
#define CHR_HORIZ_GRID	'_'
#define CHR_VERT_GRID		'|'
#define CHR_CORNER_GRID	'+'

typedef struct
{
	int width;
	int height;
	int tilesize;
	int **data;
} t_map;

int		inMapLimit(t_point point, t_map map);
int		isElement(t_point point, int element, t_map map);

int		makeMap(t_map *map, unsigned int width, unsigned int height, unsigned int tilesize);
t_map createMap(unsigned int width, unsigned int height, unsigned int tilesize);
int		importMap(t_map *map, unsigned int tilesize, char *filePath, size_t bufsize);

void	freeMap(t_map map);
void	printMap(t_map map);

void	putPoint(t_point point, t_map map, int element);
void 	putPointSize(t_point point, int size, t_map map, int element);
void	clrPoint(t_point point, t_map map);
void	clrPointSize(t_point point, int size, t_map map);

void	putLine(t_point p1, t_point p2, t_map map, int element);

void	putGrid(int width, int height, t_map map);
void	clrGrid(int width, int height, t_map map);

void	clrMap(t_map map);

void	makeZoom(t_map *zoomed, t_map map, double zoom, t_point center);

#endif
