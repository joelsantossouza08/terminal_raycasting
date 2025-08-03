#include <stdio.h>
#include <string.h>
#include <termios.h>
#include "move.h"
#include "map.h"

#define NKEYS 4
#define ESC 27

// INITIALIZE FUNCTIONS
void makeKeys(t_moves *key, char up, char left, char down, char right)
{
	key->up			= up;
	key->left		= left;
	key->down		= down;
	key->right	= right;
	return;
}

t_moves createKeys(char up, char left, char down, char right)
{
	t_moves key;

	makeKeys(&key, up, left, down, right);
	return key;
}

void initTerminal(unsigned int minChrs, int time)
{
	struct termios term;

	tcgetattr(STDIN, &term);
	term.c_lflag &= ~ICANON;
	term.c_cc[VMIN] = minChrs;
	term.c_cc[VTIME] = time;
	tcsetattr(STDIN, TCSANOW, &term);
	return;
}

void stdInitTerminal(void)
{
	initTerminal(1, 0);
	return;
}

void userConfigKeys(t_moves *key)
{
	char keys[NKEYS+1];
	char *dirs[NKEYS];
	int i;
	int j;

	memset(keys, 0, sizeof(keys));
	dirs[0] = "UP";
	dirs[1] = "LEFT";
	dirs[2] = "DOWN";
	dirs[3] = "RIGHT";
	i = -1;
	while (++i < NKEYS)
	{
		printf("%s: ", dirs[i]);
		keys[i] = getchar();
		printf("\n");
		j = i;
		while ((j = j+1 >= NKEYS ? 0 : j+1) != i)
			if (keys[i] == keys[j])
			{
				fprintf(stderr, "\nERROR: key '%c' already used by %s\n\n", keys[i--], dirs[j]);
				break;
			}
	}
	makeKeys(key, keys[0], keys[1], keys[2], keys[3]);
	return;
}

// MOVE IN MAP
int moveInMap(t_moves key, t_point *point, double *angle, t_map map)
{
	t_point moved;
	char keyPressed;

	if (!map.data)
		return 0;
	keyPressed = getchar();
	if (keyPressed == ESC)
		return 0;
	else if (keyPressed == key.left)
		*angle = createNormAngle(*angle + ROTATION * SPEED);
	else if (keyPressed == key.right)
		*angle = createNormAngle(*angle - ROTATION * SPEED);
	else if (keyPressed == key.up)
		moved = createNextPoint(*point, *angle, STEP * SPEED, ROUND);
	else if (keyPressed == key.down)
		moved = createNextPoint(*point, *angle, -STEP * SPEED, ROUND);
	if ((keyPressed == key.up || keyPressed == key.down) && inMapLimit(moved, map) && !isElement(moved, WALL, map))
		*point = moved;
	return 1;
}
