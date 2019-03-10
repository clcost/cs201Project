#include "database.h"
//add movie from database file into local memory doubly linked list
struct MOVIEDB * createDatabase(char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[], char startYear[], char endYear[], char runTime[], char genre[], struct MovieDB *currentLastMovie) {
	//head and tail of all movies list
	struct MovieDB *head = NULL;

	//initialize single mvie structure and get first movie
	struct MovieDB *temp = (struct MovieDB*) malloc (sizeof(struct MovieDB));
	
	strcpy(temp->uniqueId, uniqueId);
	strcpy(temp->titleType, titleType);
	strcpy(temp->primTitle, primTitle);
	strcpy(temp->origTitle, origTitle);
	strcpy(temp->adultFilm, adultFilm);
	strcpy(temp->startYear, startYear);
	strcpy(temp->endYear, endYear);
	strcpy(temp->runTime, runTime);
	strcpy(temp->genre, genre);

	//if this is our first movie and ptr is null
	if (currentLastMovie == 0) {
		temp->next = NULL;
		temp->prev = NULL;
		currentLastMovie = temp;
		head = temp;
	}
	//else this is not our first movie
	else {
		//point this movie's prev pointer to our known last mvoie
		temp->next = NULL;
		temp->prev = currentLastMovie;

		//point the know last movie's next to here
		currentLastMovie->next = temp;
	}
	

//	if (*head == NULL) {
//		*head = temp;
//		*tail = temp;
//	}
//	else {
//		temp->next = NULL;
//		tail->next = temp;
//		*tail = temp;
	//	tail->next = temp;
	//	temp->prev = tail;
	//	tail = temp;
//	}



	return head;
}
