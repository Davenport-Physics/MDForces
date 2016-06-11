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

#include "share.h"

static int NumberOfAtoms = 0;

static char Filename[BUFFER_LENGTH];
static char **Atoms = NULL;

static double CubicBoxLength = 0.0f;
static double **Coordinates = NULL;

void ReadInputFile();
void Initialize(int argc, char *argv[]);
void InitializeArrays(FILE *fp);

void HandleRuntimeArguments(int argc, char *argv[]);
void ParseInputString(char stringbuffer[BUFFER_LENGTH]);
char *GetParameter(char stringbuffer[BUFFER_LENGTH]);

int main(int argc, char **argv)
{
	
	Initialize(argc, argv);
	
	free(Atoms);
	free(Coordinates);
	
	return 0;
}
/*

	Attemps to initialize all of the necessary static variables needed for
	this program to run correctly. Will exit safely if certain conditions
	are not met that are necessary for the program to execute correctly.

*/

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

/*

	Looks for a file called INPUT and calls ParseInputString
	to parse the file line by line

*/
void ReadInputFile() {

	FILE *fp = fopen("INPUT", "r");

	if (fp == NULL) {

		printf("INPUT file not found\n");
		return;

	}

	char stringbuffer[BUFFER_LENGTH] = {'\0'};
	while (fgets(stringbuffer, BUFFER_LENGTH, fp) != NULL)
		ParseInputString(stringbuffer);

	fclose(fp);

}

/*

	Handles runtime arguments. Currently only the
	XYZ file is handled.

*/

void HandleRuntimeArguments(int argc, char **argv) {
	
	int i;
	for (i = 1;i < argc;i++) {
	
		if (strcasecmp(argv[i], "-f") == 0 && (i+1) < argc) {
	
			strncpy(Filename, argv[i+1], BUFFER_LENGTH);
			
		} else if (strcasecmp(argv[i], "-debug") == 0) {
		
			Debug = TRUE;
			
		}
		
	}
	
}

/*

	Initializes static pointers.

*/

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

void Input_xyz_file(char stringbuffer[BUFFER_LENGTH]);
void Input_test_forces(char stringbuffer[BUFFER_LENGTH]);
void Input_constant_temp(char stringbuffer[BUFFER_LENGTH]);
void Input_tau(char stringbuffer[BUFFER_LENGTH]);
void Input_nsteps(char stringbuffer[BUFFER_LENGTH]);
void Input_dt(char stringbuffer[BUFFER_LENGTH]);
void Input_temp(char stringbuffer[BUFFER_LENGTH]);
void Input_init_temp(char stringbuffer[BUFFER_LENGTH]);
void Input_iprint(char stringbuffer[BUFFER_LENGTH]);

static const String_T input_arguments[9] = {
{"XYZ_FILE",             8, &Input_xyz_file},
{"TEST_FORCES",         11, &Input_test_forces},
{"CONSTANT_TEMPERATURE",20, &Input_constant_temp},
{"TAU",                  3, &Input_tau},
{"NTSTEPS",              7, &Input_nsteps},
{"DT",                   2, &Input_dt},
{"TEMP",                 4, &Input_temp},
{"INIT_TEMP",            9, &Input_init_temp},
{"IPRINT",               6, &Input_iprint}};

void ParseInputString(char stringbuffer[BUFFER_LENGTH]) {

	/*
	 * strcspn returns position within string where # is located. If
	 * no # is found, it returns the length of the string.
	 * 
	 * */
	int CommentIndex = strcspn(stringbuffer, "#");
	
	//If comment leads string, simply exit this function
	if (CommentIndex == 0) {
	
		if (Debug == TRUE) {
		
			printf("String %s has a # at the beginning of the string\n", stringbuffer);
			
		}
		return;
		
	}
	
	int i;
	for (i = 0; i < 9;i++) {
	
		if (strncasecmp(input_arguments[i].string, stringbuffer, input_arguments[i].length) == 0) {
		
			if (Debug == TRUE)
				printf("Found %s in INPUT file\n", input_arguments[i].string);
				
			input_arguments[i].Function(stringbuffer);
		
		}
		
	}

}

void Input_xyz_file(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
	strncpy(Filename, parameter, strlen(parameter));
	
}
void Input_test_forces(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}
void Input_constant_temp(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}
void Input_tau(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}
void Input_nsteps(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}
void Input_dt(char stringbuffer[BUFFER_LENGTH]) {

	char *parameter = GetParameter(stringbuffer);
	
}
void Input_temp(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}
void Input_init_temp(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}
void Input_iprint(char stringbuffer[BUFFER_LENGTH]) {
	
	char *parameter = GetParameter(stringbuffer);
	
}

//Assumes that immediately following the paramater type, we have the value.
char *GetParameter(char stringbuffer[BUFFER_LENGTH]) {
	
	char *cpointer = strtok(stringbuffer," ");
	cpointer       = strtok(NULL, " ");
	
	return cpointer;
}
