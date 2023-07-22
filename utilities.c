#include "utilities.h"

const char prompt[] = "salahShell> \0";
int bgCnt = 0;

void error(char *errorMsg)
{
    printf("error: %s\n", errorMsg);
    exit(-1);
}

void builtinType(command *cmd)
{
    if (strcmp(cmd->argv[0], "quit") == 0)
    {
        cmd->builtin = QUIT;
        return;
    }
    if (strcmp(cmd->argv[0], "jobs") == 0)
    {
        cmd->builtin = JOBS;
        return;
    }
    if (strcmp(cmd->argv[0], "bg") == 0)
    {
        cmd->builtin = BG;
        return;
    }
    if (strcmp(cmd->argv[0], "fg") == 0)
    {
        cmd->builtin = FG;
        return;
    }

    cmd->builtin = NONE;
    return;
}

int parse(const char *commandLine, command *cmd)
{
    // return 1 if & argument is given (run in background)
    // return 0 if & argument is not given (run in foreground)
    char copy[MAXLENGTH]; // copy of commandLine
    char *currArg;        // points to beginning of current arguemnt
    char *currArgEnd;
    char *argsEnd; // points to when commandLine ends '\0'
    char *delimiters = " \n\t\r";

    if (commandLine == NULL)
        error("NULL commandLine");

    strncpy(copy, commandLine, MAXLENGTH);
    cmd->argc = 0;
    cmd->builtin = NONE;
    currArg = copy;
    argsEnd = &copy[strlen(copy) - 1] + 1;

    while (currArg < argsEnd)
    {
        currArg += strspn(currArg, delimiters);
        if (currArg >= argsEnd)
            break;

        currArgEnd = currArg + strcspn(currArg, delimiters);
        *currArgEnd = '\0';

        cmd->argv[cmd->argc++] = currArg;

        currArg = currArgEnd + 1;

        if (cmd->argc == MAXARGS - 1)
            break;
    }
    cmd->argv[cmd->argc] = NULL; // last position of argV must contain null

    if (cmd->argc != 0)
    {
        builtinType(cmd);
    }

    if (cmd->argc != 0 && strcmp(cmd->argv[cmd->argc - 1], "&") == 0)
    {
        cmd->argv[cmd->argc - 1] = NULL;
        cmd->argc--;
        return 1;
    }
    return 0;
}