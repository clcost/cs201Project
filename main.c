//main.c Written by Coleman Cost CS201Project
#include "user.h"

int main (void) {
	//temporary variables until stored in BST
	char uniqueId[20];
	char titleType[30];
	char primTitle[500];
	char origTitle[500];
	char adultFilm[3];
	char startYear[6];
	char endYear[6];
	char runTime[20];
	char genre[50];

	int i = 0;
	//Pointer to the first user created
	struct user *PointerToFirstUser = (struct user*) malloc (sizeof(struct user));
	PointerToFirstUser = NULL;
	//Pointer to selected user
	struct user *PointerToUser = (struct user*) malloc (sizeof(struct user));
	PointerToUser = NULL;
	//Pointer to the top of IMDb BST
	BST_Movies *topOfTree = NULL;
	//Open input file
	FILE *fp = fopen("movie_records", "r");

	printf("Creating IMDb Movie Database.\n");
	printf("Loading all IMDb Movies into BST database... (Please be patient)\n");
	//Begin reading input file and building BST
	while(1) {
		fscanf(fp, "%s", uniqueId);
		fscanf(fp, "%s", titleType);
		if (feof(fp)) break;
		fscanf(fp, " %[^\t]s", primTitle);
		fscanf(fp, " %[^\t]s", origTitle);
		fscanf(fp, "%s", adultFilm);
		fscanf(fp, "%s", startYear);
		fscanf(fp, "%s", endYear);
		fscanf(fp, "%s", runTime);
		fscanf(fp, "%s", genre);
		//Insert into IMDb BST
		topOfTree = insertToMovieBST(topOfTree, uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre, "empty", "empty");

	}
	//Close input file
	fclose(fp);

	printf("IMDb database created. Loading successful!\n\n");
	printf("Welcome to your customizable IMDb movie database!\n\n");
	printf("In this program you are able search through IMDb's movies and create your own unique database.\n\n");
	
	//Main Menu Options and Operations Below
	char userName[100];
	char titleName[500];

Mainmenu:
	printMainMenu();

	char option[10];
	scanf("%10s", option);
	i = 0;
	//Make option lowercase for ease of reading
	while (option[i]) {
		option[i] = tolower(option[i]);
		i = i + 1;
	}
	
	if (strcmp(option, "quit") == 0) {
		//Exits out of program if quit is entered
		printf("Goodbye!\n");
		goto End;
	}
	else if (strcmp(option, "create") == 0) {
		//Create a new user account
		printf("New User Creation: What is your name? (No whitespaces and max is 100 characters)\n");
		scanf("%100s", userName);

		//Send new user to createUser function
		createUser(&PointerToFirstUser, userName);
		printf("User Database created! Use the login option to log into your database.\n\n");
		
		goto Mainmenu;
	}
	else if(strcmp(option, "login") == 0) {
		//Login with existing user and jump to user menu
		//Prints user accounts and user must log into existing account or return to Main Menu
		printUserList(&PointerToFirstUser);
		printf("Please type an existing user: ");
		scanf("%100s", userName);
		PointerToUser = findUser(&PointerToFirstUser, userName);
		if (PointerToUser == NULL) {
			goto Mainmenu;
		}
		printf("Welcome back %s to the User Menu!\n\n", userName);

		goto Usermenu;
	}
	else {
		//If none of the options were entered above then return to Main Menu
		printf("Option does not exist! Check the Main Menu again.\n\n");
		goto Mainmenu;
	}
Usermenu:
	printUserMenu();

	scanf("%10s", option);
	i = strlen(option) - 1;
	//Make option lowercase for ease of reading
	while (i >= 0) {
		option[i] = tolower(option[i]);
		i = i - 1;
	}
	if (strcmp(option, "logout") == 0) {
		//Logs current user out and returns to main menu
		printf("Logging %s out. Returning to Main Menu.\n\n", PointerToUser->userName);
		goto Mainmenu;
	}
	else if (strcmp(option, "search") == 0) {
		//search IMDb database and print the result for user to look at
		//Pointer to the found movie in the IMDb BST
		struct BST_Movies *foundMoviePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		foundMoviePtr = NULL;

		//User inputs exact title they wish to search for
		printf("Please enter exact movie title to search for (titles are case-sensitive):\n");
		scanf(" %500[^\n]s", titleName);

		//Call searchIMDb function
		foundMoviePtr = searchIMDb(topOfTree, titleName);

		//If movie is not found
		if (foundMoviePtr == NULL) {
			printf("Movie does not exist in the IMDb. Returning to User Menu.\n\n");
		}
		//Movie is found and display movie to user
		else {
			printf("Movie found below:\n");
			printf("IMDb Id\tTitle Type\tPrimary Title\tOriginal Title\tAdult Film(1=Yes 0=No)\tStart Year\tEnd Year\tRun Time\tGenres\n");
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", foundMoviePtr->uniqueId, foundMoviePtr->titleType, foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->endYear, foundMoviePtr->runTime, foundMoviePtr->genre);
			printf("\n");
			printf("If you would like to add this movie to your personal database, then use the add option in User Menu.\n\n");
		}

		goto Usermenu;
	}
	else if (strcmp(option, "add") == 0) {
		//add certain movie to user database
		//searches IMDb database first then asks user for verification
		char mediaTypes[8];
		char dateObtained[12];
		char choiceYN[4];

		//Pointer to found movie
		struct BST_Movies *foundMoviePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		foundMoviePtr = NULL;

		//Ask user for movie to search for
		printf("Please enter exact movie title you wish to add (titles are case-sensitive):\n");
		scanf(" %500[^\n]s", titleName);

		//Call search function
		foundMoviePtr = searchIMDb(topOfTree, titleName);

		//If movie not found
		if (foundMoviePtr == NULL) {
			printf("Movie does not exist in the IMDb. Returing to User Menu.\n\n");
		}
		//Movie found
		else {
			printf("Movie found below:\n");
			printf("IMDb Id\tTitle Type\tPrimary Title\tOriginal Title\tAdult Film(1=Yes 0=No)\tStart Year\tEnd Year\tRun Time\tGenres\n");
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", foundMoviePtr->uniqueId, foundMoviePtr->titleType, foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->endYear, foundMoviePtr->runTime, foundMoviePtr->genre);
YN:
			//Ask for user verification
			printf("Is this the movie you wish to add to your database? (Yes or No)\n");
			scanf("%4s", choiceYN);
			int i = strlen(choiceYN) - 1;
			//Make choice lowercase for ease of reading
			while (i >= 0) {
				choiceYN[i] = tolower(choiceYN[i]);
				i = i - 1;
			}
			//If user did not enter correct input
			if (strcmp(choiceYN, "yes") != 0 && strcmp(choiceYN, "no") != 0) {
				printf("You did not enter Yes or No. Try again please.\n");
				goto YN;
			}
			//If user said no
			if (strcmp(choiceYN, "no") == 0) {
				printf("You did not want to add this movie. Returning to User Menu.\n\n");
				goto Usermenu;
			}
			//If user said yes
			else if(strcmp(choiceYN, "yes") == 0) {
				//Ask for user to put in date they obtained the movie and the type of copy they have
				printf("When is the date you acquired this movie? (Format mm/dd/yyyy)\n");
				scanf(" %11s", dateObtained);
				printf("What kind of copy did you obtain? (Choices: DVD, Blu-Ray, Digital, Other)\n");
				scanf(" %8s", mediaTypes);
				//insert into user's database
				PointerToUser->topOfUsersMovieTree = addToUserDB(PointerToUser, foundMoviePtr->uniqueId, foundMoviePtr->titleType, foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->endYear, foundMoviePtr->runTime, foundMoviePtr->genre, dateObtained, mediaTypes);

				printf("Movie was added to your personal database!\n");
				printf("After adding a new movie, your new database is show below: (Alphabetical Order)\n\n");
				printf("Primary Title\tOriginal Title\tRun Time\tGenre\tYear\tMedia Type\tDate Obtained\n\n");
				previewUserDB(PointerToUser->topOfUsersMovieTree);
				printf("Returning to User Menu.\n\n");
			}	
		}

		goto Usermenu;
	}
	else if (strcmp(option, "delete") == 0) {
		//deletes a certain movie from the user's database
		char choiceYN[4];
		//Pointer to found movie after search
		struct BST_Movies *foundMoviePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		foundMoviePtr = NULL;

		//Show user their database so they know which movie to delete
		printf("Your current database is listed below: (Alphabetical Order)\n\n");
		previewUserDB(PointerToUser->topOfUsersMovieTree);

		//Ask user for the title name they wish to delte
		printf("Please enter the exact movie title you wish to delete from your database (titles are case-sensitive):\n");
		scanf(" %500[^\n]s", titleName);

		foundMoviePtr = searchIMDb(PointerToUser->topOfUsersMovieTree, titleName);
		//If movie is not found
		if (foundMoviePtr == NULL) {
			printf("Movie does not exist in your database. Returning to User Menu.\n\n");
		}
		//Movie is found
		else {
			printf("The movie you want to delete is shown below:\n\n");
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", foundMoviePtr->titleType, foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->runTime, foundMoviePtr->genre, foundMoviePtr->dateAdded, foundMoviePtr->mediaType);
YN2:
			//Ask user for verification
			printf("Is this the movie you wish to delete from your database? (Yes or No)\n");
			scanf("%4s", choiceYN);
			int i = strlen(choiceYN) - 1;
			while (i >= 0) {
				choiceYN[i] = tolower(choiceYN[i]);
				i = i - 1;
			}
			//If user entered wrong input
			if (strcmp(choiceYN, "yes") != 0 && strcmp(choiceYN, "no") != 0) {
				printf("You did not enter Yes or No. Try again please.\n");
				goto YN2;
			}
			//User said no
			if (strcmp(choiceYN, "no") == 0) {
				printf("You did not want to delete this movie from your database. Returning to User Menu.\n\n");
				goto Usermenu;
			}
			//User said yes
			else if (strcmp(choiceYN, "yes") == 0) {
				//Call delete function
				deletefromUserDB(PointerToUser, titleName);
				printf("Movie deleted from your database!\n");
				printf("After deletion, here is your new database:\n\n");
				printf("Primary Title\tOriginal Title\tRun Time\tGenre\tYear\tMedia Type\tDate Obtained\n");
				previewUserDB(PointerToUser->topOfUsersMovieTree);
				printf("Returning to User Menu.\n\n");
			}
		}

		goto Usermenu;
	}
	else if (strcmp(option, "modify") == 0) {
		//User can modify their file and change date obtained and/or version of movie
		//User updates the day they obtained movie and the media type they own it on
		char newDateAdded[12];
		char newMediaType[8];
		char choiceYN[4];
		char titleToChange[500];

		//Pointer to found movie
		struct BST_Movies *foundMoviePtr = (struct BST_Movies*) malloc (sizeof(struct BST_Movies));
		foundMoviePtr = NULL;

		//List user's database so they can see their movies
		printf("Your current database is listed below: (Alphabetical Order)\n\n");
		previewUserDB(PointerToUser->topOfUsersMovieTree);
		printf("Please enter the exact movie title you wish to modify in your database (titles are case-sensitive):\n");
		scanf(" %500[^\n]s", titleToChange);

		//Call search function to find movie
		foundMoviePtr = searchIMDb(PointerToUser->topOfUsersMovieTree, titleToChange);

		//If movie not found
		if (foundMoviePtr == NULL) {
			printf("Movie does not exist in your database. Returning to User Menu.\n\n");
		}
		//Movie found
		else {
			printf("The movie you wish to modify is shown below:\n\n");
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", foundMoviePtr->primTitle, foundMoviePtr->origTitle, foundMoviePtr->adultFilm, foundMoviePtr->startYear, foundMoviePtr->runTime, foundMoviePtr->genre, foundMoviePtr->startYear, foundMoviePtr->dateAdded, foundMoviePtr->mediaType);
YN3:
			printf("Is this the movie you wish to modify in your database? (Yes or No)\n");
			scanf("%4s", choiceYN);
			int i = strlen(choiceYN) - 1;
			while (i >= 0) {
				choiceYN[i] = tolower(choiceYN[i]);
				i = i - 1;
			}
			//User entered incorrect input
			if (strcmp(choiceYN, "yes") != 0 && strcmp(choiceYN, "no") != 0) {
				printf("You did not enter Yes or No. Try again please.\n");
				goto YN3;
			}
			//User said no
			if (strcmp(choiceYN, "no") == 0) {
				printf("You did not want to modify this movie. Returning to User Menu.\n\n");

				goto Usermenu;
			}
			//User said yes
			else if (strcmp(choiceYN, "yes") == 0) {
				//Ask user what the wish the new attributes (date and type) to be 
				printf("What do you want the new date added to be? (Format mm/dd/yyyy)\n");
				scanf(" %11s", newDateAdded);
				printf("What do you want the new media type to be? (Choices: DVD, Blu-ray, Digital, Other)\n");
				scanf(" %8s", newMediaType);

				//Call modify function to update movie
				modifyUserDB(foundMoviePtr, newDateAdded, newMediaType);
				printf("Movie has been modified\n");
				printf("After modification, here is your new database:\n\n");
				printf("Primary Title\tOriginal Title\tRun Time\tGenre\tYear\tMedia Type\tDate Obtained\n\n");
				previewUserDB(PointerToUser->topOfUsersMovieTree);
				printf("Returning to User Menu.\n\n");
			}
		}
				
		goto Usermenu;
	}
	else if (strcmp(option, "preview") == 0) {
		//prints user's database to standard output so he/she can review it before updating
		printf("%s's custom movie database below: (Alphabetical Order)\n\n", PointerToUser->userName);
		printf("Primary Title\tOriginal Title\tRun Time\tGenre\tYear\tMedia Type\tDate Obtained\n\n");
		previewUserDB(PointerToUser->topOfUsersMovieTree);
		printf("Returning to User Menu.\n\n");
		goto Usermenu;
	}
	else if (strcmp(option, "download") == 0) {
		//prints user's database to a file
		char tempUserName[105];
		printf("Downloading user's database to a file.\n");
		strcpy(tempUserName, userName);
		strcat(tempUserName, ".log");

		FILE *fp = fopen(tempUserName, "w");
		fprintf(fp, "%s's Database File\n\n", userName);
		downloadUserFile(PointerToUser->topOfUsersMovieTree, fp);
		fclose(fp);
		printf("Download complete! File created is [%s]\n\n", tempUserName);
		goto Usermenu;
	}
	else {
		printf("Option does not exist! Check the User Menu options again.\n\n");
		goto Usermenu;
	}


End:
	return 0;
}
