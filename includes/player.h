#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "move.h"
#include "camera.h"
#include "point.h"

typedef struct
{
	t_point	point;
	//double angle;
	t_camera camera;
	t_moves	key;
	t_raytype raytype;
} t_player;

void			makePlayer(t_player *player, t_point point, t_camera camera, t_moves key, t_raytype raytype);
t_player	createPlayer(t_point point, t_camera camera, t_moves key, t_raytype raytype);

int				movePlayer(t_player *player, t_map map);

void			putPlayer(t_player player, t_map map, int flags);
void			clrPlayer(t_player player, t_map map, int flags);

#endif
