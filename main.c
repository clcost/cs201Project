#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void) {

	//char menuOp[10];
	//char logName[20];
	char uniqueId[10];
	char titleType[30];
	char primTitle[500];
	char origTitle[500];
	char adultFilm[2];
	char startYear[5];
	char endYear[5];
	char runTime[10];
	char genre[40];
	char temp;

	int i = 0;

	FILE *fp = fopen("sample.basics.tsv", "r");
 
	fscanf(fp, "%s", uniqueId);
	fscanf(fp, "%s", titleType);
	printf("flag 1\n");
	while (1) {
		printf("flag 2\n");
	//	fscanf(fp, "%s", uniqueId);
	//	fscanf(fp, "%s", titleType);
		i = 0;
		while (1) {
			printf("flag 3\n");
			temp = fgetc(fp);
			if (temp <= 9) break;
			primTitle[i] = temp;
			i = i + 1;
		}
		i = 0;
		while (1) {
			printf("flag 4\n");
			temp = fgetc(fp); 
			if (temp <= 9) break;
			origTitle[i] = temp;
			i = i + 1;
		}
		printf("flag 5\n");

		fscanf(fp, "%s", adultFilm);
		fscanf(fp, "%s", startYear);
		fscanf(fp, "%s", endYear);
		fscanf(fp, "%s", runTime);
		fscanf(fp, "%s", genre);

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);
		
		temp = fgetc(fp);
		if (temp <= 9) break;

		fscanf(fp, "%s", uniqueId);
		fscanf(fp, "%s", titleType);
	
//		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", uniqueId, titleType, primTitle, origTitle, adultFilm, startYear, endYear, runTime, genre);
	}

	fclose(fp);

	return 0;

}
