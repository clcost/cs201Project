//database.h Written by Coleman Cost CS201
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//structure for IMDB Movies BST and User's BST
typedef struct BST_Movies {
	char uniqueId[20];
	char titleType[30];
	char primTitle[500];
	char origTitle[500];
	char adultFilm[3];
	char startYear[6];
	char endYear[6];
	char runTime[20];
	char genre[50];

	char dateAdded[12];
	char mediaType[8];

	struct BST_Movies * left;
	struct BST_Movies * right;
	struct BST_Movies * parent;
} BST_Movies;

void printMainMenu(); //Prints main menu to standard output
struct BST_Movies * insertToMovieBST(struct BST_Movies *, char[], char[], char[], char[], char[], char[], char[], char[], char[], char[], char[]); //Inserts movies into the BST
char * titleWithoutATheAnd(char[]); //Makes articles in front of titles irrelevant for searching and placing purposes
struct BST_Movies * searchIMDb(struct BST_Movies *, char[]); //searches the IMDb database in order to find a certain movie
void printList(struct BST_Movies *); //prints out movies to standard output but in a different format than previewUserDB
