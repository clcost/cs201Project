//database.h
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct MovieDB {
	char uniqueId[20];
	char titleType[30];
	char primTitle[500];
	char origTitle[500];
	char adultFilm[3];
	char startYear[6];
	char endYear[6];
	char runTime[20];
	char genre[50];

	struct MovieDB* next;
	struct MovieDB* prev;
} MOVIEDB;

void printMainMenu();
void printList(struct MovieDB *);
struct MOVIEDB * createDatabase(char[], char[], char[], char[], char[], char[], char[], char[], char[], struct MovieDB *);     //constructor?
//MovieDB* returnSearch();
