This is the README file for the project
Welcome to the IMDb database program written by Coleman Cost

Description:
This program creates a BST from the IMDb database file "title.basics.tsv". With that being said, the user of the program can perform a variety of tasks to create
their own custom movie database using the IMDb database. In the program, the user can create an account, log into that account, add/delete movies 
to their custom database, search the IMDb database, modify their custom database movies, print their database to standard output or download their
database to a file.

Instructions:
	1) Download programs files from https://github.com/clcost/cs201Project.git
	2) Place the directory into your Linux subsystem
	3) **IMPORTANT** You need to download the IMDb file from IMDb
		3a) In the same directory as the program enter "wget https://www.imdb.com/interfaces/title.basics.tsv" to download IMDb file
		3b) Next, unzip the file in your directory using any method you wish
		3c) In order to get just the movies, enter "grep "movie" title.basics.tsv > movie_records" This creates the file the program will read
		3d) Make sure the file "movie_records" is in the program directory
	4) Enter "make" which creates the executable for the program
	5) Enter "./runDBProject" which runs the executable and the program should start
	6) Once the program is started you will be brought to the Main Menu and have a variety of options to choose from below

Menu Options:

	Main Menu: 
		Create - Creates a new user database for the user to login into, once created the user may use the Login option to load their database
		Login - Logs an existing user into their freshly created database or datbase that has already been created (Directs user to User Menu) NOTE** user must already exist
		Quit - Terminates the program
	User Menu:
		Search - User can search the IMDb to find a movie NOTE** User must enter title exactly and titles are case-sensitive
		Add - User searches the IMDb and adds movie to their database
		Delete- User searches their database and can delete a movie
		Modify- User can modify a movie in their database (Change the Media type and the date they obtained the movie)
		Preview - Prints the User database to standard output
		Download - Prints the User database to a file (Updates file, if file already exists)
		Logout - Logs out user and the program returns to Main Menu

Instructional Video Link:

https://youtu.be/owtWEktRqnI


Contributing Works(Works Cited):
Used for BST algorithms:
Cormen, Thomas H.., et al. Introduction to Algorithms. 3rd ed.

https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/






