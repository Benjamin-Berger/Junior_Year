#include <stdio.h>
#include <stdlib.h>
#include "time_functions.h"


int main(){
	char ch, inFile[50];
	char hc, outFile[50];
	FILE *inputFile;
	FILE *outputFile;
	int a;


	printf("Enter the input file: ");
	gets(inFile);

	printf("Enter the output file: ");
	gets(outFile);


	printf("Please type 0 or 1 to enter the coresponding modes: ");
	scanf("%d", &a);

	if(a == 0){
		inputFile = fopen(inFile, "r");
		outputFile = fopen(outFile, "w");
	
		int x;
		start_timing();
		while((x = fgetc(inputFile)) != EOF){
			fputc(x, outputFile);
		} 
		stop_timing();
		
		fclose(inputFile);
		fclose(outputFile);
	} else if(a==1) {
		char line[200];

		inputFile = fopen(inFile, "r");
		outputFile = fopen(outFile, "w");

		start_timing();
		while((fgets(line, 150, inputFile)) != NULL){
			fputs(line, outputFile);
		} 
		stop_timing();
		fclose(inputFile);
		fclose(outputFile);
	}

	printf("CPU time: %f\n", get_CPU_time_diff());
	printf("Wall time: %f\n", get_wall_clock_diff());

	printf("Type any key and Enter to close program. ");
	scanf("%d", &a);
}
