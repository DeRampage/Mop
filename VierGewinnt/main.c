#include "playground.h"
#define MAX_X 5
#define MAX_Y 5

int DropChip(tPlayer array[], int col, tPlayer chip) {
	if(array[(MAX_Y - 1) * MAX_X + col] != 0){
		return 0; //Spalte ist voll
	} else {
		array[(MAX_Y - 1) * MAX_X + col] = chip;
		DrawPlayGround(array, MAX_X, MAX_Y);
		int y = 1;
		while(y < MAX_Y && array[(MAX_Y - (y + 1)) * MAX_X + col] == 0) {
			array[(MAX_Y - y) * MAX_X + col] = 0;
			y++;
			array[(MAX_Y - y) * MAX_X + col] = chip;	
			DrawPlayGround(array, MAX_X, MAX_Y);	
		}
		return 1; //Erfolg
	}
}

int CheckComplete(tPlayer array[]) {
	int x = MAX_X;
	int counter = 0;
	while(x > 0) {
		x--;
		if(array[MAX_Y * MAX_X - x - 1] != 0){
			counter++;
		}
	}
	if(counter == MAX_X) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char **argv)
{
	enum tPlayer playGround[MAX_X * MAX_Y] = {0};
	InitPlayGround(MAX_X, MAX_Y);
	/* Testarea*/
	playGround[MAX_Y * MAX_X] = 1;
	
	DrawPlayGround(playGround, MAX_X, MAX_Y);
	while (CheckComplete(playGround) == 0) {
		DropChip(playGround, SelectCol(), PLAYER_R);
	}
	return 0;
}