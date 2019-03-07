//main.c for cs201Project written by Coleman Cost
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

	int count = 0;
	int i = 0;

	FILE *fp = fopen("movie_records_sample", "r");
 		
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

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre); //testing the variables that were just read in
		count = count + 1;
		
		temp = fgetc(fp);
		fscanf(fp, "%s", uniqueId);			//read first catagory again

		if (feof(fp)) {printf("%d BROKE THE LOOP\n", count); break; } //if we are at end of file, break the loop

		fscanf(fp, "%s", titleType); 			//read second catagory again
	}

	fclose(fp);

	return 0;
}
