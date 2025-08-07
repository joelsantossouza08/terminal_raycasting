#include <stdlib.h>
#include <math.h>
#include "camera.h"

// INITIALIZE FUNCTIONS
void makeRay(t_ray *ray, t_point point, t_dist dist, double angle, int len)
{
  ray->point = point;
  ray->dist = dist;
  ray->angle = angle;
  ray->len = len;
  return;
}

t_ray createRay(t_point point, t_dist dist, double angle, int len)
{
  t_ray ray;

  makeRay(&ray, point, dist, angle, len);
  return ray;
}

// --

void freeCamera(t_camera camera)
{
	if (camera.rays)
		free(camera.rays);
	return;
}

int makeCamera(t_camera *camera, t_point point, double angle, double fov, unsigned int nrays)
{
	camera->point = point;
	camera->angle = createNormAngle(angle);
	camera->fov = createNormAngle(fov);
	camera->nrays = nrays;
	camera->rays = calloc(nrays, sizeof(t_ray));
	return camera->rays != 0;
}

t_camera createCamera(t_point point, double angle, double fov, unsigned int nrays)
{
  t_camera camera;

  makeCamera(&camera, point, angle, fov, nrays);
  return camera;
}

// MAKE RAYS
void makeEuclideanRays(t_camera camera)
{
  double increment;
  int i;
  int middle;

	if (!camera.nrays)
		return;
  middle = camera.nrays / 2;
  camera.rays[middle].angle = camera.angle;
  camera.rays[middle].point = camera.point;
  increment = camera.fov / camera.nrays;
  i = 0;
  while (middle - ++i >= 0)
  {
    camera.rays[middle - i].angle = createNormAngle(camera.angle - increment * i);
    camera.rays[middle - i].point = camera.point;
    if (middle + i < camera.nrays)
    {
      camera.rays[middle + i].angle = createNormAngle(camera.angle + increment * i);
      camera.rays[middle + i].point = camera.point;
    }
  }
  return;
}

// RAYCASTING
void initHorizCast(t_ray *horiz, t_point start, double angle, t_map map)
{
	horiz->point.y = floor(start.y / map.tilesize) * map.tilesize;
	if (isFacingUp(angle))
	{
		horiz->point.y += map.tilesize;
		horiz->dist.y = map.tilesize;
	}
	else
		horiz->dist.y = -map.tilesize;
	angle = tan(angle);
	horiz->point.x = (horiz->point.y - start.y) / angle + start.x;
	horiz->dist.x = horiz->dist.y / angle;
	makePointsLen(&horiz->len, start, horiz->point);
	horiz->dist.len = sqrt(SQUARE(horiz->dist.y) + SQUARE(horiz->dist.x));	
	horiz->dist.dir = HORIZ;
	return;
}

void initVertCast(t_ray *vert, t_point start, double angle, t_map map)
{
	vert->point.x = floor(start.x / map.tilesize) * map.tilesize;
	if (isFacingRight(angle))
	{
		vert->point.x += map.tilesize;
		vert->dist.x = map.tilesize;
	}
	else
		vert->dist.x = -map.tilesize;
	angle = tan(angle);
	vert->point.y = (angle * (vert->point.x - start.x)) + start.y;
	vert->dist.y = vert->dist.x * angle;
	makePointsLen(&vert->len, start, vert->point);
	vert->dist.len = sqrt(SQUARE(vert->dist.y) + SQUARE(vert->dist.x));
	vert->dist.dir = VERT;
	return;
}

t_ray *hitWall(t_ray *horiz, t_ray *vert, t_map map)
{
	if (horiz->len <= vert->len)
	{
		if (isElement(horiz->point, WALL, map) || !inMapLimit(horiz->point, map))
			return horiz;
		horiz->point.x += horiz->dist.x;
		horiz->point.y += horiz->dist.y;
		horiz->len += horiz->dist.len;
	}
	else
	{
		if (isElement(vert->point, WALL, map) || !inMapLimit(vert->point, map))
			return vert;
		vert->point.x += vert->dist.x;
		vert->point.y += vert->dist.y;
		vert->len += vert->dist.len;
	}
	return 0;
}

//#include <stdio.h>
//#include <unistd.h>
//#define TIME 2
//t_ray *debugMode(t_ray *horiz, t_ray *vert, t_map map)
//{
//	if (horiz->len <= vert->len)
//	{
//		if (isElement(horiz->point, WALL, map) || !inLimit(horiz->point, map))
//		{
//			putPoint(horiz->point, map, RAY);
//			return horiz;
//		}
//		putPoint(horiz->point, map, RAY);
//		putGrid(map.tilesize, map.tilesize, map);
//		printMap(map);
//		sleep(TIME);
//		horiz->point.x += horiz->dist.x;
//		horiz->point.y += horiz->dist.y;
//		horiz->len += horiz->dist.len;
//	}
//	else
//	{
//		if (isElement(vert->point, WALL, map) || !inLimit(vert->point, map))
//		{
//			putPoint(vert->point, map, PLAYER);
//			return vert;
//		}
//		putPoint(vert->point, map, PLAYER);
//		putGrid(map.tilesize, map.tilesize, map);
//		printMap(map);
//		sleep(TIME);
//		vert->point.x += vert->dist.x;
//		vert->point.y += vert->dist.y;
//		vert->len += vert->dist.len;
//	}
//	return 0;
//}

void makeRaycasting(t_ray *ray, t_map map)
{
	t_ray horiz;
	t_ray vert;
	t_ray *hit;
	t_ray *notHit;

	if (!map.data)
		return;
	initHorizCast(&horiz, ray->point, ray->angle, map);
	initVertCast(&vert, ray->point, ray->angle, map);
	hit = notHit = 0;
	while (!hit || hit->len > notHit->len)
	{
		hit = hitWall(&horiz, &vert, map);
		if (hit)
			notHit = hit == &horiz ? &vert : &horiz;
	}
	hit = horiz.len <= vert.len ? &horiz : &vert;
	ray->point = hit->point;
	ray->dist = hit->dist;
	ray->len = hit->len;
	return;
}

// INTERACT WITH MAP
void putCamera(t_camera camera, t_map map, int flags)
{
	int i;

	if (!map.data || !flags)
		return;
	i = -1;
	if (flags & RENDER_RAYSPOINT)
		while (++i < camera.nrays)
			if (!isPointsEqual(camera.point, camera.rays[i].point))
				putPoint(camera.rays[i].point, map, RAY);
	i = -1;
	if (flags & RENDER_RAYSLINE)
		while (++i < camera.nrays)
			putLine(camera.point, camera.rays[i].point, map, RAY);
	if (flags & RENDER_CAMERA)
		putPoint(camera.point, map, CAMERA);
	return;
}

void clrCamera(t_camera camera, t_map map, int flags)
{
	int i;

	if (!map.data || !flags)
		return;
	i = -1;
	if (flags & RENDER_RAYSPOINT)
		while (++i < camera.nrays)
			if (!isPointsEqual(camera.point, camera.rays[i].point))
				clrPoint(camera.rays[i].point, map);
	i = -1;
	if (flags & RENDER_RAYSLINE)
		while (++i < camera.nrays)
			putLine(camera.point, camera.rays[i].point, map, EMPTY);
	if (flags & RENDER_CAMERA)
		clrPoint(camera.point, map);
	return;
}

// MOTION
int moveCamera(t_camera *camera, t_moves key, t_map map)
{
	int i;

	if (!map.data || !moveInMap(key, &camera->point, &camera->angle, map))
		return 0;
	makeEuclideanRays(*camera);
	i = -1;
	while (++i < camera->nrays)
		makeRaycasting(&camera->rays[i], map);
	return 1;
}

