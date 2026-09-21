# Search-and-Replace-Application
A simple search and replace application that finds a user-specified text string within a group of disk files, modifies those strings and updates the original disk files, then provides a report that indicates what has been done.


The application takes a single command argument, which will be interpreted as a text string. If the user does not enter an argument, or enters more than one argument, it prompts him to enter a single argument. The application then opens each text file in the current directory, as well as traverses into nested directories and opens the text files inside those directories too. It reads the contents of each file, and, if it encounters the word entered as the command argument, it modifies the text so that the target string is printed in upper case. Finally, the application keeps track of the files it changed and the number of changes in each one. At the end of the process, it prints out a report of the modifications.

To run the program, compile the following files: replace.c traversal.c text.c report.c, then run replace.c with the target string.

DirX includes text files and nested directories that can be used to test the application. The intended target string is 'apple'. Some of the files include the word, and some do not.
To test the application, traverse to the project directory in terminal and run the following commands:
gcc replace.c traversal.c text.c report.c
./a.exe apple
