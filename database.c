#include "database.h"
//add movie from database file into local memory doubly linked list
struct BST_Movies * insertToMovieBST(struct BST_Movies *rootptr, char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[], char startYear[], char endYear[], char runTime[], char genre[], char dateAdded[], char mediaType[]) {

	//Allocate new memory for a new movie node
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
	strcpy(new->dateAdded, dateAdded);
	strcpy(new->mediaType, mediaType);

	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	
	//If movie is first movie in, make it the root
	if (rootptr == NULL) {
		rootptr = new;
	}
	//else put movie in correct position in BST
	else {
		//Allocate space for the currentMovie we are traversing on
		struct BST_Movies *currentMovie = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		currentMovie->right = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		currentMovie->left = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		currentMovie = rootptr;
		int i = 0;
		int endOfTitle = strlen(primTitle);
		int notPlaced = -1;
			
		while (notPlaced == -1) {
			
			//Compares titles letter by letter to ensure they are put in the exact right spot
			for (i = 0; i < endOfTitle; i = i + 1) {
				//Temporary char to hold the letters being compared from each title
				char currTreeChar = currentMovie->primTitle[i];
				char currnewChar = primTitle[i];
				
				//If title in tree is > new title go to left
				if (currTreeChar > currnewChar) {
					if (currentMovie->left == NULL) {
						currentMovie->left = new;
						new->parent = currentMovie;
						notPlaced = 0;
						break;
					}
					else {
						currentMovie = currentMovie->left;
						break;
					}
				}
				//If title in tree is < new title go to right
				else if (currTreeChar < currnewChar) {
					if (currentMovie->right == NULL) {
						currentMovie->right = new;
						new->parent = currentMovie;
						notPlaced = 0;
						break;
					}
					else {
						currentMovie = currentMovie->right;
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
					break;
				}
				else {
					currentMovie = currentMovie->right;
				}
			}
		}
	}
	return rootptr;
}

//Prints movies with all of their attributes
void printList(struct BST_Movies *start) {
	if (start == NULL) {
		return;
	}

	printList(start->left);

	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", start->uniqueId, start->titleType, start->primTitle, start->origTitle, start->adultFilm, start->startYear, start->endYear, start->runTime, start->genre);

	printList(start->right);

	return;
}

//makes the articles in front of title irrelevant when searching and sorting
char * titleWithoutATheAnd(char temp[]) {
	char *resultPtr;
	char result[500];
	char firstFour[4];
	int newIndex = 0;
	int oldIndex = 0;
	firstFour[0] = temp[0];
	firstFour[1] = temp[1];
	firstFour[2] = temp[2];
	firstFour[3] = temp[3];
	
	//Case for The
	if (firstFour[0] == 'T' && firstFour[1] == 'h' && firstFour[2] == 'e' && firstFour[3] == ' ') {
		for (int i = 4; i < strlen(temp); i = i + 1) {
			newIndex = i - 4;
			oldIndex = i;
			result[newIndex] = temp[oldIndex];
		}
	}
	//Case for And
	else if (firstFour[0] == 'A' && firstFour[1] == 'n' && firstFour[2] == 'd' && firstFour[3] == ' ') {
		for (int i = 4; i < strlen(temp); i = i + 1) {
				newIndex = i - 4;
				oldIndex = i;
				result[newIndex] = temp[oldIndex];
		}
	}
	//Case for A
	else if (firstFour[0] == 'A' && firstFour[1] == ' ') {
		for (int i = 2; i < strlen(temp); i = i + 1) {
			newIndex = i - 2;
			oldIndex = i;
			result[newIndex] = temp[oldIndex];
		}
	}

	else {
		//return entire title if none of the cases exist
		strcpy(result, temp);
		
	}
	resultPtr = result;
	return resultPtr;
}

//Searches the IMDb BST and user DB
struct BST_Movies * searchIMDb(struct BST_Movies *currentPtr, char searchTitle[]) {
		if (currentPtr == NULL) {
			return NULL;
		}

		//Recursive left
		if (currentPtr->primTitle[0] > searchTitle[0]) {
			return searchIMDb(currentPtr->left, searchTitle);
		}
		//compare char by char 
		else if (currentPtr->primTitle[0] == searchTitle[0]) {
			int searchTitleLength = strlen(searchTitle);
			for (int i = 1; i < searchTitleLength; i = i + 1) {
				//Recursive left
				if (currentPtr->primTitle[i] > searchTitle[i]) {
					return searchIMDb(currentPtr->left, searchTitle);
				}
				//Recursive right
				else if (currentPtr->primTitle[i] < searchTitle[i]) {
					return searchIMDb(currentPtr->right, searchTitle);
				}
			}
			//if here, title has been found
			if (strcmp(currentPtr->primTitle, searchTitle) == 0) {
				//return currentPtr;
				return currentPtr;
			}
		}
		//Recursive right
		else if (currentPtr->primTitle[0] < searchTitle[0]) {
			return searchIMDb(currentPtr->right, searchTitle);
		}
		//If movie not found, return NULL
		return NULL;

}

//Print Main Menu
void printMainMenu() {
	printf("==============================Main Menu==============================\n");
	printf("Options\t\tDescription\n");
	printf("_____________________________________________________________________\n\n");
	printf("Create\t\tCreate a new database for yourself\n");
	printf("Login\t\tIf you already have a database log back in to load it\n");
	printf("Quit\t\tExit out of program\n");

	return;
}
