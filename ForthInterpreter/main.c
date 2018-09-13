#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"

size_t exception = NO_EXCEPTIONS;

int main(int argc, char* argv[])
{
    if (argc == 2) {
        exception = run(argv[1]);
    } else {
        exception = COMMAND_LINE_ARGUMENTS_EXCEPTION;
    }
    dealWithException(exception);
    return exception;
}
