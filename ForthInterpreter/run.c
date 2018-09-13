#include "run.h"

enum Condition condition = INTEPRETE;

int run(char* filename) {
    FILE *forth_program;
    forth_program = fopen(filename,"r");

    if (NULL == forth_program) {
        return FILE_NOT_FOUND_EXCEPTION;
    }

    struct commands* words = NULL;
    char* new_word = NULL;

    size_t exceptionCode = NO_EXCEPTIONS;

    /* while not end-of-file */
    while (!feof(forth_program)) {
        char* word = malloc(sizeof(char) * 32);
        if (word == NULL)
            return MEMORY_EXCEPTION;
        if (fscanf(forth_program, "%s", word) != 1 && !feof(forth_program))
            return PARSE_WORD_EXCEPTION;

        if (condition == INTEPRETE) {
            exceptionCode = processToken(word);
            if (exceptionCode >= DIV_BY_NULL_EXCEPTION && exceptionCode <= MEMORY_EXCEPTION)
                return exceptionCode;
            int return_value = defineConstant(word);
            switch(return_value) {
            case ADD_NEW_WORD:
                new_word = NULL;
                words = NULL;
                new_word = malloc(sizeof(char) * 32);
                if (fscanf(forth_program, "%s", new_word) != 1)
                    return PARSE_WORD_EXCEPTION;
                condition = COMPILE;
                break;
            case END_NEW_WORD:
                return INTERPRETE_EXCEPTION;
                break;
            case FORGET:
                word = NULL;
                word = malloc(sizeof(char) * 32);
                if (word == NULL)
                    return MEMORY_EXCEPTION;
                if (fscanf(forth_program, "%s", word) != 1)
                    return PARSE_WORD_EXCEPTION;
                removeWord(word);
                break;
            default:
                break;
            }
        } else if (condition == COMPILE) {
            int return_value = defineConstant(word);
            switch(return_value) {
            case END_NEW_WORD:
                if (addNewWord(new_word, words) != NO_EXCEPTIONS)
                    return MEMORY_EXCEPTION;
                condition = INTEPRETE;
                break;
            default:
                words = add_new_command(words, word);
                if (words == NULL)
                    return MEMORY_EXCEPTION;
                break;
            }
        }
        free(word);
    }

    /* a little clean-up */
    freeList(words);
    free(new_word);
    fclose(forth_program);
    return NO_EXCEPTIONS;
}
