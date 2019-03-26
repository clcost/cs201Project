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
	printf("==============================User Menu==============================\n");
	printf("Options\t\tDescription\n");
	printf("_____________________________________________________________________\n\n");
	printf("Search\t\tUser can search IMDb for a movie\n");
	printf("Add\t\tUser can add movie to their database\n");
	printf("Delete\t\tUser can delete a movie from their database\n");
	printf("Modify\t\tUser can modify a movie in their database\n");
	printf("Preview\t\tPrints user's database to standard output\n");
	printf("Download\tOutputs user's database to a file (Updates file if exists)\n");
	printf("Logout\t\tLog user out and return to Main Menu\n\n");
	printf("Please select an option above by typing in the command line.\n");


	return;
}

void createUser(struct user **firstUser, char userName[]) {
	struct user *new = (struct user*) malloc (sizeof(struct user));
	strcpy(new->userName, userName);
	new->topOfUsersMovieTree = (struct user*) malloc (sizeof(struct user));
	new->next = (struct user*) malloc (sizeof(struct user));
	new->prev = (struct user*) malloc (sizeof(struct user));

	new->topOfUsersMovieTree = NULL;
	new->next = NULL;
	new->prev = NULL;

	if (*firstUser == NULL) {
		*firstUser = new;
	}
	else {
		//set the prev attribute of our new user to last user in list

		//let the next attribute of our new user stay NULL

		//set the next attribute of the last user in the list to the new user
		int foundUser = -1;
		struct user *currentUser = (struct user*) malloc (sizeof(struct user));
		currentUser->next = (struct user*) malloc (sizeof(struct user));
		currentUser->prev = (struct user*) malloc (sizeof(struct user));
		currentUser = *firstUser;

		while (currentUser->next != NULL) {
			//finding last user in list
			currentUser = currentUser->next;
		}
		new->prev = currentUser;
		currentUser->next = new;
	}
}

void deleteUser(struct user **firstUser, char userName[]) {
	if (*firstUser == NULL) {
		printf("There are no users to delete.\n");
		return;
	}

	struct user *currentUser = (struct user*) malloc (sizeof(struct user));
	currentUser->next = (struct user*) malloc (sizeof(struct user));
	currentUser->prev = (struct user*) malloc (sizeof(struct user));
	currentUser = *firstUser;

	int nameFound = -1;

	//look at first name
	if (strcmp(userName, currentUser->userName) == 0) {
		nameFound = 0;
	}
	//search through users to find matching username
	while (nameFound == -1 && currentUser->next != NULL) {
		if (strcmp(userName, currentUser->userName) == 0) {
			nameFound = 0;
			break;
		}
		currentUser = currentUser->next;
	}

	if (nameFound != -1) {
	
		//we have found user
		//check if user is the first in the list
		if (currentUser->prev == NULL) {
			if (currentUser->next != NULL) {
				currentUser->next->prev = NULL;
				*firstUser = currentUser->next;
			}
			else {
				*firstUser = NULL;
			}
		}
		else if (currentUser->next == NULL) {
			currentUser->prev->next = NULL;
			currentUser->prev = NULL;
		}

		else {
			//set the next attribute of the prev user, to our found user's next attribute
			currentUser->prev->next = currentUser->next;
			//set the prev attribute of the next user, to our found user's prev attribute
			currentUser->next->prev = currentUser->prev;
		}
	}
	else {
		printf("User to delete does not exist.\n");
	}

	free(currentUser);
}

void printUserList(struct user *firstUser) {
	printf("Beginning of list\n");
	if (firstUser == NULL) {
		printf("No users exist.\n");
		return;
	}
	printf("%s\n", firstUser->userName);
	while (firstUser->next != NULL) {
		firstUser = firstUser->next;
		printf("%s\n", firstUser->userName);
	}
}

void deletefromUserDB(struct user * rootPtr, char movieTitle[]) {

}

void modifyUserDB(struct user * rootPtr, char movieTitle[]) {

}

void previewUserDB(struct user * rootPtr) {

}

void downloadUserFile(struct user * rootPtr, char userName[]) {

}
