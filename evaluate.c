#include "evaluate.h"

void eval(char *commandLine)
{
    // parse the input commandLine into command struct
    // check whether the command is builtin command or not, if builtin interpret specially otherwise execute normally
    // call fork to have a copy of memory in a new location(image)
    command cmd;
    int bg = parse(commandLine, &cmd);
    if (cmd.builtin == NONE)
        execNormalCommand(&cmd, bg);
    else
        execBuiltinCommand(&cmd, bg);
}

void execBuiltinCommand(command *cmd, int bg){};
void execNormalCommand(command *cmd, int bg)
{
    // printf("current pid: %d\n",getpid());
    // pid_t childid=fork();
    // printf("current pid: %d\n",getpid());
    if (cmd->argc == 0)
        return;

    pid_t childid = fork();

    if (childid == -1)
    {
        error("fork");
    }
    if (childid == 0)
    {
        if (execvp(cmd->argv[0], cmd->argv) == -1)
        {
            printf("%s command not found\n", cmd->argv[0]);
            return;
        }
    }
    if (bg == 1)
    {
        printf("[%d] running in background\n", bg++);
    }
    else
    {
        wait(&childid);
    }
}
