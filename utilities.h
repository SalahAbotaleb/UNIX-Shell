#ifndef UTILITIES
#define UTILITIES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXARGS 128
#define MAXLENGTH 1024 // max length of input is 1024 char
extern const char prompt[];

extern int bgCnt;

typedef struct
{
    // command structure: command argument1 argument2 ... argumentN
    // command is stored as argv[0]
    int argc;
    char *argv[MAXARGS];
    enum builtin_type
    { // is arg[0] a build in command
        NONE,
        QUIT,
        JOBS,
        BG,
        FG
    } builtin; // BG: Background job, FG:Foreground job
} command;

void error(char *);
void builtinType(command *);
int parse(const char *, command *);

#endif
