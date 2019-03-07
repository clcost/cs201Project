#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void) {

	char uniqueId[20];
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

	FILE *fp = fopen("sample.basics.tsv", "r");
 		
		fscanf(fp, "%s", uniqueId); printf("|%s|\n", uniqueId);
		fscanf(fp, "%s", titleType); printf("|%s|\n", titleType);
		temp = fgetc(fp);
	
	while (1) {
		//fscanf(fp, "%s", uniqueId);
		//fscanf(fp, "%s", titleType);
		i = 0;
		//temp = fgetc(fp);
		
		while (1) {
			if (!isspace(temp)) break; 
			temp = fgetc(fp);
		}
		printf("ffs\n");
		while (1) {
			if (temp == '\t') break;
			primTitle[i] = temp;
			i = i + 1;
			temp = fgetc(fp);
		}
	
		primTitle[i] = '\0'; printf("[%s]\n", primTitle);
		i = 0;
		temp = fgetc(fp);

		while (1) {
			if (!isspace(temp)) break;
			temp = fgetc(fp);
		}

		while (1) {
			if (temp == '\t') break;
			origTitle[i] = temp;
			i = i + 1;
			temp = fgetc(fp);
		}
		origTitle[i] = '\0'; printf("[%s]\n", origTitle);
		//i = 0;
		//temp = fgetc(fp);

		fscanf(fp, "%s", adultFilm); printf("(%s)\n", adultFilm);
		fscanf(fp, "%s", startYear);
		fscanf(fp, "%s", endYear);
		fscanf(fp, "%s", runTime);
		fscanf(fp, "%s", genre); printf("(%s)\n", genre);

		printf("%s %s %s %s %s %s %s %s %s\n", uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);
		count = count + 1;
		temp = fgetc(fp);
		if (temp == -1) {printf("%d BROKE THE LOOP\n", count); break; }

		fscanf(fp, "%s", uniqueId);
		fscanf(fp, "%s", titleType);
	}
	printf("%d\n", count);
	fclose(fp);

	return 0;
}
