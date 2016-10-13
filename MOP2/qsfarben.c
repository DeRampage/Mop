#include <sdlite.h> 
#define MAX_COLORS 80
#define BLOCK_SIZE 48

typedef struct {
	unsigned char blue, green, red, alpha;
} tColor;
	
typedef union {
	tColor c;
	int32_t col;
} tCol;


tColor gList[MAX_COLORS] =
{
	128, 128, 255, 255,
	128, 255, 255, 255,
	128, 255, 128, 255,
	255, 255, 128, 255,
	255, 128, 255, 255,
	191, 128, 255, 255,
	192, 255, 255, 255,
	193, 0, 128, 255,
	194, 255, 128, 255,
	195, 128, 255, 255,
	128, 191, 255, 255,
	128, 128, 192, 255,
	128, 192, 128, 255,
	255, 193, 128, 255,
	255, 194, 255, 255,
	128, 0, 255, 255,
	0, 255, 255, 255,
	128, 255, 0, 255,
	255, 0, 128, 255,
	0, 128, 255, 255,
	0, 127, 0, 255,
	128, 0, 0, 255,
	128, 0, 128, 255,
	0, 0, 129, 255,
	0, 0, 80, 255,
	80, 0, 80, 255,
	80, 80, 80, 255,
	60, 60, 60, 255,
	40, 40, 40, 255,
	20, 20, 20, 255,
	128, 128, 80, 255,
	128, 255, 80, 255,
	128, 80, 128, 255,
	255, 80, 128, 255,
	255, 128, 80, 255,
	191, 128, 80, 255,
	192, 255, 80, 255,
	0, 100, 0, 255,
	0, 80, 0, 255,
	0, 60, 0, 255,
	0, 40, 0, 255,
	80, 192, 200, 255,
	224, 224, 225, 255,
	234, 254, 245, 255,
	255, 255, 255, 255,
	255, 0, 0, 255,
	0, 255, 0, 255,
	255, 0, 255, 255,
	0, 0, 255, 255,
	254, 255, 0, 255,
	255, 0, 255, 255,
	0, 253, 255, 255,
	255, 80, 80, 255,
	0, 128, 255, 255,
	0, 64, 128, 255,
	0, 64, 255, 255,
	0, 40, 80, 255,
	80, 20, 20, 255,
	128, 40, 40, 255,
	255, 80, 90, 255,
	80, 80, 255, 255,
	128, 80, 255, 255,
	192, 80, 255, 255,
	0, 0, 40, 255,
	0, 0, 100, 255,
	160, 160, 160, 255,
	192, 192, 192, 255,
	64, 92, 64, 255,
	64, 128, 192, 255,
	64, 192, 192, 255,
	64, 192, 128, 255,
	192, 20, 225, 255,
	40, 0, 40, 255,
	100, 0, 100, 255,
	160, 60, 160, 255,
	192, 39, 192, 255,
	92, 64, 64, 255,
	128, 64, 192, 255,
	192, 64, 192, 255,
	192, 64, 128, 255,
};

void CreateRandomGray(tColor list[])
{
	for (int i = 0; i < 80; i++)
	{
		unsigned char grayValue = rand()&255;
		list[i].alpha = 255;
		list[i].red = grayValue;
		list[i].green = grayValue;
		list[i].blue = grayValue;
	}		 
}

void DrawColors(SDL_Surface* screen, const tColor list[])
{
	int i,j;
	SDL_Rect r = { 0, 0, BLOCK_SIZE, BLOCK_SIZE };
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 10; i++)
		{
			SDL_FillRect(screen, &r,  ((tCol*)&list[i + j * 10])->col);
			r.x += BLOCK_SIZE;
		}
		r.x = 0;
		r.y += BLOCK_SIZE;
	}
	SDL_Flip(screen);
}


/* event handling */
int EventLoop(void)
{
	int index;
	SDL_Event event;
	while (1)
	{
		SDL_WaitEvent(&event) ;
		switch (event.type) 
		{
			case SDL_QUIT:
				return 0;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 0;
				default: 
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				index = event.button.x / BLOCK_SIZE + event.button.y / BLOCK_SIZE * 10;
				if (index<MAX_COLORS)
					printf("Farbe: r=%2hhx,g=%2hhx,b=%2hhx\n",
							gList[index].red,
							gList[index].green,
							gList[index].blue);

				break;
			default: break;
		}
	}
	return 0;
}

/* ToDo: Write Compare Functions */
int cmpfunc (const void* a, const void* b)
{
	const tColor **ap = a, **bp = b;
	return ( *(int *)a - *(int *)b );
}


int main(void)
{
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;
  
    atexit(SDL_Quit);

    SDL_Surface *screen = SDL_SetVideoMode(BLOCK_SIZE*10, BLOCK_SIZE*8, 0, 0);
    //screen = SDL_SetVideoMode(BLOCK_SIZE * 10, BLOCK_SIZE *8, 0, 0);
    if (screen == NULL)
        return 2;

	
	DrawColors(screen, gList);
	
	/* ToDo: add function call to qsort() */
	qsort(gList, sizeof(gList), sizeof(tColor), cmpfunc);
	
	DrawColors(screen, gList);
	
	return EventLoop();
}

