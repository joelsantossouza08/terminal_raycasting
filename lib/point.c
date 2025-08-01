#include <math.h>
#include "point.h"

// INITIALIZE FUNCTIONS
void makeDPoint(t_dpoint *point, double x, double y)
{
	point->x = x;
	point->y = y;
	return;
}

t_dpoint createDPoint(double x, double y)
{
	t_dpoint point;

	makeDPoint(&point, x, y);
	return point;
}

void makePoint(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
	return;
}

t_point createPoint(int x, int y)
{
	t_point point;

	makePoint(&point, x, y);
	return point;
}

void makeDVector(t_dvector *vector, t_dpoint p1, t_dpoint p2)
{
	vector->x = p2.x - p1.x;
	vector->y = p2.y - p1.y;
	return;
}

t_dvector createDVector(t_dpoint p1, t_dpoint p2)
{
	t_dvector vector;

	makeDVector(&vector, p1, p2);
	return vector;
}

void makeVector(t_vector *vector, t_point p1, t_point p2)
{
	vector->x = p2.x - p1.x;
	vector->y = p2.y - p1.y;
	return;
}

t_vector createVector(t_point p1, t_point p2)
{
	t_vector vector;

	makeVector(&vector, p1, p2);
	return vector;
}

// POINT CHECK CONDITIONS
int isPointsEqual(t_point a, t_point b)
{
	return a.x == b.x && a.y == b.y;
}

// ARITHMETIC FUNCTIONS
void makeAddedPoint(t_point *point, int x, int y)
{
	point->x += x;
	point->y += y;
	return;
}

t_point createAddedPoint(t_point point, int x, int y)
{
	makeAddedPoint(&point, x, y);
	return point;
}

void makeSumPoints(t_point *p1, t_point p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
	return;
}

t_point createSumPoints(t_point p1, t_point p2)
{
	makeSumPoints(&p1, p2);
	return p1;
}

// ANGLES
void makeNormAngle(double *angle)
{
	*angle = fmod(*angle, CIRCLE);
	*angle += *angle <= 0 ? CIRCLE : 0;
	return;
}

double createNormAngle(double angle)
{
	angle = fmod(angle, CIRCLE);
	return angle <= 0 ? angle + CIRCLE : angle;
}

int isFacingUp(double angle)
{
	return angle > 0 && angle < SEMI_CIRCLE;
}

int isFacingDown(double angle)
{
	return !isFacingUp(angle);
}

int isFacingRight(double angle)
{
	return angle > 3*PI/2 || angle < QUARTER_CIRCLE;
}

int isFacingLeft(double angle)
{
	return !isFacingRight(angle);
}

// LINES
void makeNextPoint(t_point *point, double angle, double steps, int flags)
{
	t_dpoint result;

	result.x = point->x + cos(angle) * steps;
	result.y = point->y + sin(angle) * steps;

	if (flags == ROUND)
		makePoint(point, round(result.x), round(result.y));
	else
		makePoint(point, result.x, result.y);
	return;
}

t_point createNextPoint(t_point point, double angle, double steps, int flags)
{
	makeNextPoint(&point, angle, steps, flags);
	return point;
}

void makePointsLen(int *len, t_point p1, t_point p2)
{
	t_vector vector;

	makeVector(&vector, p1, p2);
	*len = sqrt(SQUARE(vector.y) + SQUARE(vector.x));
	return;
}

int createPointsLen(t_point p1, t_point p2)
{
	int len;

	makePointsLen(&len, p1, p2);
	return len;
}

void makeDist(t_dist *dist, t_point p1, t_point p2)
{
	dist->x = p2.x - p1.x;
	dist->y = p2.y - p1.y;
	dist->len = createPointsLen(p1, p2);
	return;
}

t_dist createDist(t_point p1, t_point p2)
{
	t_dist dist;

	makeDist(&dist, p1, p2);
	return dist;
}

