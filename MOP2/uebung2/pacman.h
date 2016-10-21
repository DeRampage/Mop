#ifndef _PACMAN_H
#define _PACMAN_H

/* A simple Pacman-Project (c) 2009 by D. Pawelczak *************************/

/* GLOBAL DEFINES ***********************************************************/

//#define MAX_X 20

//#define MAX_Y 13
#define MAX_X 20
#define MAX_Y 13


/* GLOBAL INCLUDES **********************************************************/

/* GLOBAL TYPES *************************************************************/

typedef enum { EMPTY, NEW, SOLID, PLAYER, PLAYER2, PLAYER_LEFT, PLAYER_LEFT2,
			   PLAYER_UP, PLAYER_UP2, PLAYER_DOWN, PLAYER_DOWN2, SPLASH, 
			   ENEMY, ENEMY2, GOODIE, GOODIE2, MAX_FIELDS } tField;

typedef enum { RIGHT, LEFT, UP, DOWN } tDir;

/* GLOBAL MACROS ************************************************************/

#define CHECK_EMPTY(x,y) (playground[y][x] == EMPTY || playground[y][x] == NEW)
#define CHECK_FREE(x,y) (playground[y][x] == EMPTY || playground[y][x] == NEW || playground[y][x] == GOODIE)
#define ACCOUNT_GOODIE(x,y) ((playground[y][x] == NEW) * 1 + ((playground[y][x] == GOODIE) * 100))
#define CHECK_EMPTY_OR_PLAYER(x,y) (playground[y][x] == EMPTY || playground[y][x] == NEW || playground[y][x] == PLAYER)


/* GLOBAL VARIABLES **********************************************************/
extern tDir gPacmanDir;
extern tField playground[MAX_Y][MAX_X]; /* play ground */



/* GLOBAL FUNCTIONS **********************************************************/

/* Initializes the game, loads the icons, sets up timer callback to draw playground. */
int PacMan(void); 
/* stores the Pacman's position in output parameters x,y; return 0 if pacman is dead. */
int GetPacmanPosition(unsigned int* x, unsigned int* y); 
/* checks keyboard events and alters Pacman's position, returns 1, if quit event received. */
/* Note, check events blocks, if no event is present */
int CheckEvents(void); 

/* GLOBAL CALLBACKS **********************************************************/


#endif