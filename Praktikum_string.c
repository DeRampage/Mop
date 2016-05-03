#define GIGA 1024
#define ZWO
#include <stdio.h>
#include <string.h>

int CountChar(const char* src, char ch);
int ReplaceChar(char* dest, const char* src, char ch, char newCh);
int CountWord(const char* src, const char* word);
int ReplaceWord(char* dest, const char* src, const char* word, const char* newWord);

int main(void){
	//const char* text = "nanana!";
	

	char text[GIGA] ="";
	printf("Bitte Text eingeben: ");
	fgets(text, GIGA, stdin);
	printf("Suche nach Zeichen: ");
	char zeichen = "\0";
	scanf("%c\n", &zeichen);
	printf("Ersetze Zeichen: ");
	char ersatzzeichen = "\0";
	scanf("%c\n", &ersatzzeichen);
	//aufgabe 2
	if(text[0] == '\n') {
		int i = 0;
		char ersatz[] = "nanana!";
		while(i < 7 ) {
			text[i] = ersatz[i];
			i++;
		}
	}
	if(zeichen == '\n') {
		zeichen = 'a';
	}

	printf("Anzahl Zeichen \"%c\": %d", zeichen, CountChar(text, zeichen));
	
	//Aufgabe 3
	char neuertext[GIGA] ="";
	ReplaceChar(neuertext, text, zeichen, ersatzzeichen);
	printf("\nText ersetzt : %s", neuertext);
	
	//Aufgabe 6&7
	char wort[ZWO] ="";
	printf("Suche nach Wort: ");
	scanf("%s\n", &wort);
	printf("Anzahl Woerter \"%s\": %d", wort, CountWord(text, wort));
	
	//Aufgabe 8
	char nochneuertext[GIGA] ="";
	char neueswort[ZWO] ="";
	printf("\nErsetze \"%s\" durch : ", wort);
	scanf("%s\n", &neueswort);
	ReplaceWord(nochneuertext, text, wort, neueswort);
	printf("Text ersetzt : %s", nochneuertext);
	return 0;
}

int CountChar(const char* src, char ch) {
	int counter = 0;
	int i = 0;
	while (src[i] != '\0') {
		if(src[i] == ch) {
			counter++;
		}
		i++;
	}
	return counter;
}

int ReplaceChar(char* dest, const char* src, char ch, char newCh) {
	int counter = 0;
	int i = 0;
	while(src[i] != '\0') {
		if(src[i] == ch) {
			dest[i] = newCh;
			counter++;
		} else {
			dest[i] = src[i];
		}
		i++;
	}
	
	return counter;
}

int CountWord(const char* src, const char* word) {
	int counter = 0;
	int b = 0;
	int wortlaenge = strlen(word);
	for(int i = 0; i < strlen(src); i++) {
		b = 0;
		while (src[i + b] == word[b]) {
			b++;
			if(b == wortlaenge){
				counter++;
				i = i + b;
				b = 0;
			}	
		}
	}
	return counter;
}

int ReplaceWord(char* dest, const char* src, const char* word, const char* newWord) {
	int counter = 0;
	int b = 0;
	int wortlaenge = strlen(word);
	//Array durchlaufen
	for(int i = 0; i < strlen(src); i++) {
		b = 0;
		//gesamte Wortlaenge pruefen
		if(src[i + b] == word[b]) {
			while (src[i + b] == word[b]) {
				b++;
				if(b == wortlaenge){
					while (b > 0) {
						dest[i + b - 1] = newWord[b - 1];
						b--;
					}
					i = i + wortlaenge;
					counter++;
				}	
			}
		} else {
			dest[i] = src[i];
		}
	}
}