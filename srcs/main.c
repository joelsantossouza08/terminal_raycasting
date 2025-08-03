#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal-raycasting.h"
#include "split.h"

#define ANGLE TO_RAD(275)
#define FOV TO_RAD(60)

int main(void)
{
	t_map map;
	t_camera camera;
	t_point center;
	t_moves key;
	t_brightness brightness;
	t_screen screen;
	t_dpoint vision;

	stdInitTerminal();
	importMap(&map, 100, "test.map", 1024);

	center = createPoint(map.width/2, map.height/2);

	camera = createCamera(center, ANGLE, FOV, 600);

	key = createKeys('w', 'a', 's', 'd');

	vision = createDPoint(200, 20);
	brightness = createBrightness(vision, " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@");

	screen = createScreen(600, 150, FOV, brightness);

	while (1)
	{
		if (!moveCamera(&camera, key, map))
			break;
		//putCamera(camera, map, ALL);
		//putGrid(map.tilesize, map.tilesize, map);
		//printMap(map);
		//clrCamera(camera, map, ALL);

		make3DVision(camera, screen, map.tilesize*2, brightness.range/2);
		printScreen(screen);
	}
	freeMap(map);
	freeCamera(camera);
	freeScreen(screen);
	return 0;
}
