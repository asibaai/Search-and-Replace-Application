//-----------------------------------------------------
// Written by: Arwa Alsibaai
//-----------------------------------------------------

#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include "traversal.h"
#include "text.h"
#include "report.h"

int main(int argc, char* argv[])
{
    // get the name of the current directory (where the search begins):
	char current_dir[PATH_MAX];
	if (!(getcwd(current_dir, sizeof(current_dir))))
    {
        fprintf(stderr, "Unable to get current directory.");
        exit(1);
    }

    if(argc < 2) // if the user does not enter an argument
    {
        fprintf(stderr, "You did not enter an argument.");
        exit(1);
    }
    if(argc > 2) // if the argument is more than one word
    {
        fprintf(stderr, "The argument can be only one word.");
        exit(1);
    }

	report_intro(argv[1], current_dir); // print the beginning of the report
    traverse_dir(".", argv[1], "", current_dir); // carry out the search process
    sort(current_dir); // sort the modified files and print them

    return 0;

}
