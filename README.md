# Terminal Raycasting
#### Video Demo: https://youtu.be/Y5R43J6mi88

#### Description:
In this project, my goal was achieve a mini raycasting game, running on terminal,
where the color and the light of each pixel would be determined for the color and
the density of a character. To do that my program is divided in 3 general parts.

Map
The map consist of a bidimensional matrix of ints, where 0 represent empty spaces
and 1 represent walls. Basically, the player can walk in empty spaces but can't
walk throught walls. This concept represent the 2D format of the game.

Rays
The player has rays that calculate the distance of the closest wall in his
repective direction. To do that, is made a loop while is not found a wall
in the current position checked.

3D Projection
To do the 3D projection, is used the distance of each ray to determine if
the wall should be printed smaller or bigger. It happens because closest
thing in field of view looks bigger and far away things look smaller.
With that, is applied too, the concept that far away produces more shadow
and closest produce clearer


**Map.c -**
In this file, has the proper functions to handle creation of maps matrix, printing 
2D matrix in terminal and a function that import a map reading a file. The importMap
function accept only file maps that contains the same number of elements in each
line. Each map has a width, height, data and tilesize, that is the size of each grid
of the map. So the map is divided by blocks of size tilesize X tilesize. In the creation
function, is allocated data to the map, so the programmer should use the function freeMap
after using the variable.

**Camera.c -**
This file have the functions to create a camera, rays, determine the rays based on
a field of view of a camera and put the camera position in a map. One of the most
important part of this file is the raycasting function, where it calculate the length
of a ray. To calculate the ray length I used the following algorithm:
    - First we get the current camera position. Then check direction that the player is looking
    - In the player's direction we get the next position of the closest tilesize grid, 
    because if the map is made by blocks, a wall can appear in each block of the map
    - Then we check if the current block position is a wall. if it is, so we stop the loop
    and calculate the distance of the ray using the hypotenuse
    sqrt(cathetus1 * cathetus1 + cathetus2 * cathetus2)
    - This value is stored in a array of rays of the camera, and then, is done the same thing
    to the other rays

**Screen.c -**
Provide the structure of a screen, where can display a 3D projection of a 2D map
getting the ray's len. To do that, each ray length is draw in the screen as a line
but in a perspective format. To give the perspective, is done the following calculumn:
WallSize * RayLen / PlaneDist. The WallSize, represent how tall the walls is going to look,
and the PlaneDist, is the distance of the camera and the actual plane that is going to be
the screen that we are looking at.

**Move.c -**
This file have the structure of keyboard keys to move a player of a camera. It consist of
a UP, LEFT, DOWN, RIGHT characters to be able to move the player, where UP and DOWN moves
the camera/player to forward and backwards, and the RIGHT AND LEFT moves rotate the player.
The move() function permita that a camera/player move in a 2D map provided.
If the motion exceeds the map limits or hit a wall, the motion is not done.

**Pixel.c -**
Create pixels representation using characters scale of density to luminosity
and escape character '\e' to print colored characters in terminal. It provides too
a brightness structure, that have a scale variable to user pass a
gradual increasing character's density string to represent the gradual lighting.
This structure have a brightness vision that is how dark the camera vision is going
to be.

**Split.c -**
I created a split function to handle importation of maps in files, where the split 
function returns a array of strings that was splited by a determined delimiter.

**Point.c -**
That is the base file of my project that is used from all of others. It provides the 
point structure and all creation, arithmetics, calculation of lines, and others.
