//user.h
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "database.h"
//in the user database we only need title, genre, runTime, and year released
//then the user will input if they own it on dvd bluray or digital and the date they obtained the movie through std input
typedef struct user {
	char userName[100];
	struct BST_MOVIES* topOfUsersMovieTree; //pointer to top of User's DB Tree

	struct user* next;
	struct user* prev;
} USER;

void printUserMenu();
void createUser();
void deleteUser();
struct BST_MOVIES * addToUserDB(struct user *, char[], char[], char[], char[], char[], char[], char[], char[], char[]);	//after searching for title in the main DB add movie to userDB
void deletefromUserDB(); //remove movie from user's DB
void updateUserDB(); //update user DB by rewriting to the user's file
void sortUserDB(); //sort user database by title
void printUserFile();
int findMovie(); //looks for specific movie in user's movie database; returns 0 if found, -1 if not;
