//-----------------------------------------------------
// Written by: Arwa Alsibaai
//-----------------------------------------------------


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "text.h"
#include "report.h"

void search_file(char filename[], char target[], char path[], char cwd[])
{
    // declare the variables
    struct changed_file this; // keeps track of the changes in this file
    this.changes = 0; // the number of changes is initialized to 0
    this.name = malloc(strlen(filename)); // allocate memory for the file name
    strcpy(this.name, filename); // store the file name for use
    
    int length = strlen(target); // get the length of the target string
    FILE *fptr; // create a file pointer
    fptr = fopen(filename, "r+"); // open the file to read and write
    if(fptr == NULL) // check if the file was opened
    {
        fprintf(stderr, "Error opening file %s", filename);
    }
    
    while(!feof(fptr)) // loop through the file until it reaches the end of the file
    {
        char c = fgetc(fptr); // get the chracter where the cursor is at
        if(EOF == c) // if the character is at the end of the file, break out of the loop
            break;

        if (c == target[0] || c == toupper(target[0])) // if the character matches that of the first character in the traget string
        {
            char word[length + 1]; // create a string to store the word. It should be of the length of the target string. Add one for the terminating character
            int index = 0;
            
            // store characters in the word array of the size of the target string
            do
            {
                word[index++] = c;
                c = fgetc(fptr);
            } while (!feof(fptr) && index < length);
            word[index] = '\0';

            // create a variable to move the cursor back and change the word later
            int back = length + 1; 
            if (feof(fptr))
                back = length;

            if (strcasecmp(word, target) == 0) // if the stored word matches the target string
            {
                fseek(fptr, -back, SEEK_CUR); // move the cursor back
                for(int i = 0; i<=length; i++)
                {
                    word[i] = toupper(word[i]); // change the word to uppercase
                }
                fprintf(fptr, "%s", word); // modify the text as needed
                this.changes++; // increment the number of changes made in the file
            }

        }
    }

    if(this.changes > 0)
    {
        FILE *fptr2; // create another file pointer
        char temp_name[PATH_MAX]; // temporary path name to store the path to the temp file in it
        strcpy(temp_name, cwd); // copy the name of the parent directory to start the path there
        strcat(temp_name, "/");
        strcat(temp_name, "temp.txt"); // concatenate the name of the temporary file to create its path
        fptr2 = fopen(temp_name, "a"); // create a temporary file in the parent directory
        // if there are changes made in the file, these will be recorded in the temporary file
        // they will be used later for sorting
        if(strcmp(path, "") == 0) // if the path is empty, it is at the parent directory and so does not need to be printed
            fprintf(fptr2, "%d,%s\n", this.changes, this.name);
        else
            fprintf(fptr2, "%d,%s%s\n", this.changes, path, this.name);
        fclose(fptr2); // close the file pointer
    }

    fclose(fptr); // close the file pointer
    free(this.name); // free the memory allocated for the name

}