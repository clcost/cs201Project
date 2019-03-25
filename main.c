//main.c
//#include "user.h"
#include "database.h"
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

	BST_MOVIES *parent = NULL;
	BST_MOVIES *left = NULL;
	BST_MOVIES *right = NULL;
	BST_MOVIES *topOfTree = NULL;
	
	FILE *fp = fopen("movie_records_sample", "r");

	printf("Creating IMDb Movie Database.\n");
	printf("Loading... (Please be patient, may take a couple minutes)\n");
 		
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

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);

		topOfTree = insertToMovieBST(topOfTree, uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);

		temp = fgetc(fp);
		fscanf(fp, "%s", uniqueId);			//read first catagory again

		if (feof(fp)) break; 				//if we are at end of file, break the loop

		fscanf(fp, "%s", titleType); 			//read second catagory again
	}

	printList(topOfTree);
	fclose(fp);
	printf("IMDb database created. Loading successful!\n\n");
	printf("Welcome to your customizable IMDb movie database!\n\n");
	printf("In this program you are able search through IMDb's movies and create your own unique database.\n\n");

	printf("Enter movie to search for:\n");
	char searchTitle[500];
	scanf("%s", searchTitle);
	struct BST_Movies *returnedSearch = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
	returnedSearch = NULL;
	returnedSearch = searchIMDb(topOfTree, searchTitle);
	if (returnedSearch == NULL) {
		printf("Movie does not exist.\n");
	}
	else {
		printf("Movie found.\n");
		printf("%s\t%s\t%s\n", returnedSearch->primTitle, returnedSearch->origTitle, returnedSearch->startYear);
	}

Mainmenu:
	printMainMenu();

	char option[10];
	scanf("%s", option);
	i = 0;
	while (option[i]) {					//makes option all lowercase for ease of reading
		option[i] = tolower(option[i]);
		i = i + 1;
	}
	
	printf("%s\n", option);
	if (strcmp(option, "quit") == 0) {
		printf("Goodbye!\n");
		goto End;
	}
	else if (strcmp(option, "create") == 0) {
		//do something with a new user and go to user menu

		goto Usermenu;
	}
	else if(strcmp(option, "login") == 0) {
		//login with existing user and jump to user menu
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
			goto Usermenu;
	}
	else if (strcmp(option, "add") == 0) {
		//add certain movie to user database
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
	else if (strcmp(option, "preview") == 0) {
		//prints user's database to standard output so he/she can review it before updating
		goto Usermenu;
	}
	else if (strcmp(option, "sort") == 0) {
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
