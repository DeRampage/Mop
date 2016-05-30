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

int CheckHor (const tPlayer array[], tPlayer player){//geht doch über 2 zeilen
	//INIT
	int max_verschiebung = MAX_X - 4;//maximale Ausbreitung um noch 4 zu schaffen
	int won = 0;
	
	//Check
		for(int x = 0; x <= max_verschiebung; x++) {//stellt sicher dass 4 nicht über zwei Zeilen geht
			for(int y = 0; y <= MAX_Y; y = y + MAX_X) {//geht die Zeilen durch
				if(array[x + y] == player){//geht von links nach rechts durch die Reihe
					if(array[x + y + 1] == player){
						if(array[x + y + 2] == player){
							if(array[x + y + 3] == player){
								won++;
							}
						}		
					}	
				}
			}
		}
	
	//Result
	if(won > 0) {
		ShowYouWon(player);
		return 1;
	} else {
		return 0;
	}
}

int CheckVer (const tPlayer array[], tPlayer player){
		//INIT
	int max_verschiebung = MAX_Y - 4;//maximale Ausbreitung um noch 4 zu schaffen
	int won = 0;
	
	//Check
		for(int x = 0; x <= MAX_X; x++) {//stellt sicher dass 4er nicht über zwei Zeilen geht
			for(int y = 0; y <= max_verschiebung; y++) {//geht die Zeilen durch
				if(array[x + y] == player){//geht von links nach rechts durch die Reihe
					if(array[x + y + MAX_X] == player){
						if(array[x + y + MAX_X + MAX_X] == player){
							if(array[x + y + MAX_X + MAX_X + MAX_X] == player){
								won++;
							}
						}		
					}	
				}
			}
		}
	
	//Result
	if(won > 0) {
		ShowYouWon(player);
		return 1;
	} else {
		return 0;
	}
}


int main(int argc, char **argv)
{
	enum tPlayer playGround[MAX_X * MAX_Y] = {0};
	InitPlayGround(MAX_X, MAX_Y);
	
	/* Testarea
	playGround[0] = 2; 
	playGround[5] = 2;
	playGround[10] = 2;
	playGround[15] = 2;
	*/
	int player = 1; // Rot beginnt
	DrawChips(13, 13, 1); //Anzahl verbleibende Chips malen
	
	DrawPlayGround(playGround, MAX_X, MAX_Y);//Spielfläche aufbauen
	
	int won = 0;
	while (CheckComplete(playGround) == 0 && CheckHor(playGround, 2) == 0) {
		DropChip(playGround, SelectCol(), PLAYER_R);
	}
	/*
	while (CheckComplete(playGround) == 0 && won == 0) {
		
		if(player == 1){ //Spielerrotation
			DropChip(playGround, SelectCol(), PLAYER_L);
			won = CheckHor(playGround, 1);
			won = CheckVer(playGround, 1);
			DrawChips(13, 13, 2); //Anzahl verbleibende Chips malen
			player = 2;
		} else {
			DropChip(playGround, SelectCol(), PLAYER_R);
			won = CheckHor(playGround, 2);
			won = CheckVer(playGround, 2);
			DrawChips(13, 13, 1); //Anzahl verbleibende Chips malen
			player = 1;
		}
	}
	*/
	return 0;
}