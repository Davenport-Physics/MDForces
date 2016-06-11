/*
 * main.c
 * 
 * Copyright 2016 Emma Davenport <Davenport.physics@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const int BUFFER_LENGTH = 256;

void ReadInputFile();
void ParseInputString(char stringbuffer[BUFFER_LENGTH]);
void Initialize(int argc, char *argv[]);
void InitializeArrays(FILE *fp);
void HandleRuntimeArguments(int argc, char *argv[]);

static int NumberOfAtoms = 0;

static char Filename[BUFFER_LENGTH] = {'\0'};
static char **Atoms = NULL;

static double CubicBoxLength = 0.0f;
static double **Coordinates = NULL;

int main(int argc, char **argv)
{
	
	Initialize(argc, argv);
	
	free(Atoms);
	free(Coordinates);
	
	return 0;
}

void ReadInputFile() {

	FILE *fp = fopen("INPUT", "r");

	if (fp == NULL) {

		printf("INPUT file not found\n");
		return;

	}

	char stringbuffer[BUFFER_LENGTH] = {'\0'};
	while ((fgets(stringbuffer, BUFFER_LENGTH, fp)) != EOF)
		ParseInputString(stringbuffer);

	fclose(fp);

}


void HandleRuntimeArguments(int argc, char **argv) {
	
	int i;
	for (i = 1;i < argc;i++) {
	
		if (strcasecmp(argv[i], "-f") == 0 && (i+1) < argc) {
	
			strncpy(Filename, argv[i+1], BUFFER_LENGTH);
			
		}
		
	}
	
}

void Initialize(int argc, char *argv[]) {

	ReadInputFile();

	if (argc > 1)
		HandleRuntimeArguments(argc, argv);

	FILE *fp = fopen(Filename, "r");
	
	if (fp == NULL) {
	
		printf("File %s not found, please re-run the program\n", Filename);
		exit(1);
		
	}
	
	fscanf(fp,"%d", &NumberOfAtoms);
	fscanf(fp,"%lf", &CubicBoxLength);
	
	printf("Number of atoms = %d and Cubic Box Length = %lf", NumberOfAtoms, CubicBoxLength);
	
	InitializeArrays(fp);
	
	fclose(fp);

}

void InitializeArrays(FILE *fp) {
	
	Atoms = (char **)malloc(NumberOfAtoms * sizeof(char *));
	Coordinates = (double **)malloc(NumberOfAtoms * sizeof(double *));
	
	int i;
	for (i = 0;i < NumberOfAtoms;i++) {
	
		Atoms[i] = (char *)malloc(3 * sizeof(char));
		Coordinates[i] = (double *)malloc(3 * sizeof(double));
		
	}
	
	for (i = 0;i < NumberOfAtoms;i++) {
	
		fscanf(fp, "%s %lf %lf %lf", Atoms[i], &(Coordinates[i][0]), &(Coordinates[i][1]), &(Coordinates[i][2]));
		printf("Atom %d %s with coordinates = %lf %lf %lf\n", i+1, Atoms[i], Coordinates[i][0], Coordinates[i][1], Coordinates[i][2]);
		
	}
	
}

typedef struct {

	char *string;
	int length;

} String_T;

static String_T input_arguments[9] = {
{"XYZ_FILE", 8},
{"TEST_FORCES",11},
{"CONSTANT_TEMPERATURE",20},
{"TAU", 3},
{"NTSTEPS", 7},
{"DT", 2},
{"TEMP", 4},
{"INIT_TEMP", 9},
{"IPRINT", 6}};

void ParseInputString(char stringbuffer[BUFFER_LENGTH]) {

	

}
