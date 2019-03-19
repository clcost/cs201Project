//user.h
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "database.h"

typedef struct user {
	char userName[100];
	struct MovieDB* moviesOfUser; //pointer to start of userDB
	struct MovieDB* tailOfMoviesOfUser; //pointer the the end of user's database

	struct user* next;
	struct user* prev;
} USER;

void printUserMenu();
void createUser();
void deleteUser();
void addMovie(struct user *, char[], char[], char[], char[], char[], char[], char[], char[], char[]);
struct MOVIEDB * addToUserDB();	//after searching for title in the main DB add movie to userDB
void deletefromUserDB(); //remove movie from user's DB
void updateUserDB(); //update user DB by rewriting to the user's file
void sortUserDB(); //sort user database by title
void printUserFile();
int findMovie(); //looks for specific movie in user's movie database; returns 0 if found, -1 if not;
