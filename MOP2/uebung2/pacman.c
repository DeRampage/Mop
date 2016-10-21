/* A simple Pacman-Project (c) 2009 by D. Pawelczak *************************/

#include "pacman.h"

#define ICON_SIZE 32
#define SIZE_X (ICON_SIZE*MAX_X)
#define SIZE_Y (ICON_SIZE*MAX_Y+24)

#ifdef MOPVM
#include <sdlite.h>
#else
#include <SDL/sdl.h>
#endif

/* GLOBAL VARIABLES *********************************************************/

tField playground[MAX_Y][MAX_X]; 		/* play ground */

static SDL_Surface *bmps[MAX_FIELDS];   /* image files */
static SDL_Surface* text1 = NULL;
static tDir gPacmanDir = RIGHT;     	/* current direction */
static int gScore = 0;           
static int gHighScore = 250;
static int gSplash = 0;             	/* adds a splash bitmap */

static void SetPacmanPosition(unsigned int x, unsigned int y)
{
	gSplash = (ACCOUNT_GOODIE(x,y)>1);
	gScore+=ACCOUNT_GOODIE(x,y);
	playground[y][x] = PLAYER;
}

/* Help function to retrieve the current x/y-position of the pacman */
int GetPacmanPosition(unsigned int*x, unsigned int*y)
{
	int i,j;
	for (i=0;i<MAX_X;i++)
		for (j=0;j<MAX_Y;j++)
				if (playground[j][i] == PLAYER)
				{
					if (x)
						*x=i;
					if (y)
						*y=j;
					return 1;
				}

	
	return 0; 
}

/* checks, if pacman ate everything */
static int IsAllEaten(void)
{
	int i,j;
	for (i=0;i<MAX_X;i++)
		for (j=0;j<MAX_Y;j++)
			if (playground[j][i]==NEW)
				return 0;
	return 1;
}


static int DrawText(SDL_Surface* screen, char* txt, int x, int y)
{
	SDL_Rect to;
	SDL_Rect from;
	int i, l;

	
	if (!text1)
		return 0;

	to.x = (short) x;
	to.y = (short) y;
	to.w = 0;
	to.h = 0;

	for (i = 0; txt[i]!='\0'; i++)
		if (txt[i] != ' ')
		{
			l = txt[i];
			l -= 32;
			to.w=0;
			to.h=0;
			from.x = (short)(1+((l) % 13)*24);
			from.y = (short)(6+((l) / 13)*24);
			from.w = 22;
			from.h = 23;
			SDL_BlitSurface(text1, &from, screen, &to);
			to.x += 15;
			if ((l>32) && (l<64)) to.x += 3;
			l = txt[i];
			if ((l=='f') || (l=='t')|| (l=='i')|| (l=='l')|| (l=='o')|| (l=='e')|| (l=='s')|| (l=='.')
				) to.x -= 3;
			if ((l=='m')||(l=='w')) to.x += 7;
		} else to.x += 8;

		return 1;
}



/* draws the whole game, as a timer event */
static void DrawPlayground(int flagPacmansMouth, SDL_Surface* screen)
{
	int i,j;
	static int lastScore = -1;
	static int lastHighScore = -1;
	static int x, y;
	static int hasWone = 0;
	 
	for (i=0;i<MAX_X;i++)
		for (j=0;j<MAX_Y;j++)
		{
//				VDrawBMP(i*ICON_SIZE,j*ICON_SIZE,bmps[playground[j][i]]);
			SDL_Rect pos = { i * ICON_SIZE, j * ICON_SIZE, ICON_SIZE, ICON_SIZE};
			SDL_Surface* image = NULL;
			if (playground[j][i]!=PLAYER)
			{
				image = bmps[playground[j][i]];
			} else
			{ /* select player image */
				switch (gPacmanDir)
				{
					case RIGHT: image = bmps[PLAYER+flagPacmansMouth];
						break;
					case LEFT:	image = bmps[PLAYER_LEFT+flagPacmansMouth];
						break;
					case UP:	image = bmps[PLAYER_UP+flagPacmansMouth];
						break;
					case DOWN:	image = bmps[PLAYER_DOWN+flagPacmansMouth];
						break;
				}
			}
			SDL_BlitSurface(image, NULL, screen, &pos);
			if (playground[j][i] ==PLAYER && gSplash)
				SDL_BlitSurface(bmps[SPLASH], NULL, screen, &pos);
			
		}
	
	gSplash=0;
	if (!GetPacmanPosition(&x, &y) && !hasWone)
	{
		SDL_Rect rect = {SIZE_X/2-100,SIZE_Y/2-100,200,75};
		SDL_FillRect(screen, &rect,0xff0000ff);
		rect.x +=  1;
		rect.w -=  2;
		rect.y +=  1;
		rect.h -=  2;
		SDL_FillRect(screen, &rect,0xff000000);
		DrawText(screen, "Game over!", rect.x+25, rect.y+25);
	} else
	if (IsAllEaten() || hasWone)
	{
		hasWone = 1;
		SDL_Rect rect = {SIZE_X/2-100,SIZE_Y/2-100,200,75};
		SDL_FillRect(screen, &rect,0xff0000ff);
		rect.x +=  1;
		rect.w -=  2;
		rect.y +=  1;
		rect.h -=  2;
		SDL_FillRect(screen, &rect,0xff000000);
		playground[y][x] = PLAYER;
		DrawText(screen, "You won!", rect.x+25, rect.y+25);
	}

/* Draw Score */
	if (gScore!=lastScore)
	{
		char tmp[8];
		DrawText(screen, "Score:", 2, SIZE_Y - 24);
		sprintf(tmp,"%d",gScore);
		DrawText(screen, tmp, 100, SIZE_Y - 24);
		lastScore = gScore;
	}
	
	if (gHighScore<gScore)
	{
		gHighScore = gScore;
		DrawText(screen, "A new Highscore!", SIZE_X-240, SIZE_Y-24);

	}
	/* Draw High Score */
	if (gHighScore!=lastHighScore)
	{
		char tmp[8];
		DrawText(screen, "Highscore:", 180, SIZE_Y-24);
		sprintf(tmp,"%d",gHighScore);
		DrawText(screen, tmp,320,SIZE_Y-24);
		lastScore = gScore;
	}
	
	SDL_Flip(screen);
}


/* Global Timer-Callback, which synchronizes the whole game and draws the graphics */
static int ScreenTimer(int timertick, void*param)
{
	static int pacmansMouth = 0;
	/* animation flag for pacman's mouth open/close state */
	pacmansMouth = !pacmansMouth;	
	DrawPlayground(pacmansMouth, param);
	return timertick; /* reestablish timer */
}

/* Creates a simple labyrinth */
static void CreatePlayground(void)
{
	int i,j;
	/* Mark the whole playground as untouched (new) */
	for (i=0;i<MAX_X;i++)
		for (j=0;j<MAX_Y;j++)
			playground[j][i]=NEW;

	/* create x-border */
	for (i=0;i<MAX_X;i++)
	{
		playground[0][i]=SOLID;
		playground[MAX_Y-1][i]=SOLID;
	}
	/* create y-border */
	for (j=0;j<MAX_Y;j++)
	{
		playground[j][0]=SOLID;
		playground[j][MAX_X-1]=SOLID;
	}
	/* create a simple labyrinth */
	for (j=2;j<MAX_Y-1;j+=2)
	{
		for (i=2;i<MAX_X-2;i++)
			if (rand()%11!=0)
				playground[j][i]=SOLID;
		playground[j+1][rand()%(MAX_X-1)]=SOLID;
	}
	/* Start position of player */
	playground[1][1]=PLAYER;
}

static int error(int errno)
{
	printf("Error initializing the SDL!\n%s\n", SDL_GetError());
	return errno;
}

/*****************************************************************/

int PacMan(void)
{
	SDL_Surface *start = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return error(1);
    start = SDL_SetVideoMode(SIZE_X, SIZE_Y, 32, SDL_SWSURFACE);
    if (start == NULL)
        return error(2);

	bmps[EMPTY] = SDL_LoadBMP("iconEmpty.bmp");
	bmps[NEW]= SDL_LoadBMP("iconNew.bmp");
	bmps[SOLID]= SDL_LoadBMP("iconSolid.bmp");
	bmps[GOODIE]= SDL_LoadBMP("iconGoodie1.bmp");
	bmps[PLAYER]= SDL_LoadBMP("iconPacman.bmp");
	bmps[PLAYER2]= SDL_LoadBMP("iconPacman2.bmp");
	bmps[PLAYER_LEFT]= SDL_LoadBMP("iconPacmanL.bmp");
	bmps[PLAYER_LEFT2]= SDL_LoadBMP("iconPacmanL2.bmp");
	bmps[PLAYER_UP]= SDL_LoadBMP("iconPacmanU.bmp");
	bmps[PLAYER_UP2]= SDL_LoadBMP("iconPacmanU2.bmp");
	bmps[PLAYER_DOWN]= SDL_LoadBMP("iconPacmanD.bmp");
	bmps[PLAYER_DOWN2]= SDL_LoadBMP("iconPacmanD2.bmp");
	bmps[SPLASH]= SDL_LoadBMP("iconSplash.bmp");
	SDL_SetColorKey(bmps[SPLASH], SDL_SRCCOLORKEY, 0);
	bmps[ENEMY]= SDL_LoadBMP("iconGS1.bmp");
	bmps[ENEMY2]= SDL_LoadBMP("iconGS2.bmp");
	
	for (tField i = EMPTY; i <= ENEMY2; i++)
		if (bmps[i] == NULL) 
		{
			printf("Error loading bitmap file!\n");
			return 3;
		}	
	text1 = SDL_LoadBMP("font8.bmp");
	if (text1 == NULL) 
	{
		printf("Error loading font8.bmp file!\n");
		return 4;
	}	

	CreatePlayground();
	/* add timer to update the playground */
	SDL_AddTimer(200, ScreenTimer, start); /* draws screen */

	return 0;
}

/*****************************************************************/

int CheckEvents(void)
{
	unsigned int x, y;
	int dx = 0, dy = 0;
	SDL_Event event;
	
	SDL_WaitEvent(&event);
	
	switch (event.type) 
	{
	
//		case SDL_QUIT: return 1;
			
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: 	return 1;
			case SDLK_RIGHT: 	gPacmanDir = RIGHT; dx=1; dy=0; 	break;
			case SDLK_LEFT:		gPacmanDir = LEFT;  dx=-1; dy=0; 	break;
			case SDLK_UP: 		gPacmanDir = UP;    dx=0; dy=-1; 	break;
			case SDLK_DOWN:		gPacmanDir = DOWN;  dx=0; dy=1; 	break;
			}
			if (dx||dy)
			{
				if (GetPacmanPosition(&x,&y))
				if (x > 0U && y > 0U && CHECK_FREE(x + dx, y + dy))
				{
					playground[y][x] = EMPTY;
					SetPacmanPosition(x+dx,y+dy);
					SDL_Delay(180); /* reduce pacman speed */
				}
			} 
			break;
		default:
			/* slow down in case of other events (not needed in threaded version) */
			SDL_Delay(100); 
			break;
	}
	return 0;
}
