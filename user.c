#include "user.h"
int findMovie() {

	return -1;

}

struct MOVIEDB * addToUserDB (struct user *pointerToUser, char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[],char startYear[], char endYear[], char runTime[], char genre[], struct UserDB *currentLastMovie) {

	int movieSearchResult = findMovie();

	//if movie is found print message saying it exists already
	if (movieSearchResult == 0) {
		printf("Movie is already in user database.\n");
	}

	else if (movieSearchResult == -1) {

		addMovie(pointerToUser, uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);
	}

	else {
		printf("There is logical issue with the function findMovie()\n returned %d", movieSearchResult);
	}

	return pointerToUser->moviesOfUser;

}

void addMovie(struct user *pointerToUser, char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[],char startYear[], char endYear[], char runTime[], char genre[]) {

	//get header and tail of user's DB
	struct MovieDB *head = pointerToUser->moviesOfUser;
	struct MovieDB *tail = pointerToUser->tailOfMoviesOfUser;

	struct MovieDB *temp = (struct Movie*) malloc (sizeof(struct MovieDB));

	strcpy(temp->uniqueId, uniqueId);
	strcpy(temp->titleType, titleType);
	strcpy(temp->primTitle, primTitle);
	strcpy(temp->origTitle, origTitle);
	strcpy(temp->adultFilm, adultFilm);
	strcpy(temp->startYear, startYear);
	strcpy(temp->endYear, endYear);
        strcpy(temp->runTime, runTime);
	strcpy(temp->genre, genre);


	if (tail == 0) {
		temp->next = NULL;
		temp->prev = NULL;
		tail = temp;
		head = temp;
	}
	else {
		temp->next = NULL;
		temp->prev = tail;

		tail = temp;
	}
}
