#ifndef EVALUATE
#define EVALUATE

#include <unistd.h>
#include "utilities.h"

void eval(char *);
void execBuiltinCommand(command *cmd, int bg);
void execNormalCommand(command *cmd, int bg);

#endif
