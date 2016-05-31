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

int CheckHor (const tPlayer array[], tPlayer player, int *coordsx, int *coordsy){//geht doch über 2 zeilen
	//INIT
	int max_verschiebung = MAX_X - 4;//maximale Ausbreitung um noch 4 zu schaffen
	int won = 0;
	
	//Check
		for(int x = 0; x <= max_verschiebung; x++) {//stellt sicher dass 4 nicht über zwei Zeilen geht
			for(int y = 0; y <= (MAX_Y - 1) * MAX_X; y = y + MAX_X) {//geht die Zeilen durch
				if(array[x + y] == player){//geht von links nach rechts durch die Reihe
					if(array[x + y + 1] == player){
						if(array[x + y + 2] == player){
							if(array[x + y + 3] == player){
								won++;
								*coordsx = x;
								*coordsy = y / MAX_X;
							}
						}		
					}	
				}
			}
		}
	
	//Result
	if(won > 0) {
		//ShowYouWon(player);
		return 1;
	} else {
		return 0;
	}
}

int CheckVer (const tPlayer array[], tPlayer player, int *coordsx, int *coordsy){
		//INIT
	int max_verschiebung = MAX_Y - 4;//maximale Ausbreitung um noch 4 zu schaffen
	int won = 0;
	
	//Check
		for(int x = 0; x < MAX_X; x++) {
			for(int y = 0; y <= max_verschiebung; y++) {
			
				if(array[x + (y * MAX_X)] == player){//Erster Fund
					if(array[x + (y * MAX_X) + MAX_X] == player){//1 Zeile über erster Fund
						if(array[x + (y * MAX_X) + 2 * MAX_X] == player){
							if(array[x + (y * MAX_X) + 3 * MAX_X] == player){
								won++;
								*coordsx = x;
								*coordsy = y;
							}
						}		
					}	
				}
			}
		}
	
	//Result
	if(won > 0) {
		//ShowYouWon(player);
		return 1;
	} else {
		return 0;
	}
}


int main(int argc, char **argv)
{
	enum tPlayer playGround[MAX_X * MAX_Y] = {0};
	InitPlayGround(MAX_X, MAX_Y);
	int chips_rot, chips_gelb;
	if((MAX_X * MAX_Y) % 2 != 0) {
		chips_rot = MAX_X * MAX_Y / 2 + 1;
		chips_gelb = MAX_X * MAX_Y / 2 + 1;
	} else {
		chips_rot = MAX_X * MAX_Y / 2;
		chips_gelb = MAX_X * MAX_Y / 2;
	}
	
	int player = 2; // Gelb beginnt
	DrawChips( chips_gelb, chips_rot, player); //Anzahl verbleibende Chips malen
	
	DrawPlayGround(playGround, MAX_X, MAX_Y);//Spielfläche aufbauen
	
	/*
	while (CheckComplete(playGround) == 0 && CheckHor(playGround, 2) == 0) {
		DropChip(playGround, SelectCol(), PLAYER_R);
	}*/	
	int x = 0;
	int y = 0;
	while (CheckComplete(playGround) == 0) {
		if(player == 1){ //Spielerrotation
			while(DropChip(playGround, SelectCol(), PLAYER_L)==0){}//Wiederholen bis richtig gesetzt wurde
			chips_rot--;
			if(CheckHor(playGround, 1, &x, &y) == 1) {
				HighlightChipHor(x, y);
				ShowYouWon(1);	
				DrawChips(0, 0, 0);			
				return 0;
			}
			if(CheckVer(playGround, 1, &x, &y) == 1) {
				HighlightChipVer(x, y);
				ShowYouWon(1);
				DrawChips(0, 0, 0);				
				return 0;
			}
			player = 2;
			DrawChips( chips_gelb, chips_rot, player); //Anzahl verbleibende Chips malen
		} else {
			while(DropChip(playGround, SelectCol(), PLAYER_R)==0){}//Wiederholen bis richtig gesetzt wurde
			chips_gelb--;
			if(CheckHor(playGround, 2, &x, &y) == 1) {
				HighlightChipHor(x, y);
				ShowYouWon(2);		
				DrawChips(0, 0, 0);		
				return 0;
			}
			if(CheckVer(playGround, 2, &x, &y) == 1) {
				HighlightChipVer(x, y);
				ShowYouWon(2);	
				DrawChips(0, 0, 0);			
				return 0;
			}
			player = 1;
			DrawChips( chips_gelb, chips_rot, player); //Anzahl verbleibende Chips malen
		}
	}
	DrawChips(0, 0, 0);
	return 0;
}
