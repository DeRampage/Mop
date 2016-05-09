/* Praktikum Maschinenorientiertes Programmieren - Vorlage Versuch 4 von D. Pawelczak */
#include <math.h>
#ifdef MOPVM
#include <sdlite.h>
#else
#include <SDL/sdl.h>
#endif

/* Konstanten */
#define SIZE_X 320
#define SIZE_Y 240
#define MAX_ITERATION 128
#define BIT_DEPTH 32
#define MAX_BETRAG 4
#define EINEZEILE SIZE_X * 4

/* Strukturen */
typedef struct{
	unsigned char blue; 
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
} tColor;

typedef struct {
	double re;
	double im;
} tComplex;

/*Funktionsprototypen*/
void PutPixel(unsigned char* videoRam, int x, int y, const tColor *c);
void FillScreen(unsigned char* videoRam, const tColor *c);
int Iteration(tComplex *c);
void Mandelbrot (unsigned char* videoRam, tComplex *c, double delta);

const tColor gColorList[] = 
{ 	
	{ 0x10, 0x00, 0x00, 0xFF }, { 0x20, 0x00, 0x00, 0xFF }, { 0x30, 0x00, 0x00, 0xFF }, { 0x40, 0x00, 0x00, 0xFF }, { 0x50, 0x00, 0x00, 0xFF }, { 0x60, 0x00, 0x00, 0xFF }, { 0x70, 0x00, 0x00, 0xFF }, { 0x80, 0x00, 0x00, 0xFF },
	{ 0x90, 0x00, 0x00, 0xFF }, { 0xad, 0x00, 0x00, 0xFF }, { 0xb0, 0x00, 0x00, 0xFF }, { 0xc0, 0x00, 0x00, 0xFF }, { 0xd0, 0x00, 0x00, 0xFF }, { 0xe0, 0x00, 0x00, 0xFF }, { 0xf0, 0x00, 0x00, 0xFF }, { 0xff, 0x00, 0x00, 0xFF },
	{ 0xff, 0x10, 0x10, 0xFF }, { 0xff, 0x20, 0x20, 0xFF }, { 0xff, 0x30, 0x30, 0xFF }, { 0xff, 0x40, 0x40, 0xFF }, { 0xff, 0x50, 0x50, 0xFF }, { 0xff, 0x60, 0x60, 0xFF }, { 0xff, 0x70, 0x70, 0xFF }, { 0xff, 0x80, 0x80, 0xFF },
	{ 0xff, 0x90, 0x80, 0xFF }, { 0xff, 0xa0, 0x80, 0xFF }, { 0xff, 0xb0, 0x80, 0xFF }, { 0xff, 0xc0, 0x80, 0xFF }, { 0xff, 0xd0, 0x80, 0xFF }, { 0xff, 0xe0, 0x80, 0xFF }, { 0xff, 0xf0, 0x80, 0xFF }, { 0xff, 0xff, 0x80, 0xFF },
	{ 0xf0, 0xff, 0x80, 0xFF }, { 0xe0, 0xff, 0x80, 0xFF }, { 0xd0, 0xff, 0x80, 0xFF }, { 0xc0, 0xff, 0x80, 0xFF }, { 0xb0, 0xff, 0x80, 0xFF }, { 0xa0, 0xff, 0x80, 0xFF }, { 0x90, 0xff, 0x80, 0xFF }, { 0x80, 0xff, 0x80, 0xFF },
	{ 0x80, 0xff, 0x80, 0xFF }, { 0x70, 0xff, 0x70, 0xFF }, { 0x60, 0xff, 0x60, 0xFF }, { 0x50, 0xff, 0x50, 0xFF }, { 0x40, 0xff, 0x40, 0xFF }, { 0x30, 0xff, 0x30, 0xFF }, { 0x20, 0xff, 0x20, 0xFF }, { 0x10, 0xff, 0x10, 0xFF },
	{ 0x00, 0xf0, 0x00, 0xFF }, { 0x00, 0xe0, 0x00, 0xFF }, { 0x00, 0xd0, 0x00, 0xFF }, { 0x00, 0xc0, 0x00, 0xFF }, { 0x00, 0xb0, 0x00, 0xFF }, { 0x00, 0xa0, 0x00, 0xFF }, { 0x00, 0x90, 0x00, 0xFF }, { 0x00, 0x80, 0x00, 0xFF },
	{ 0x00, 0x80, 0x10, 0xFF }, { 0x00, 0x80, 0x20, 0xFF }, { 0x00, 0x80, 0x30, 0xFF }, { 0x00, 0x80, 0x40, 0xFF }, { 0x10, 0x80, 0x50, 0xFF }, { 0x20, 0x80, 0x60, 0xFF }, { 0x30, 0x80, 0x70, 0xFF }, { 0x40, 0x80, 0x80, 0xFF },
	{ 0x40, 0x90, 0x90, 0xFF }, { 0x50, 0xa0, 0xa0, 0xFF }, { 0x60, 0xb0, 0xb0, 0xFF }, { 0x60, 0xc0, 0xc0, 0xFF }, { 0x70, 0xd0, 0xd0, 0xFF }, { 0x70, 0xe0, 0xe0, 0xFF }, { 0x70, 0xf0, 0xf0, 0xFF }, { 0x70, 0xff, 0xff, 0xFF },
	{ 0x80, 0xff, 0xff, 0xFF }, { 0x80, 0xf0, 0xff, 0xFF }, { 0x80, 0xd0, 0xff, 0xFF }, { 0x80, 0xc0, 0xff, 0xFF }, { 0x80, 0xb0, 0xff, 0xFF }, { 0x80, 0xa0, 0xff, 0xFF }, { 0x80, 0x90, 0xff, 0xFF }, { 0x80, 0x80, 0xff, 0xFF }, 
	{ 0x70, 0x70, 0xff, 0xFF }, { 0x60, 0x60, 0xff, 0xFF }, { 0x50, 0x50, 0xff, 0xFF }, { 0x40, 0x40, 0xff, 0xFF }, { 0x30, 0x30, 0xff, 0xFF }, { 0x20, 0x20, 0xff, 0xFF }, { 0x10, 0x10, 0xff, 0xFF }, { 0x00, 0x00, 0xff, 0xFF }, 
	{ 0x00, 0x00, 0xf0, 0xFF }, { 0x00, 0x00, 0xe0, 0xFF }, { 0x00, 0x00, 0xd0, 0xFF }, { 0x00, 0x00, 0xc0, 0xFF }, { 0x00, 0x00, 0xb0, 0xFF }, { 0x00, 0x00, 0xa0, 0xFF }, { 0x00, 0x00, 0x90, 0xFF }, { 0x00, 0x00, 0x80, 0xFF }, 
	{ 0x10, 0x00, 0x80, 0xFF }, { 0x20, 0x00, 0x80, 0xFF }, { 0x30, 0x00, 0x80, 0xFF }, { 0x40, 0x00, 0x80, 0xFF }, { 0x50, 0x00, 0x80, 0xFF }, { 0x60, 0x00, 0x80, 0xFF }, { 0x70, 0x00, 0x80, 0xFF }, { 0x80, 0x00, 0x80, 0xFF }, 
	{ 0x80, 0x10, 0x80, 0xFF }, { 0x90, 0x10, 0x80, 0xFF }, { 0xa0, 0x10, 0x90, 0xFF }, { 0xb0, 0x10, 0xa0, 0xFF }, { 0xc0, 0x10, 0xa0, 0xFF }, { 0xd0, 0x10, 0xb0, 0xFF }, { 0xe0, 0x20, 0xc0, 0xFF }, { 0xf0, 0x20, 0xd0, 0xFF }, 
	{ 0xff, 0x20, 0xf0, 0xFF }, { 0xff, 0x30, 0xf0, 0xFF }, { 0xff, 0x40, 0xf0, 0xFF }, { 0xff, 0x50, 0xe0, 0xFF }, { 0xff, 0x60, 0xd0, 0xFF }, { 0xff, 0x70, 0xc0, 0xFF }, { 0xff, 0x80, 0xb0, 0xFF }, { 0xff, 0x90, 0xa0, 0xFF }, 
	{ 0xff, 0x80, 0x90, 0xFF }, { 0xff, 0x90, 0x80, 0xFF }, { 0xff, 0xa0, 0x80, 0xFF }, { 0xff, 0xb0, 0x80, 0xFF }, { 0xff, 0xc0, 0x80, 0xFF }, { 0xff, 0xd0, 0x80, 0xFF }, { 0xff, 0xe0, 0x80, 0xFF }, { 0xff, 0xf0, 0x80, 0xFF },   
	{ 0x00, 0x00, 0x00, 0xFF }
};

int main(int argc, char** argv) {
	
	unsigned char* videoRam = NULL;
	SDL_Surface *screen = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		return 1;
	}
    screen = SDL_SetVideoMode(SIZE_X, SIZE_Y, BIT_DEPTH, 0);
    if (screen == NULL){
        return 2;
	}
	/* the ptr to video memory */
	videoRam = screen->pixels;
	
	// Aufgabe 1
	tColor sandyBrown = { .blue = 0x60, .green = 0xA4, .red = 0xF4, .alpha = 0xFF};
	//PutPixel(videoRam, 50, 50, &sandyBrown);
	
	// Aufgabe 2
	//FillScreen(videoRam, &sandyBrown);
	
	//Aufgabe 3
	
	tComplex ceins = {0, 0}; // Antwort 128
	tComplex czwo = {0.5, 0}; // Antwort 5
	tComplex cdrei = {-14, 17}; // Antwort 0
	printf("Anzahl Wiederholung: %i", Iteration(&czwo));
	
	
	//Aufgabe 5
	
	tComplex ctest = {-2, -1};
	double delta = 0.008;
	
	
	// Aufgabe 6
	/*
	tComplex ctest = {0.410600057, 0.3616605002};
	double delta = 0.0000004;
	*/
	
	Mandelbrot(videoRam, &ctest, delta);
	
	SDL_Flip(screen);
	return 0;
}

void PutPixel(unsigned char* videoRam, int x, int y, const tColor *c) {
	if(x >= 0 && x < SIZE_Y * 4){
		x = x * 4;
		if(y >= 0 && y < SIZE_Y){
			if(y > 0){
				for(y = y; y > 0; y--){
					x+= EINEZEILE;
				}
			}
			videoRam[x] = c->blue;
			videoRam[x + 1] = c->green;
			videoRam[x + 2] = c->red;
			videoRam[x + 3] = c->alpha;
		}
	}
}

void FillScreen(unsigned char* videoRam, const tColor *c) {
	int y = 0;
	int x = 0;
	while(x < SIZE_X) {
		y = 0;
		while(y < SIZE_Y){
			PutPixel(videoRam, x, y, c);
			y++;
		}
		x++;
	}
}

int Iteration(tComplex *c) {
	tComplex zComplex = {0, 0};
	int i = 0;
	for(i = 0; i < MAX_ITERATION; i++) {
		double real = (pow(zComplex.re, 2) - pow(zComplex.im, 2)) + c->re;
		double imag = (2 * zComplex.re * zComplex.im) + c->im;
		if(pow(real, 2) + pow(imag, 2) > pow(MAX_BETRAG, 2)) break;
		zComplex.re = real;
		zComplex.im = imag;
	}
	return i;
}

void Mandelbrot (unsigned char* videoRam, tComplex *c, double delta) {
	double start = c -> re;
	for(int i = 0; i < SIZE_Y; i++) {
		c->re = start;
		for(int k = 0; k < SIZE_X; k++) {
			tColor color = gColorList[Iteration(c)];
			PutPixel(videoRam, k, i, &color);
			c->re += delta;
		}
		c->im += delta;
	}
}