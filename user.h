//user.h Written by Coleman Cost CS201
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "database.h"

//Node for users
typedef struct user {
	char userName[100];

	struct BST_Movies* topOfUsersMovieTree; //pointer to top of User's DB Tree

	struct user* next;
	struct user* prev;
} user;

void printUserMenu(); //prints user menu
void createUser(struct user **, char[]); //creates a new user
void deleteUser(struct user **, char[]); //deletes a user
struct user * findUser(struct user **, char[]); //finds an existing user in order to log them in
struct BST_Movies * addToUserDB(struct user *, char[], char[], char[], char[], char[], char[], char[], char[], char[], char[], char[]);	//after searching for title in the main DB add movie to userDB
void deletefromUserDB(struct user *, char[]); //remove movie from user's DB
struct BST_Movies * recursiveDeleteUserDB(struct BST_Movies *, char[]); //recursive function for delete
struct BST_Movies * minMovieVal(struct BST_Movies *); //returns movie's successor
void modifyUserDB(struct BST_Movies *, char[], char[]); //user can modify the date added and/or the type of copy they have
void previewUserDB(struct BST_Movies  *); //prints user's DB to standard output
void downloadUserFile(struct BST_Movies *, FILE *); //prints user's DB to a file
void printUserList(struct user **); //prints username list
