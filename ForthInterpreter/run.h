#ifndef RUN_H
#define RUN_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_interpreter.h"

enum Condition {INTEPRETE, COMPILE};

int run(char* filename);

#endif // RUN_H
