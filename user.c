#include "user.h"
int findMovie() {

	return -1;

}

struct BST_MOVIES * addToUserDB (struct user *pointerToUser, char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[], char startYear[], char endYear[], char runTime[], char genre[]) {

	int movieSearchResult = findMovie();

	//if movie is found print message saying it exists already
	if (movieSearchResult == 0) {
		printf("Movie is already in user database.\n");
	}

	else if (movieSearchResult == -1) {

		insertToMovieBST(pointerToUser->topOfUsersMovieTree, uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);
	}

	else {
		printf("There is logical issue with the function findMovie()\n returned %d", movieSearchResult);
	}

	return pointerToUser->topOfUsersMovieTree;

}

void printUserMenu() {
	printf("============User Menu=========");
}


