#define GIGA 1024
#define ZWO 33
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
	
	if(text[0] == '\n' || text[0] == " ") {
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
	scanf("%32s\n", &wort);
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
	if(src == NULL) return -1;
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
	if(src == NULL) return -1;
	if(dest == NULL) return -1;
	int counter = 0;
	int i = 0;
	if(src[0] == '\0') {
		dest[0] == '\0';
	}
	while(src[0] != '\0') {
		if(src[0] == ch) {
			dest[0] = newCh;
			counter++;
		} else {
			dest[0] = src[0];
		}
		dest++;
		src++;
	}
	dest[0] = '\0';
	return counter;
}

int CountWord(const char* src, const char* word) {
	if(src == NULL) return -1;
	if(word == NULL) return -1;
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
	if(src == NULL || dest == NULL || newWord == NULL || word == NULL) return -1;
	if(src[0] == '\0') {
		dest[0] = '\0';
	}
	if(strstr(src, word) == NULL){
		for(int i = 0; i < strlen(src); i++) {
			dest[i] = src[i];
		}
	}
	int counter = 0;
	int b = 0;
	int wortlaenge = strlen(word);
	if(wortlaenge != strlen(newWord)) return -1;
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
			if(src[0] == '\0') {
				dest[i] = " ";
			}
			dest[i] = src[i];
		}
	}
	return counter;
}