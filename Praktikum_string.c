#include <stdio.h>

int CountChar(const char* src, char ch);
int ReplaceChar(char* dest, const char* src, char ch, char newCh);

int main(void){
	//const char* text = "nanana!";
	
	const char* text[50] = "";
	printf("Bitte Text eingeben: ");
	fgets(text, 50, stdin);
	printf("Suche nach Zeichen: ");
	char zeichen ="\n";
	scanf("%c", &zeichen);
	printf("Ersetze Zeichen: ");
	char ersatzzeichen ="\n";
	scanf("%c", &ersatzzeichen);
	//aufgabe 2
	if(text[0] == '\n') {
		printf("\nAnzahl \"%c\": %d", zeichen, CountChar("nanana!", "a"));
	} else {
		printf("\nAnzahl \"%c\": %d", zeichen, CountChar(text, zeichen));
	}
	//Aufgabe 3
	ReplaceChar(text, text, zeichen, ersatzzeichen);
	return 0;
}

int CountChar(const char* src, char ch) {
	int counter = 0;
	int i = 0;
	while (src[i] != '\n') {
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
	while(src[i] != '\n') {
		if(src[i] == ch) {
			dest[i] = newCh;
			counter++;
		}
		i++;
	}
	
	return counter;
}