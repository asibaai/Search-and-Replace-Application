//-----------------------------------------------------
// Written by: Arwa Alsibaai
//-----------------------------------------------------


#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "traversal.h"
#include "text.h"

void traverse_dir(char *dir, char target[], char path[], char cwd[]) 
{

    // declare the variables
    DIR *directory; // pointer to the directory
    struct dirent *entry; // pointer to the entries inside the directory
    struct stat filestat; // will be used to check the type of entry
    char new[PATH_MAX]; // the new path will be stored here so the origiinal is not modified
    strcpy(new, path); // copy the original path to the new one
    
    if(chdir(dir)) // if changing the directory is successful, 0 is returned (which is equal to false)
    {
        fprintf(stderr, "Error changing to %s\n", dir);
        exit(1);
    }

    directory = opendir("."); // open the directory
    if (directory == NULL) 
    {
        fprintf(stderr, "Error reading directory %s\n", dir);
        exit(1);
    }

    while((entry = readdir(directory))) // read the contents of the directory till the end is reached
    {

        stat(entry -> d_name, &filestat); // store the type of entry in filestat
        if(S_ISDIR(filestat.st_mode)) // check if the entry is a directory
        {
            if(strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0)
                continue; // skip the current and parent directories
            strcat(new, entry -> d_name); // concatenate the name of the directory to the path name
            strcat(new, "\\"); // add a backslash (between the names of directories)
            traverse_dir(entry -> d_name, target, new, cwd); // make a recursive call to the directory to search it
            strcpy(new, path); // when you return from the recursive call change back to the old path name
        }
        else // if the entry is a regular file
        {
            char *ext = strrchr(entry -> d_name, '.'); // get the extension of the file
            if(ext)
            {
                if (strncmp(ext, ".txt", 4) == 0) // check if the file is a text file
                {
                    search_file(entry -> d_name, target, new, cwd); // search the file for the target word
                }
            }
        }
        
    }
    
    chdir(".."); // return to the parent directory
    closedir(directory); // close the directory

}