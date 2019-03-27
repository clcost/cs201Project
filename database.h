//database.h
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//need to form a tree rather than a linked list
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

	char dateAdded[10];
	char mediaType[8];

	struct BST_Movies * left;
	struct BST_Movies * right;
	struct BST_Movies * parent;
} BST_MOVIES;

void printMainMenu();
struct BST_Movies * insertToMovieBST(struct BST_Movies *, char[], char[], char[], char[], char[], char[], char[], char[], char[]);
const char * titleWithoutATheAnd(char[]);
struct BST_Movies * searchIMDb(struct BST_Movies *, char[]);
void printList(struct BST_Movies *);
