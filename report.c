//-----------------------------------------------------
// Written by: Arwa Alsibaai
//-----------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "report.h"
#include "text.h"

void report_intro(char target[], char cwd[]) // print the beginning of the report, takes the target string as an argument
{
	printf("----------------------------------------------\n");
	printf("Target string: %s", target);
	printf("\n\nSearch begins in current folder: %s", cwd);
	printf("\n\n\n** Search Report **\n\n");
	printf("Updates\t\tFile Name\n");
}

int compare(const void *w, const void *x) // the comparator function required by qsort
{
	// cast the arguments to structs for changed files
	const file *y = (file *)w;
	const file *z = (file *)x;

	// define the conditions for the function
	if(y -> changes > z -> changes)
		return -1;
	else if(y -> changes < z -> changes)
		return 1;
	else
		return 0;
}

void sort(char cwd[]) // sort the entries and print them
{
	char temp_name[PATH_MAX]; // temporary path name to store the path to the temp file in it
    strcpy(temp_name, cwd); // copy the name of the parent directory to start the path there
    strcat(temp_name, "/");
    strcat(temp_name, "temp.txt"); // concatenate the name of the temporary file to get its path

	FILE *fptr; // create a file pointer
	fptr = fopen(temp_name, "r"); // open the temporary file to read the entries from it
    if(fptr == NULL) // check if the file was opened
    {
        fprintf(stderr, "Error opening file");
    }

	file files[1000]; // create an array of structs to store the entries
	int index = 0; // will be used to go through the array and store entries
	do
	{
		files[index].name = malloc(PATH_MAX); // allocate memory for the file name
		fscanf(fptr, "%d,%s\n", &files[index].changes, files[index].name); // scan the temporary file
		index++;
	} while (!feof(fptr));

	qsort(files, index, sizeof(file), compare); // sort the array

	for(int i = 0; i < index; i++)
	{
		printf("%d\t\t%s\n", files[i].changes, files[i].name); // print the entries
	}

	for(int i = 0; i < index; i++)
	{
		free(files[i].name); // free the allocated memory for all the file names
	}

	remove(temp_name); // delete the temporary file
}