#include "user.h"
//Function for adding to user's BST
struct BST_Movies * addToUserDB (struct user *pointerToUser, char uniqueId[], char titleType[], char primTitle[], char origTitle[], char adultFilm[], char startYear[], char endYear[], char runTime[], char genre[], char dateAdded[], char mediaType[]) {
	//User insertToMovieBST to insert to user database
	return insertToMovieBST(pointerToUser->topOfUsersMovieTree, uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre, dateAdded, mediaType);

}

//Function prints the user menu to standard output
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

//Function finds user in order to login
struct user * findUser(struct user **firstUser, char userName[]) {
	//Pointer to the user the function is looking at
	struct user *currentUser = (struct user*) malloc (sizeof(struct user));
	currentUser->topOfUsersMovieTree = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	currentUser->next = (struct user*) malloc (sizeof(struct user));
	currentUser->prev = (struct user*) malloc (sizeof(struct user));

	currentUser = *firstUser;
	//When nameFound == 0, funcion has found the user we were looking for
	int nameFound = -1;

	if (strcmp(userName, currentUser->userName) == 0) {
		nameFound = 0;
	}

	while (nameFound == -1 && currentUser->next != NULL) {
		if (strcmp(userName, currentUser->userName) == 0) {
			nameFound = 0;
			break;
		}
		currentUser = currentUser->next;
	}

	if (strcmp(userName, currentUser->userName) == 0) {
		nameFound = 0;
	}

	if (nameFound != -1) {
		return currentUser;
	}
	//If we are here, then user was not found
	else {
		printf("User could not be found. Returning to Main Menu.\n");
		return NULL;
	}
}

//Function creates new user
void createUser(struct user **firstUser, char userName[]) {
	//Allocate memory for the new user structure
	struct user *new = (struct user*) malloc (sizeof(struct user));
	strcpy(new->userName, userName);
	new->topOfUsersMovieTree = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	new->next = (struct user*) malloc (sizeof(struct user));
	new->prev = (struct user*) malloc (sizeof(struct user));

	new->topOfUsersMovieTree = NULL;
	new->next = NULL;
	new->prev = NULL;
	//If this is our first user then make the first user ptr == the new user
	if (*firstUser == NULL) {
		*firstUser = new;
	}
	else {
		//set the prev attribute of our new user to last user in list
		//let the next attribute of our new user stay NULL
		//set the next attribute of the last user in the list to the new user
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

//Function deletes a user account
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

	//check last user if name is still not found
	if (strcmp(userName, currentUser->userName) == 0) {
		nameFound = 0;
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
			free(currentUser);
		}
		else if (currentUser->next == NULL) {
			currentUser->prev->next = NULL;
			currentUser->prev = NULL;
			free(currentUser);
		}

		else {
			//set the next attribute of the prev user, to our found user's next attribute
			currentUser->prev->next = currentUser->next;
			//set the prev attribute of the next user, to our found user's prev attribute
			currentUser->next->prev = currentUser->prev;
			free(currentUser);
		}
	}
	else {
		printf("User to delete does not exist.\n");
	}
}

//Prints the user accounts to standard output
void printUserList(struct user **firstUser) {
	//If no users exist
	if (*firstUser == NULL) {
		printf("No users exist.\n");
		return;
	}
	//Create pointer for thet user we are looking at in memory
	struct user *currentUser = (struct user*) malloc (sizeof(struct user));
	currentUser->next = (struct user*) malloc (sizeof(struct user));
	currentUser->prev = (struct user*) malloc (sizeof(struct user));
	currentUser = *firstUser;

	printf("Beginning of User List: ");
	printf("%s ", currentUser->userName);
	while (currentUser->next != NULL) {
		currentUser = currentUser->next;
		printf("%s ", currentUser->userName);
	}
	printf("\n");

}

//Delete from User's BST database
void deletefromUserDB(struct user * rootPtr, char movieTitle[]) {
	if (rootPtr == NULL) {
		printf("User's database is empty.\n");
		return;
	}

	struct BST_Movies *deletePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	deletePtr = searchIMDb(rootPtr->topOfUsersMovieTree, movieTitle);
	
	if (deletePtr == NULL) {
		printf("Movie was not found; therefor, nothing to delete.\n");
		return;
	}
	
	//Call recursive delete function in order to keep tree maintained
	struct BST_Movies *newRoot = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	newRoot = recursiveDeleteUserDB(rootPtr->topOfUsersMovieTree, movieTitle);
	//set user's new topOfMovieTree
	rootPtr->topOfUsersMovieTree = newRoot;
	

}

//Called by function above and maintains tree order when a node is deleted
struct BST_Movies * recursiveDeleteUserDB(struct BST_Movies *rootPtr, char movieTitle[]) {
	//DeletePtr traverses through tree for the delete node
	struct BST_Movies *deletePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	deletePtr->right = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	deletePtr->left = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	deletePtr->parent = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));

	//if tree is empty
	if (rootPtr == NULL) {
		return rootPtr;
	}

	if (strcmp(movieTitle, rootPtr->primTitle) < 0) {
	       rootPtr->left = recursiveDeleteUserDB(rootPtr->left, movieTitle);
	}
	else if (strcmp(movieTitle, rootPtr->primTitle) > 0) {
		rootPtr->right = recursiveDeleteUserDB(rootPtr->right, movieTitle);
	}	

	else {
		//check if movie has only one child or no child
		if (rootPtr->left == NULL) {
			struct BST_Movies *temp = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
			temp = rootPtr->right;
			free(rootPtr);
			return temp;
		}

		else if (rootPtr->right == NULL) {
			struct BST_Movies *temp = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
			temp = rootPtr->left;
			free(rootPtr);
			return temp;
		}

		//movie with two children
		//get inorder successor
		struct BST_Movies *temp = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		temp = minMovieVal(rootPtr->right);
		
		strcpy(temp->uniqueId, rootPtr->uniqueId);
		strcpy(temp->titleType, rootPtr->titleType);
		strcpy(temp->primTitle, rootPtr->primTitle);
		strcpy(temp->origTitle, rootPtr->origTitle);
		strcpy(temp->adultFilm, rootPtr->adultFilm);
		strcpy(temp->startYear, rootPtr->startYear);
		strcpy(temp->endYear, rootPtr->endYear);
		strcpy(temp->runTime, rootPtr->runTime);
		strcpy(temp->genre, rootPtr->genre);
		strcpy(temp->dateAdded, rootPtr->dateAdded);
		strcpy(temp->mediaType, rootPtr->mediaType);

		recursiveDeleteUserDB(rootPtr->right, temp->primTitle);
	}
	return rootPtr;
}

//Function returns the successor to a node
struct BST_Movies * minMovieVal(struct BST_Movies *ptr) {
	struct BST_Movies *currentPtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	currentPtr = ptr;

	while (currentPtr->left != NULL) {
		currentPtr = currentPtr->left;
	}

	return currentPtr;
}

//Function modifies a movie node in a user's database
void modifyUserDB(struct BST_Movies *rootPtr, char newDateAdded[], char newMediaType[]) {
	if (rootPtr == NULL) {
		return;
	}
	
	//Update dat and type for the desired new variables
	strcpy(rootPtr->dateAdded, newDateAdded);
	strcpy(rootPtr->mediaType, newMediaType);
}

//Prints user's database to standard output
void previewUserDB(struct BST_Movies *rootPtr) {
	if (rootPtr == NULL) {
		return;
	}

	previewUserDB(rootPtr->left);

	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", rootPtr->primTitle, rootPtr->origTitle, rootPtr->runTime, rootPtr->genre, rootPtr->startYear, rootPtr->mediaType, rootPtr->dateAdded);

	previewUserDB(rootPtr->right);

	return;
}

//Prints user's database to a file
void downloadUserFile(struct BST_Movies *rootPtr, FILE *fp) {
	if (rootPtr == NULL) {
		return;
	}

	downloadUserFile(rootPtr->left, fp);

	fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n", rootPtr->primTitle, rootPtr->origTitle, rootPtr->runTime, rootPtr->genre, rootPtr->startYear, rootPtr->mediaType, rootPtr->dateAdded);

	downloadUserFile(rootPtr->right, fp);

	return;
}
