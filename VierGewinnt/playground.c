/* Vorlage für Praktikum Maschinenorientiertes Programmieren Versuch 5 (Felder) (c) by D. Pawelczak */
#include "playground.h"
#ifdef MOPVM
#include <sdlite.h>
#else
#include <SDL/sdl.h>
#endif

/* module defines */
#define COLOR_DEPTH 32
#define TILE_SIZE 56
/* global surface */
static SDL_Surface* screen;
/* global images */
static SDL_Surface* chips[6];
static SDL_Surface* win;
static SDL_Surface* black;

/* My Space */

typedef struct{
	int Status;
} tPlayer;

/*My Space End */
/* loads a bmp into  array chips */
static int LoadChip(char* fileName, SDL_Surface* chips[], int index) {
	chips[index] = SDL_LoadBMP(fileName);	
	if (!chips[index]) {
		printf("Error loading bitmap file: %s\n", fileName);
		return 1;
	}
	/* make black transparent except for empty */
	if (index) 
		SDL_SetColorKey(chips[index], SDL_SRCCOLORKEY, 0);
	return 0;
}
	

/* initializes a playground with x*y elements. x,y within 4..8 */
int InitPlayGround(int sizeX, int sizeY){
	SDL_Surface *start = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 || sizeX < 4 || sizeY < 4 || sizeX > 8 || sizeY > 8)
		return 1;
    screen = SDL_SetVideoMode(sizeX * TILE_SIZE, (sizeY + 1) * TILE_SIZE, COLOR_DEPTH, 0);
    if (screen == NULL)
        return 2;
	
	if (LoadChip("box.bmp", chips, 0))
		return 3;
	if (LoadChip("chip1.bmp", chips, 1))
		return 3;
	if (LoadChip("chip2.bmp", chips, 2))
		return 3;
	if (LoadChip("box2.bmp", chips, 3))
		return 3;
	if (LoadChip("chip1g.bmp", chips, 4))
		return 3;
	if (LoadChip("chip2g.bmp", chips, 5))
		return 3;
	win = SDL_LoadBMP("win.bmp");
	if (!win) {
		printf("Could not load win.bmp!\n");
		return 4;
	} else
		SDL_SetColorKey(win, SDL_SRCCOLORKEY, 0);
	black = SDL_LoadBMP("black.bmp");
	if (!win) {
		printf("Could not load black.bmp!\n");
		return 4;
	}
	start = SDL_LoadBMP("start.bmp");
	if (!start) {
		printf("Could not load start.bmp!\n");
		return 4;
	} else {
		
		SDL_Rect pos = { (sizeX / 2) * TILE_SIZE - 100 ,  80 };
		SDL_BlitSurface( start, NULL, screen, &pos);
	}
	SDL_Flip(screen);
	SDL_Delay(10);
	return 0;
}
void ShowYouWon(tPlayer selected)
{
	int sizeX = screen->w / TILE_SIZE;
	SDL_Rect pos = { (sizeX / 2)*56 - 100 ,  80 };
	SDL_BlitSurface( chips[selected], NULL, screen, &pos);
	pos.x -= 8;
	pos.y -= 8;
	SDL_BlitSurface( win, NULL, screen, &pos);
	SDL_Flip(screen);
	SDL_Event event;
	while(1) {
		SDL_WaitEvent(&event) ;
		switch (event.type) {

			case SDL_QUIT:
				return;
				break;
			case SDL_MOUSEBUTTONDOWN:
            	return;
				break;			
			default: 
				break;
		}
	}

}


void DrawPlayGround(tPlayer playGround[], int sizeX, int sizeY) {
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++) {
			SDL_Rect pos = { j * 56, (i + 1) * 56, 56, 56 };
			SDL_BlitSurface(chips[playGround[(sizeY - 1 - i) * sizeX + j]], NULL, screen, &pos);
		}
	SDL_Flip(screen);
	SDL_Delay(10);

}
void ClearPlayGround(int sizeX, int sizeY) {
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++) {
			SDL_Rect pos = { j*56, (i+1)*56, 56, 56 };
			SDL_BlitSurface(chips[0], NULL, screen, &pos);
		}
	SDL_Flip(screen);
	//SDL_Delay(10);

}

int SelectCol(void)
{
	SDL_Event event;
	while(1) {
		SDL_WaitEvent(&event) ;
		switch (event.type) {

			case SDL_QUIT: 
				return 0;
				
			case SDL_MOUSEBUTTONDOWN: 
				
				/* check top rows in screen, return column */
				if (event.button.y < 2 * TILE_SIZE) {
					return event.button.x / TILE_SIZE;
				}
				break;
			default:
				break;	
				
		}
	}
	return 0;
}
	
void DrawChips(int countR, int countL, int selected) {
	int i = 0; 
	int gSizeX = screen->w / TILE_SIZE;
	int gSizeY = screen->h / TILE_SIZE;
	SDL_Surface *draw;
	
	for (i = 0; i < gSizeX; i++) {
		SDL_Rect pos = {i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
		SDL_BlitSurface(black, NULL, screen, &pos);
	}
	draw = chips[1];
	if (selected != 1)
		draw = chips[1 + 3];
	
	/* stack chips from left */
	for (i = 0; i < countL; i++) {
		SDL_Rect pos = { i * TILE_SIZE / ((10 - gSizeX) *( 1 + gSizeX*gSizeY/12)),  0, 56, 56 };
		SDL_BlitSurface(draw, NULL, screen, &pos);
	}
	draw = chips[2];
	if (selected != 2)
		draw = chips[2 + 3];
	
	/* stack chips from left */
	for (i = 0; i < countR; i++) {
		SDL_Rect pos = { (gSizeX-1)*TILE_SIZE-(i*TILE_SIZE/((10-gSizeX)*(1+gSizeX*gSizeY/12))), 0, TILE_SIZE, TILE_SIZE };
		SDL_BlitSurface(draw, NULL, screen, &pos);
	}
	SDL_Flip(screen);
}

void HighlightChipHor(int x, int y) {
	int sizeY = screen->h;
	for (int i = 0; i < 4; i++)	{
		SDL_Rect pos = { (x + i) * TILE_SIZE, sizeY - TILE_SIZE - y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
		SDL_BlitSurface(chips[3], NULL, screen, &pos);
	}
}
void HighlightChipVer(int x, int y) {
	int sizeY = screen->h;
	for (int i = 0; i < 4; i++)	{
		SDL_Rect pos = { x * TILE_SIZE, sizeY - TILE_SIZE - (y + i) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
		SDL_BlitSurface(chips[3], NULL, screen, &pos);
	}
}
			
