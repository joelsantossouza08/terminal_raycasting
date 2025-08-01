#include <string.h>
#include "player.h"

// INITIALIZE FUNCTIONS
void makePlayer(t_player *player, t_point point, t_camera camera, t_moves key, t_raytype raytype)
{
	player->point = point;		
	player->camera = camera;
	player->key = key;
	player->raytype = raytype;
	return;
}

t_player createPlayer(t_point point, t_camera camera, t_moves key, t_raytype raytype)
{
	t_player player;

	makePlayer(&player, point, camera, key, raytype);
	return player;
}

// MOTIONS
int movePlayer(t_player *player, t_map map)
{
	if (!map.data || !move(player->key, &player->point, &player->camera.angle, map))
		return 0;
	//rayscasting(player->camera, player->raytype, map);
	return 1;
}

// ITERACT WITH MAP
void putPlayer(t_player player, t_map map, int flags)
{
	if (!map.data)
		return;
	if (flags)
		putCamera(player.camera, map, flags);
	putPoint(player.point, map, PLAYER);
	return;
}

void clrPlayer(t_player player, t_map map, int flags)
{
	if (!map.data)
		return;
	if (flags)
		clrCamera(player.camera, map, flags);
	clrPoint(player.point, map);
	return;
}
