#include "database.h"
//add movie from database file into local memory doubly linked list
struct BST_Movies * insertToMovieBST(struct BST_Movies *rootptr, char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[], char startYear[], char endYear[], char runTime[], char genre[]) {
	printf("begin function\n");
	struct BST_Movies *new = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	new->parent = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	new->left = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	new->right = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));

	strcpy(new->uniqueId, uniqueId);
	strcpy(new->titleType, titleType);
	strcpy(new->primTitle, primTitle);
	strcpy(new->origTitle, origTitle);
	strcpy(new->adultFilm, adultFilm);
	strcpy(new->startYear, startYear);
	strcpy(new->endYear, endYear);
	strcpy(new->runTime, runTime);
	strcpy(new->genre, genre);

	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	
	char newTitleWOATheAnd[500];
	char currentTitleWOATheAnd[500]; 
	const char *temp = titleWithoutATheAnd(primTitle);
	
	strcpy(newTitleWOATheAnd, &temp);

	printf("flag 1\n");

	//If rootptr is NULL
	if (rootptr == NULL) {
		rootptr = new;
		printf("Movie is placed root\n");
	}
	//else put movie in correct position in BST
	else {
		struct BST_Movies *currentMovie = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		currentMovie->right = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		currentMovie->left = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		currentMovie = rootptr;
		int i = 0;
		int endOfTitle = strlen(newTitleWOATheAnd);
		int notPlaced = -1;
			
		while (notPlaced == -1) {
			char currentTitleWOATheAnd[500];
			temp = titleWithoutATheAnd(currentMovie->primTitle);
		        strcpy(currentTitleWOATheAnd, &temp);

			for (i = 0; i < endOfTitle; i = i + 1) {
				char currTreeChar = currentTitleWOATheAnd[i];
				printf("%c\n", currTreeChar);
				char currnewChar = newTitleWOATheAnd[i];
				printf("%c\n", currnewChar);

				if (currTreeChar > currnewChar) {
					if (currentMovie->left == NULL) {
						currentMovie->left = new;
						new->parent = currentMovie;
						notPlaced = 0;
						printf("Movie is placed left\n");
						break;
					}
					else {
						currentMovie = currentMovie->left;
						printf("flag 2\n");
						break;
					}
				}

				else if (currTreeChar < currnewChar) {
					if (currentMovie->right == NULL) {
						currentMovie->right = new;
						new->parent = currentMovie;
						notPlaced = 0;
						printf("Movie is placed right\n");
						break;
					}
					else {
						currentMovie = currentMovie->right;
						printf("flag 3\n");
						break;
					}
				}
			}
			//If titles are equal place to the right
			if (i == endOfTitle) {
				if (currentMovie->right == NULL) {
					currentMovie->right = new;
					new->parent = currentMovie;
					notPlaced = 0;
					printf("Movie is placed right\n");
					break;
				}
				else {
					currentMovie = currentMovie->right;
					printf("flag 4\n");
				}
			}
		}
	}
	printf("end of function\n");
	return rootptr;
}
	
void printList(struct BST_Movies *start) {
	struct BST_Movies *current = start;
	if (start == NULL) {
		return;
	}

	printList(start->left);

	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", start->uniqueId, start->titleType, start->primTitle, start->origTitle, start->adultFilm, start->startYear, start->endYear, start->runTime, start->genre);

	printList(start->right);

	return;
}

const char * titleWithoutATheAnd(char temp[]) {
	char result[500];
	char firstFour[4];
	int newIndex = 0;
	int oldIndex = 0;
	firstFour[0] = temp[0];
	firstFour[1] = temp[1];
	firstFour[2] = temp[2];
	firstFour[3] = temp[3];

	if (firstFour[0] == 'T' && firstFour[1] == 'h' && firstFour[2] == 'e' && firstFour[3] == ' ') {
		for (int i = 4; i <= strlen(temp); i = i + 1) {
			newIndex = i - 4;
			oldIndex = i;
			result[newIndex] = temp[oldIndex];
		}
	}
	else if (firstFour[0] == 'A' && firstFour[1] == 'n' && firstFour[2] == 'd' && firstFour[3] == ' ') {
		for (int i = 4; i <= strlen(temp); i = i + 1) {
				newIndex = i - 4;
				oldIndex = i;
				result[newIndex] = temp[oldIndex];
		}
	}

	else if (firstFour[0] == 'A' && firstFour[1] == ' ') {
		for (int i = 2; i <= strlen(temp); i = i + 1) {
			newIndex = i - 2;
			oldIndex = i;
			result[newIndex] = temp[oldIndex];
		}
	}

	else {
		//return entire title if none of the cases exist
		strcpy(result, temp);
		
	}
	printf("%s\n", result);
	return *result;
}

struct BST_Movies * searchIMDb(struct BST_Movies *currentPtr, char searchTitle[]) {
		if (currentPtr == NULL) {
			return NULL;
		}

		else if (currentPtr->primTitle[0] > searchTitle[0]) {
			searchIMDb(currentPtr->left, searchTitle);
		}
		else if (currentPtr->primTitle[0] == searchTitle[0]) {
			int searchTitleLength = strlen(searchTitle);
			int found = 0;
			for (int i = 1; i < searchTitleLength; i = i + 1) {
				if (currentPtr->primTitle[i] > searchTitle[i]) {
					searchIMDb(currentPtr->left, searchTitle);
				}
				else if (currentPtr->primTitle[i] < searchTitle[i]) {
					searchIMDb(currentPtr->right, searchTitle);
				}
			}
			//if here, title has been found
			return currentPtr;
		}
		else if (currentPtr->primTitle[0] < searchTitle[0]) {
			searchIMDb(currentPtr->right, searchTitle);
		}
		//If movie not found, return NULL
		return NULL;

}

void printMainMenu() {
	printf("==========Main Menu==========\n\n");
	printf("Options\t\tDescription\n");
	printf("_____________________________\n\n");
	printf("Create\t\tCreate a new database for yourself\n");
	printf("Login\t\tIf you already have a database log back in to load it\n");
	printf("Quit\t\tExit out of program\n");

	return;
}
