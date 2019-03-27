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

void printUserMenu(); //prints user menu
void createUser(struct user **, char[]); //creates a new user
void deleteUser(struct user **, char[]); //deletes a user
struct BST_MOVIES * addToUserDB(struct user *, char[], char[], char[], char[], char[], char[], char[], char[], char[]);	//after searching for title in the main DB add movie to userDB
void deletefromUserDB(struct user *, char[]); //remove movie from user's DB
struct BST_Movies * recursiveDeleteUserDB(struct BST_Movies *, char[]); //recursive function for delete
struct BST_Movies * minMovieVal(struct BST_Movies *); //returns movie's successor
void modifyUserDB(struct user *, char[]); //user can modify the date added and/or the type of copy they have
void previewUserDB(struct user  *); //prints user's DB to standard output
void downloadUserFile(struct user *, char[]); //prints user's DB to a file
int findMovie(); //looks for specific movie in user's movie database; returns 0 if found, -1 if not;
void printUserList(struct user *);
