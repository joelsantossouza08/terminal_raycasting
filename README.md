Terminal Raycasting
#### Video Demo:  <URL HERE>

Description:
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
With that is applied too, the concept that far away produces more shadow
and closest produce clearer

