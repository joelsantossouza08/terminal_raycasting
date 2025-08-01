#ifndef CAMERA_H
#define CAMERA_H 

#include "map.h"
#include "move.h"

#define RENDER_CAMERA			1
#define RENDER_RAYSPOINT	2
#define RENDER_RAYSLINE		4
#define ALL RENDER_CAMERA | RENDER_RAYSLINE

typedef struct
{
  t_point point;
	t_dist	dist;
  double  angle;
  int     len;
} t_ray;

typedef struct
{
	t_point point;
	double angle;
	double fov;
	int nrays;
	t_ray *rays;
} t_camera;

typedef		void (*t_raytype)(t_camera);

void			makeRay(t_ray *ray, t_point point, t_dist dist, double angle, int len);
t_ray			createRay(t_point point, t_dist dist, double angle, int len);

void			freeCamera(t_camera camera);
int 			makeCamera(t_camera *camera, t_point point, double angle, double fov, unsigned int nrays);
t_camera	createCamera(t_point point, double angle, double fov, unsigned int nrays);

void 			makeEuclideanRays(t_camera camera);
void  		makePerpendicularRays(t_camera camera);

void  		rayscasting(t_camera camera, t_raytype raytype, t_map map);
void			makeRaycasting(t_ray *ray, t_map map);

void			putCamera(t_camera camera, t_map map, int flags);
void			clrCamera(t_camera camera, t_map map, int flags);

int				moveCamera(t_camera *camera, t_moves key, t_map map);

#endif
