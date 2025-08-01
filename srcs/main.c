#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal-raycasting.h"

#define ANGLE TO_RAD(223.45)
#define FOV TO_RAD(60)

int main(void)
{
	t_map map;
	t_camera camera;
//	t_point center;
	t_moves key;
//
//	(void)center;
//	stdInitTerminal();
	map = createMap(10, 10, 10);
//
//	center = createPoint(map.width/2, map.height/2);
//
	camera = createCamera(createPoint(39, 98), ANGLE, FOV, 20);
//
	key = createKeys('w', 'a', 's', 'd');
//
//	putPointSize(createPoint(0, map.height-map.tilesize), map.tilesize, map, WALL);
//	putPointSize(createPoint(1*map.tilesize, map.height-map.tilesize*2), map.tilesize, map, WALL);
//	putPointSize(createPoint(2*map.tilesize, map.height-map.tilesize*3), map.tilesize, map, WALL);
//	putPointSize(createPoint(3*map.tilesize, map.height-map.tilesize*4), map.tilesize, map, WALL);
//
//	putPointSize(createPoint(map.width-map.tilesize, map.tilesize), map.tilesize, map, WALL);
//	putPointSize(createPoint(map.width-map.tilesize*2, map.tilesize), map.tilesize, map, WALL);
//	putPointSize(createPoint(map.width-map.tilesize*3, map.tilesize), map.tilesize, map, WALL);
//	putPointSize(createPoint(map.width-map.tilesize*4, map.tilesize), map.tilesize, map, WALL);
//	putPointSize(createPoint(map.width-map.tilesize*5, map.tilesize), map.tilesize, map, WALL);
//	putPointSize(createPoint(map.width-map.tilesize*6, map.tilesize*2), map.tilesize, map, WALL);
//	while (1)
//	{
//		if (!moveCamera(&camera, key, map))
//			break;
//		putCamera(camera, map, ALL);
//		putGrid(map.tilesize, map.tilesize, map);
//		printMap(map);
//		clrCamera(camera, map, ALL);
//		//printf("position: %d, %d\n", camera.point.x, camera.point.y);
//		//printf("angle: %Lf\n", TO_DEGRE(camera.angle));
//	}
//	freeMap(map);
//	freeCamera(camera);
	t_screen screen;
	t_brightness brightness;

	brightness = createBrightness(50, "'.*(L#");
	screen = createScreen(20, 20, FOV, brightness);

	moveCamera(&camera, key, map);

	make3DVision(camera, screen, map.tilesize*2, brightness.range/2);
	printScreen(screen);
	(void)brightness;
	return 0;
}	
