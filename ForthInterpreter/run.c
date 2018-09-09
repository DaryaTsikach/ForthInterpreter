#include "run.h"

enum Condition condition = INTEPRETE;

int run(char* filename) {
    FILE *forth_program;
    forth_program = fopen(filename,"r");

    if (NULL == forth_program) {
        fprintf(stderr, "error while opening forth program %s \n", filename);
        return (-1);
    }

    struct commands* words = NULL;
    char* new_word = NULL;

    /* while not end-of-file */
    while (!feof(forth_program)) {
        char* word = malloc(sizeof(char) * 32);
        if (fscanf(forth_program, "%s", word) != 1)
            break;

        if (condition == INTEPRETE) {
            processToken(word);
            int return_value = defineConstant(word);
            switch(return_value) {
            case ADD_NEW_WORD:
                new_word = NULL;
                words = NULL;
                new_word = malloc(sizeof(char) * 32);
                if (fscanf(forth_program, "%s", new_word) != 1)
                    fprintf(stderr, "Error while parsing new word");
                condition = COMPILE;
                break;
            case END_NEW_WORD:
                fprintf(stderr, "couldn`t execute ; command at interpreting mode");
                break;
            case FORGET:
                word = NULL;
                word = malloc(sizeof(char) * 32);
                if (fscanf(forth_program, "%s", word) != 1)
                    break;
                removeWord(word);
                break;
            default:
                break;
            }
        } else if (condition == COMPILE) {
            int return_value = defineConstant(word);
            switch(return_value) {
            case END_NEW_WORD:
                addNewWord(new_word, words);
                condition = INTEPRETE;
                break;
            default:
                words = add_new_command(words, word);
                break;
            }
        }
        free(word);
    }

    /* a little clean-up */
    freeList(words);
    free(new_word);
    fclose(forth_program);
    return 0;
}
