//main.c
#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void) {

	char uniqueId[20];					//temporary variables for movie until stored in data structure
	char titleType[30];
	char primTitle[500];
	char origTitle[500];
	char adultFilm[3];
	char startYear[6];
	char endYear[6];
	char runTime[20];
	char genre[50];
	char temp;

	int i = 0;
	//FIX
	struct user *PointerToFirstUser = (struct user*) malloc (sizeof(struct user));
	PointerToFirstUser = NULL;

	struct user *PointerToUser = (struct user*) malloc (sizeof(struct user));
	PointerToUser = NULL;

	BST_MOVIES *topOfTree = NULL;
	
	FILE *fp = fopen("movie_records_sample", "r");

	printf("Creating IMDb Movie Database.\n");
	printf("Loading all IMDb Movies into BST database... (Please be patient, may take a couple minutes)\n");
 		
		fscanf(fp, "%s", uniqueId);			//scanning in uniqueId and titleType from file
		fscanf(fp, "%s", titleType);
		temp = fgetc(fp);
	
	while (1) {
		i = 0;
		
		while (1) {					//advancing fp to next word
			if (isalpha(temp)) break; 
			temp = fgetc(fp);
		}

		while (1) {					//reading primTitle in char by char (in order to include spaces)
			if (temp == '\t') break;
			primTitle[i] = temp;
			i = i + 1;
			temp = fgetc(fp);
		}
	
		primTitle[i] = '\0';
		i = 0;

		while (1) {					//advancing fp to next title
			if (isalpha(temp)) break;
			temp = fgetc(fp);
		}

		while (1) {					//reading origTitle in char by char (in order to include spaces)
			if (temp == '\t') break;
			origTitle[i] = temp;
			i = i + 1;
			temp = fgetc(fp);
		}
		origTitle[i] = '\0';

		fscanf(fp, "%s", adultFilm);			//reading in the rest of the variables from file
		fscanf(fp, "%s", startYear);
		fscanf(fp, "%s", endYear);
		fscanf(fp, "%s", runTime);
		fscanf(fp, "%s", genre);

		topOfTree = insertToMovieBST(topOfTree, uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);

		temp = fgetc(fp);
		fscanf(fp, "%s", uniqueId);			//read first catagory again

		if (feof(fp)) break; 				//if we are at end of file, break the loop

		fscanf(fp, "%s", titleType); 			//read second catagory again
	}

	fclose(fp);

	printf("IMDb database created. Loading successful!\n\n");
	printf("Welcome to your customizable IMDb movie database!\n\n");
	printf("In this program you are able search through IMDb's movies and create your own unique database.\n\n");
	
	/*char userName1[100];
	while (1) { //while quit is not entered, the function keeps asking for names to be added to list
		printf("Add a username: ");
		scanf("%s", userName1);
		if (strcmp(userName1, "quit") == 0) break;
		createUser(&PointerToFirstUser, userName1);
	}
	printUserList(&PointerToFirstUser); //prints the list before any deletes
	printf("Enter a username to delete: ");
	scanf("%s", userName1);
	deleteUser(&PointerToFirstUser, userName1);
	printUserList(&PointerToFirstUser); //prints the list after delete
	*/
/*	printf("Enter movie to search for:\n");
	char searchTitle[500];
	scanf("%[^\n]s", searchTitle);
	printf("[%s]", searchTitle);
	struct BST_Movies *returnedSearch = (struct BST_Movies*) malloc (sizeof(struct BST_Movies)); //(struct BST_Movies*) malloc (sizeof(struct BST_Movies));

	returnedSearch = searchIMDb(topOfTree, searchTitle);
	if (returnedSearch == NULL) printf("Why is this NULL???\n");

//	if (returnedSearch == NULL) {
//		printf("Movie does not exist.\n");
//	}
	if (returnedSearch != NULL) {
		printf("Movie found.\n");
		printf("%s\t%s\t%s\n", returnedSearch->primTitle, returnedSearch->origTitle, returnedSearch->startYear);
	}
	else {
		printf("Movie does not exist.\n");
	}
*/
	char userName[100];
	char titleName[500];

Mainmenu:
	printMainMenu();

	char option[10];
	scanf("%10s", option);
	i = 0;
	while (option[i]) {					//makes option all lowercase for ease of reading
		option[i] = tolower(option[i]);
		i = i + 1;
	}
	
	printf("%s\n", option);
	if (strcmp(option, "quit") == 0) {
		//exits out of program
		printf("Goodbye!\n");
		goto End;
	}
	else if (strcmp(option, "create") == 0) {
		//do something with a new user and go to user menu
		//char userName[100];
		printf("New User Creation: What is your name? (Please use first name and max is 100 characters)\n");
		scanf("%s", userName);
		createUser(&PointerToFirstUser, userName);
		printf("Welcome %s to the User Menu!\n", userName);
		
		goto Usermenu;
	}
	else if(strcmp(option, "login") == 0) {
		//login with existing user and jump to user menu
		printUserList(&PointerToFirstUser);
		printf("Please type an existing user: ");
		scanf("%s", userName);
		PointerToUser = findUser(&PointerToFirstUser, userName);
		if (PointerToUser == NULL) {
			goto Mainmenu;
		}
		printf("Welcome back %s to the User Menu!\n", userName);

		goto Usermenu;
	}
	else {
		printf("Option does not exist! Check the Main Menu again.\n\n");
		goto Mainmenu;
	}
Usermenu:
	printUserMenu();

	scanf("%s", option);
	i = 0;
	while (option[i]) {
		option[i] = tolower(option[i]);
		i = i + 1;
	}
	if (strcmp(option, "logout") == 0) {
		printf("Logging user out. Returning to Main Menu.\n\n");
		goto Mainmenu;
	}
	else if (strcmp(option, "search") == 0) {
		//search IMDb database and print results for user to look at
		//char titleName[500];
		struct BST_Movies *foundMoviePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		foundMoviePtr = NULL;
		printf("Please enter exact movie title to search for (titles are case-sensitive):\n");
		scanf(" %[^\n]s", titleName);
		printf("[%s]", titleName);
		foundMoviePtr = searchIMDb(topOfTree, titleName);
		if (foundMoviePtr == NULL) {
			printf("Movie does not exist in the IMDb. Returning to User Menu.\n\n");
		}
		else {
			printf("Movie found below:\n");
			printf("IMDb Id\tTitle Type\tPrimary Title\tOriginal Title\tAdult Film(1=Yes 0=No)\tStart Year\tEnd Year\tRun Time\tGenres\n");
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", foundMoviePtr->uniqueId, foundMoviePtr->titleType, foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->endYear, foundMoviePtr->runTime, foundMoviePtr->genre);
			printf("\n");
			printf("If you would like to add this movie to your personal database, then use the add option in User Menu.\n");
		}

		goto Usermenu;
	}
	else if (strcmp(option, "add") == 0) {
		//add certain movie to user database
		char mediaTypes[8];
		char dateObtained[10];
		char choiceYN[4];

		struct BST_Movies *foundMoviePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		foundMoviePtr = NULL;

		printf("Please enter exact movie title you wish to add (titles are case-sensitive):\n");
		scanf(" %[^\n]s", titleName);
		printf("{%s}", titleName);
		foundMoviePtr = searchIMDb(topOfTree, titleName);
		if (foundMoviePtr == NULL) {
			printf("Movie does not exist in the IMDb. Returing to User Menu.\n\n");
		}
		else {
			printf("Movie found below:\n");
			printf("IMDb Id\tTitle Type\tPrimary Title\tOriginal Title\tAdult Film(1=Yes 0=No)\tStart Year\tEnd Year\tRun Time\tGenres\n");
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", foundMoviePtr->uniqueId, foundMoviePtr->titleType, foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->endYear, foundMoviePtr->runTime, foundMoviePtr->genre);
YN:
			printf("Is this the movie you wish to add to your database? (Yes or No)\n");
			scanf(" %s", choiceYN);
			strcpy(choiceYN, tolower(choiceYN));
			if (strcmp(choiceYN, "yes") != 0 || strcmp(choiceYN, "no") != 0) {
				printf("You did not enter Yes or No. Try again please.\n");
				goto YN;
			}
			if (strcmp(choiceYN, "no" == 0)) {
				printf("You did not want to add this movie. Returning to User Menu.\n\n");
				goto Usermenu;
			}



		}


		goto Usermenu;
	}
	else if (strcmp(option, "delete") == 0) {
		//deletes a certain movie from the user's database
		goto Usermenu;
	}
	else if (strcmp(option, "update") == 0) {
		//rewrites user file to the file is updated based on what the user has added or deleted
		goto Usermenu;
	}
	else if (strcmp(option, "modify")) {
		//User can modify their file and change date obtained and/or version of movie
		goto Usermenu;
	}
	else if (strcmp(option, "preview") == 0) {
		//prints user's database to standard output so he/she can review it before updating
		goto Usermenu;
	}
	else if (strcmp(option, "download") == 0) {
		//sorts users database by title using some sort of sorting algorithm that is efficient
		goto Usermenu;
	}
	else {
		printf("Option does not exist! Check the User Menu options again.\n\n");
		goto Usermenu;
	}


End:
	return 0;
}
