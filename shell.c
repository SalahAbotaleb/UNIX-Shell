#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "evaluate.h"

int main()
{

    char commandLine[MAXLENGTH];
    while (1) // the main loop of the program
    {
        printf("%s", prompt);
        if (fgets(commandLine, MAXLENGTH, stdin) == NULL && ferror(stdin))
        {
            error("fgets error");
        }
        if (feof(stdin)) // when EOF terminate (ctrl+D -> EOF)
            exit(0);
        commandLine[strlen(commandLine) - 1] = '\0'; // removing \n by replacing it with null terminating char

        eval(commandLine); // evaluating the command for execution
    }

    return 0;
}
