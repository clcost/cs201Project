#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct movie {
	void **data;
	char uniqueId[10];
	char titleType[20];
	char titleName[200];
	bool adultFilm;
	int startYear;
	int endYear;
	int runTime;
	char genreOne[15];
	char genreTwo[15];
	char genreThree[15];

} MOVIE;

MOVIE *newMovie() {
	MOVIE *newMovie;
	newMovie = (MOVIE *)malloc(sizeof(MOVIE));
	newMovie->data = NULL;
	strcpy(newMovie->uniqueId, "\0");
	strcpy(newMovie->titleType, "\0");
	strcpy(newMovie->titleName, "\0");
	newMovie->adultFilm = 0;
	newMovie->startYear = 0;
	newMovie->endYear = 0;
	newMovie->runTime = 0;
	strcpy(newMovie->genreOne, "\0");
	strcpy(newMovie->genreTwo, "\0");
	strcpy(newMovie->genreThree, "\0");

	return newMovie;
}


int main (void) {

	char menuOp[10];
	char logName[20];
	printf("Welcome to the IMDb database! In this program you may create your own custom movie database.\n");
	printf("What would you like your custome database to be named?\n");
	
	while (strcmp(menuOp, "Exit") != 1 || strcmp(menuOp, "exit") != 1) {

	}

}
