#ifndef MOVE_H
#define MOVE_H

#include "point.h"
#include "map.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define ROTATION 0.01
#define STEP 1
#define SPEED 5

typedef struct
{
	char up;
	char left;
	char down;
	char right;
} t_moves;

void		makeKeys(t_moves *key, char up, char left, char down, char right);
t_moves	createKeys(char up, char left, char down, char right);

void		initTerminal(unsigned int flags, int time);
void		stdInitTerminal(void);
void		userConfigKeys(t_moves *key);

int			move(t_moves key, t_point *point, double *angle, t_map map);

#endif
