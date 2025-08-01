#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "map.h"

// UTILS FUNCTIONS
int inMapLimit(t_point point, t_map map)
{
	return point.x >= 0 && point.x < map.width && point.y >= 0 && point.y < map.height;
}

int isElement(t_point point, int element, t_map map)
{
	if (!inMapLimit(point, map))
		return -1;
	return map.data[point.x][point.y] == element;
}

// INITIALIZE FUNCTIONS
void freeMap(t_map map)
{
	if (!map.data)
		return;
	while (map.width--)
		if (map.data[map.width] != 0)
		{
			free(map.data[map.width]);
			map.data[map.width] = 0;
		}
	free(map.data);
	map.data = 0;
	return;
}

int makeMap(t_map *map, unsigned int width, unsigned int height, unsigned int tilesize)
{
	width *= tilesize;
	height *= tilesize;
	map->width = width;
	map->height = height;
	map->tilesize = tilesize;
	map->data = width ? calloc(width, sizeof(int*)) : 0;
	if (!map->data)
		return 0;
	if (height)
		while (width--)
		{
			map->data[width] = calloc(height, sizeof(int));
			if (!map->data[width])
			{
				freeMap(*map);
				return 0;
			}
		}
	return 1;
}

t_map createMap(unsigned int width, unsigned int height, unsigned int tilesize)
{
	t_map map;

	makeMap(&map, width, height, tilesize);
	return map;
}

void printMap(t_map map)
{
	t_point p;

	if (!map.data)
		return;
	system("clear");
	p.y = map.height;
	while (--p.y >= 0 && (p.x = -1))
	{
		while (++p.x < map.width)
		{
			if (map.data[p.x][p.y] == EMPTY)
				printf("%c ", CHR_EMPTY);
			else if (map.data[p.x][p.y] == WALL)
				printf("%c ", CHR_WALL);
			else if (map.data[p.x][p.y] == PLAYER)
				printf("%c ", CHR_PLAYER);
			else if (map.data[p.x][p.y] == CAMERA)
				printf("%c ", CHR_CAMERA);
			else if (map.data[p.x][p.y] == RAY)
				printf("%c ", CHR_RAY);
			else if (map.data[p.x][p.y] == HORIZ_GRID)
				printf("%c ", CHR_HORIZ_GRID);
			else if (map.data[p.x][p.y] == VERT_GRID)
				printf("%c ", CHR_VERT_GRID);
			else if (map.data[p.x][p.y] == CORNER_GRID)
				printf("%c ", CHR_CORNER_GRID);
		}
		printf("\n");
	}
	return;
}

// ADD ELEMENT TO MAP
void putPoint(t_point point, t_map map, int element)
{
	if (map.data && inMapLimit(point, map))
		map.data[point.x][point.y] = element;
	return;
}

void putPointSize(t_point point, int size, t_map map, int element)
{
	t_point p;

	p.x = -1;
	while (++p.x <= size && (p.y = -1))
			while (++p.y <= size)
				putPoint(createSumPoints(point, p), map, element);
	return;
}

void clrPoint(t_point point, t_map map)
{
	if (map.data && inMapLimit(point, map))
		map.data[point.x][point.y] = EMPTY;
	return;
}

void clrPointSize(t_point point, int size, t_map map)
{
	t_point p;

	p.x = -1;
	while (++p.x <= size && (p.y = -1))
			while (++p.y <= size)
				clrPoint(createSumPoints(point, p), map);
	return;
}

void putLine(t_point p1, t_point p2, t_map map, int element)
{
	t_vector dir;
	t_dpoint step;
	double angle;
	int len;
	int i;

	if (!map.data)
		return;
	dir	= createVector(p1, p2);
	angle = atan2(dir.y, dir.x);
	step = createDPoint(cos(angle), sin(angle));
	len = sqrt(SQUARE(dir.y) + SQUARE(dir.x));
	i = -1;
	while (++i < len)
	{
		p2.x = p1.x + step.x * i;
		p2.y = p1.y + step.y * i;
		if (!isElement(p2, WALL, map))
			putPoint(p2, map, element);
	}
	return;
}

void putGrid(int width, int height, t_map map)
{
	t_point p;

	p.y = map.height;
	while (p.y >= 0 && (p.x = -1))
	{
		while (++p.x < map.width)
			if (isElement(p, EMPTY, map) && p.x % width)
				putPoint(p, map, HORIZ_GRID);
		p.y -= height;
	}
	p.x = map.width;
	while (p.x >= 0 && (p.y = -1))
	{
		while (++p.y < map.height)
			if (isElement(p, EMPTY, map))
			{
				if (p.y % height)
					putPoint(p, map, VERT_GRID);
				else
					putPoint(p, map, CORNER_GRID);
			}
		p.x -= width;
	}
	return;
}

void clrGrid(int width, int height, t_map map)
{
	t_point p;

	p.y = map.height;
	while (p.y >= 0 && (p.x = -1))
	{
		while (++p.x < map.width)
			if (isElement(p, EMPTY, map) && p.x % width)
				clrPoint(p, map);
		p.y -= height;
	}
	p.x = map.width;
	while (p.x >= 0 && (p.y = -1))
	{
		while (++p.y < map.height)
			if (isElement(p, EMPTY, map) && p.y % height)
				clrPoint(p, map);
		p.x -= width;
	}
	return;
}

void clrMap(t_map map)
{
	t_point p;

	p.x = -1;
	while (++p.x < map.width && (p.y = -1))
		while (++p.y < map.height)
			clrPoint(p, map);
	return;
}

// ZOOM MAP
void makeZoom(t_map *zoomed, t_map map, double zoom, t_point center)
{
	t_point p;
	t_point zp;
	t_dpoint scale;
		
	if (!map.data || !map.width || !map.height)
		return;
	if (!zoomed->width && !zoomed->height)
	{
		zoomed->width = map.width;
		zoomed->height = map.height;
		zoomed->tilesize = map.tilesize;
	}
	if (!zoomed->data && !makeMap(zoomed, zoomed->width, zoomed->height, zoomed->tilesize))
		return;
	scale = createDPoint((double) zoomed->width / map.width, (double) zoomed->height / map.height);
	p.y = map.height;
	while (--p.y >= 0 && (p.x = -1))
		while (++p.x < map.width)
			if (!isElement(p, EMPTY, map))
			{
				zp.x = round((p.x - center.x) * zoom + center.x * scale.x);
				zp.y = round((p.y - center.y) * zoom + center.y * scale.y);
				putPoint(zp, *zoomed, map.data[p.x][p.y]);
			}
	return;	
}

