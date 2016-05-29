#ifndef PLAYGROUND_H
#define PLAYGROUND_H

typedef enum tPlayer{EMPTY, PLAYER_L, PLAYER_R}; /* ToDo */


/* initializes a playground with x*y elements. x,y within 4..8 */
int InitPlayGround(int sizeX, int sizeY);

/* draws an empty playground */
void ClearPlayGround(int sizeX, int sizeY);

/* draws the playground according to a x*y array of enums */
void DrawPlayGround(tPlayer playGround[], int sizeX, int sizeY);

/* draws the amount of chips of the right and left player */
void DrawChips(int countR,  /* amount of chips for the right player */
			   int countL,  /* amount of chips for the left player */
			   tPlayer player /* selects player */
			   );
/* highlights 4 chips within the playgound horizontally */
void HighlightChipHor(int x, int y);
/* highlights 4 chips within the playgound vertically */
void HighlightChipVer(int x, int y);
/* returns the row 0 .. sizeX-1 selected by the player's mouse click */ 
int SelectCol(void);
/* Shows who won */
void ShowYouWon(tPlayer selected);


#endif