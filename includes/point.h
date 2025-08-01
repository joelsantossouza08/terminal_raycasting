#ifndef POINT_H
#define POINT_H

#define SQUARE(n) ((n) * (n))

#define PI 3.14159265358979323846264338327950288420L
#define CIRCLE (PI * 2)
#define SEMI_CIRCLE PI
#define QUARTER_CIRCLE (PI / 2)

#define TO_RAD(a) ((a) * (PI / 180))
#define TO_DEGRE(a) ((a) * (180 / PI))

#define ROUND 1

typedef struct
{
	double x;
	double y;
} t_dpoint;

typedef struct
{
	int x;
	int y;
} t_point;

typedef struct
{
	int x;
	int y;
	int len;
} t_dist;

typedef 	t_point t_vector;
typedef		t_dpoint t_dvector;

void			makeDPoint(t_dpoint *point, double x, double y);
t_dpoint	createDPoint(double x, double y);

void			makePoint(t_point *point, int x, int y);
t_point		createPoint(int x, int y);

void			makeDVector(t_dvector *vector, t_dpoint p1, t_dpoint p2);
t_dvector createDVector(t_dpoint p1, t_dpoint p2);

void			makeVector(t_vector *vector, t_point p1, t_point p2);
t_vector	createVector(t_point p1, t_point p2);

void			makeDist(t_dist *dist, t_point p1, t_point p2);
t_dist		createDist(t_point p1, t_point p2);

int				isPointsEqual(t_point a, t_point b);

void			makeAddedPoint(t_point *point, int x, int y);
t_point		createAddedPoint(t_point point, int x, int y);
void			makeSumPoints(t_point *p1, t_point p2);
t_point		createSumPoints(t_point p1, t_point p2);

void			makeNormAngle(double *angle);
double		createNormAngle(double angle);
int				isFacingUp(double angle);
int				isFacingDown(double angle);
int				isFacingRight(double angle);
int				isFacingLeft(double angle);

void			makeNextPoint(t_point *point, double angle, double steps, int flags);
t_point		createNextPoint(t_point point, double angle, double steps, int flags);
void			makePointsLen(int *len, t_point p1, t_point p2);
int				createPointsLen(t_point p1, t_point p2);

#endif
