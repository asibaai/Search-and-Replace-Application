//-----------------------------------------------------
// Written by: Arwa Alsibaai
//-----------------------------------------------------


#ifndef REPORT_H_
#define REPORT_H_

// define the struct of changed files
typedef struct changed_file // will be used to keep track of the changed files
{
    int changes; // tracks the number of changes made
    char *name; // tracks the name of the file
} file;

// define all functions
void report_intro(char target[], char cwd[]);
int compare(const void *w, const void *x);
void sort(char cwd[]);

#endif /* REPORT_H_ */