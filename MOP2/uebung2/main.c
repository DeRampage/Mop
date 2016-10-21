#include "pacman.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sdlite.h>
#include <threads.h>




typedef struct 
{
	unsigned int x, y;
	tField behind;
}tGoodie;

int randomGTime(int von, int bis);

Uint32 RemoveGoodie(Uint32 intervall, void* param){
	tGoodie* fG = param;
	//printf("Parameter x: %d und y: %d\n", fG->x, fG->y);
	playground[fG->y][fG->x] = fG->behind;
	
	free(fG);
	return 0;
}


/* ToDo: Callbacks for Goodies */
Uint32 NewGoodie(Uint32 intervall, void* param){
int rX = 0, rY = 0;
   do{
		rX = rand() % (MAX_X-1);
		rY = rand() % (MAX_Y-1);
    	printf("%d, %d\n", rX, rY);
		
	} while(!CHECK_EMPTY(rX, rY));

	tGoodie *fG = malloc(sizeof(tGoodie));
	fG-> x = rX;
	fG-> y = rY;
	fG->behind = playground[rY][rX];
	
	playground[rY][rX] = GOODIE;
			
	SDL_TimerID remover = SDL_AddTimer(randomGTime(4000, 7000), RemoveGoodie, fG);
	
	SDL_TimerID timer = SDL_AddTimer(randomGTime(2000, 5000), NewGoodie, NULL);
	
	
	return 0;
}


int randomGTime(int von, int bis){
	int time;
	time = rand()% (bis-von) + von;
	//printf("GTIME: %d\n", time); 
	return time;
	
}

/* ToDo: Thread Function for Enemy */
int Enemy(void* dummy){
	
		unsigned int count;
		unsigned int x,y;
		unsigned int i = 10,j = 10;
		count=0;
		printf("Thread:");
		
		do {
			x = rand();
			y = rand();
			x %= (MAX_X); 
			y %= (MAX_Y);
		} while(!CHECK_EMPTY(x, y));
		
		playground[y][x] = ENEMY;
	
	//Steuerung des Enemy
	SDL_Delay(randomGTime(3000, 5000));
	thrd_create(NULL, Enemy, NULL);

	
	for (count = 0; count < 25U; count++)
	{
			int nx, ny;
			
			nx = x;
			ny = y;
			//playground[y][x] = ENEMY;
		
			/* retrieve pacman position, so that enemy can follow ... */
			GetPacmanPosition(&i, &j);
			if (i>x && CHECK_EMPTY_OR_PLAYER(x + 1, y))
				nx++;
			else
			if (i<x && CHECK_EMPTY_OR_PLAYER(x - 1, y))
				nx--;
			else
			if (j<y && CHECK_EMPTY_OR_PLAYER(x, y - 1))
				ny--;
			else
			if (j>y && CHECK_EMPTY_OR_PLAYER(x, y + 1))
				ny++;
			playground[y][x]=EMPTY;
			playground[ny][nx]=ENEMY;
			x=nx;
			y=ny;
				
			SDL_Delay(200);
			 
			
	}
		
	playground[y][x]=EMPTY;
	
	return 0;
}


int EventLoop(void)
{
	while(1)
	{
		if (CheckEvents())
			break;
	}
	return 0;
}

int main(int argc, char**argv)
{
	int errno =  0;
	srand(time(NULL));
	if (errno = PacMan())
	{
		return errno;
	}
	
	/* ToDo: add Timer-Callbacks for Goodies */
	//SDL_TimerID timer = SDL_AddTimer(200, NewGoodie, NULL);
	if(CheckEvents()){
		return 0;
	}
	SDL_TimerID timer = SDL_AddTimer(randomGTime(2000, 7000), NewGoodie, NULL);
	if(timer){
		printf("Timer erfolgreich erstellt!\n");
	}
	thrd_create(NULL, Enemy, NULL);
	
	
	/* Implementation of an enemy *********************************************/
	/* An enemy lives for 25 Steps and walks a bit slower than the player ... */
	/**************************************************************************/
	
	/* ToDo: move enemy into Thread */
	/* Already done */
	
	
	
	/* EventLoop */
	
	return EventLoop();
	
}
