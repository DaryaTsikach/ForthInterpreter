#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"

int main(int argc, char* argv[])
{
    if (argc == 2) {
        run(argv[1]);
    } else {
        fprintf(stderr, "wrong number of arguments. expected: 1 \n");
    }
    return 0;
}
