#include <stdio.h>
#include <sdlite.h>

void PutPixel(unsigned char* videoRam, int x, int y, const tColor *c);

void FillScreen(unsigned char* videoRam, const tColor *c);

int main(void){
	const tColor *c;
	SDL_Init();
	SDL_SetVideoMode();
	//FillScreen();
	PutPixel(
	return 0;
}


void PutPixel(unsigned char* videoRam, int x, int y, const tColor *c) {
	printf("x: %d y: %d\n", x, y);
}

void FillScreen(unsigned char* videoRam, const tColor *c) {
	
}