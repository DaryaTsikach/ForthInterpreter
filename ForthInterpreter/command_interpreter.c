#include "command_interpreter.h"
#include "dictionary.h"

struct StackNode* forth_stack = NULL;

struct Word* dictionary = NULL;

enum Boolean {TRUE, FALSE};

enum Boolean skip = FALSE;
enum Boolean inCycle = FALSE;

struct Cycle {
    char* command;
    struct Cycle* next;
};

struct Cycle* cycle = NULL;

struct Cycle* addToCycle(struct Cycle* cycle, char* word) {
    if (cycle == NULL) {
        cycle = malloc(sizeof(struct Cycle));
        cycle->next = NULL;
        cycle->command = malloc(sizeof(char) * strlen(word));
        strcpy(cycle->command, word);
        return cycle;
    }
    struct Cycle* current = cycle;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(struct Cycle));
    current->next->command = malloc(sizeof(char) * strlen(word));
    strcpy(current->next->command, word);
    current->next->next = NULL;
    return cycle;
}

void iterateCycle(struct Cycle* cycle) {
    if (cycle == NULL)
        return;
    struct Cycle* current = cycle;
    while (current != NULL) {
        processToken(current->command);
        current = current->next;
    }
}

void freeCycle(struct Cycle* head) {
   struct Cycle* tmp;
   while (head != NULL) {
       tmp = head;
       head = head->next;
       free(tmp->command);
       free(tmp);
   }
}

int processStackOperation(const size_t operation) {
    if (operation == DUP) {
        short int elem = peek(forth_stack);
        push(&forth_stack, elem);
    }
    if (operation == DUP2) {
        short int first_part = pop(&forth_stack);
        short int second_part = pop(&forth_stack);
        push(&forth_stack, second_part);
        push(&forth_stack, first_part);
        push(&forth_stack, second_part);
        push(&forth_stack, first_part);
    }
    if (operation == DROP) {
        pop(&forth_stack);
    }
    if (operation == DROP2) {
        pop(&forth_stack);
        pop(&forth_stack);
    }
    if (operation == OVER) {
        short int n1 = pop(&forth_stack);
        short int n2 = peek(forth_stack);
        push(&forth_stack, n1);
        push(&forth_stack, n2);
    }

    if (operation == OVER2) {
        short int n1_1 = pop(&forth_stack);
        short int n1_2 = pop(&forth_stack);
        short int n2_1 = pop(&forth_stack);
        short int n2_2 = pop(&forth_stack);
        push(&forth_stack, n2_2);
        push(&forth_stack, n2_1);
        push(&forth_stack, n1_2);
        push(&forth_stack, n1_1);
        push(&forth_stack, n2_2);
        push(&forth_stack, n2_1);
    }
    if (operation == ROT) {
        short int n1 = pop(&forth_stack);
        short int n2 = pop(&forth_stack);
        short int n3 = pop(&forth_stack);
        push(&forth_stack, n2);
        push(&forth_stack, n1);
        push(&forth_stack, n3);
    }
    if (operation == ROT2) {
        short int n1_1 = pop(&forth_stack);
        short int n1_2 = pop(&forth_stack);
        short int n2_1 = pop(&forth_stack);
        short int n2_2 = pop(&forth_stack);
        short int n3_1 = pop(&forth_stack);
        short int n3_2 = pop(&forth_stack);

        push(&forth_stack, n2_2);
        push(&forth_stack, n2_1);
        push(&forth_stack, n1_2);
        push(&forth_stack, n1_1);
        push(&forth_stack, n3_2);
        push(&forth_stack, n3_1);
     }
    if (operation == SWAP) {
        short int first = pop(&forth_stack);
        short int second = pop(&forth_stack);
        push(&forth_stack, first);
        push(&forth_stack, second);
     }
    if (operation == SWAP2) {
        short int n1_1 = pop(&forth_stack);
        short int n1_2 = pop(&forth_stack);
        short int n2_1 = pop(&forth_stack);
        short int n2_2 = pop(&forth_stack);

        push(&forth_stack, n1_2);
        push(&forth_stack, n1_1);
        push(&forth_stack, n2_2);
        push(&forth_stack, n2_1);
     }
    if (operation == PICK) {
        const int n = pop(&forth_stack);
        short int array[n + 1];
        int index;
        for (index = 0; index <= n; ++index) {
            array[index] = pop(&forth_stack);
        }
        for (index = n; index >= 0; --index) {
            push(&forth_stack, array[index]);
        }
        push(&forth_stack, array[n]);
    }
    if (operation == ROLL) {
        const size_t n = pop(&forth_stack);
        short int array[n + 1];
        size_t index;
        for (index = 0; index <= n; ++index) {
            array[index] = pop(&forth_stack);
        }
        for (index = n - 1; index != 0; --index) {
            push(&forth_stack, array[index]);
        }
        push(&forth_stack, array[0]);
        push(&forth_stack, array[n]);
    }
    if (operation == OUT) {
        short int top_elem = pop(&forth_stack);
        printf("%hi \n", top_elem);
    }
    if (operation == OUT2) {
        int number = pop(&forth_stack);
        number = (number << 16) & 0xFFFF0000;
        number += pop(&forth_stack) & 0x0000FFFF;
        printf("%d \n", number);
    }
    return 1;
}

int processBinaryOperation(size_t operation) {
    if (operation >= ADD && operation <= DIVMOD) {
        short int second_number = pop(&forth_stack);
        short int first_number = pop(&forth_stack);
        short int result = 0;

        if (operation == ADD)
            result = first_number + second_number;
        if (operation == SUB)
            result = first_number - second_number;
        if (operation == MULT)
            result = first_number * second_number;
        if (operation == DIV) {
            if (second_number == 0) {
                fprintf(stderr, "ariphmetic error: div by 0 \n");
                return 0;
            }
            result = first_number / second_number;
        }
        if (operation == MOD)
            result = first_number % second_number;
        if (operation == DIVMOD) {
            result = first_number % second_number;
            push(&forth_stack, result);
            if (second_number == 0) {
                fprintf(stderr, "ariphmetic error: div by 0 \n");
                return 0;
            }
            result = first_number / second_number;
        }
        push(&forth_stack, result);
    }
    if (operation >= DADD && operation <= DMOD) {
        int first_number = pop(&forth_stack);
        first_number = (first_number << 16) & 0xFFFF0000;
        first_number += pop(&forth_stack) & 0x0000FFFF;

        int second_number = pop(&forth_stack);
        second_number = (second_number << 16) & 0xFFFF0000;
        second_number += pop(&forth_stack) & 0x0000FFFF;
        int result = 0;
        short int result_second_part = 0;
        short int result_first_part = 0;
        if (operation == DADD) {
            result = first_number + second_number;
            result_second_part = result & 0x0000FFFF;
            result_first_part = (result >> 16) & 0x0000FFFF;
        }
        if (operation == DSUB) {
            result = first_number - second_number;
            result_second_part = result & 0x0000FFFF;
            result_first_part = (result >> 16) & 0x0000FFFF;
        }
        if (operation == DMUL) {
            result = first_number * second_number;
            result_second_part = result & 0x0000FFFF;
            result_first_part = (result >> 16) & 0x0000FFFF;
        }
        if (operation == DDIV) {
            if (second_number == 0) {
                fprintf(stderr, "ariphmetic error: div by 0 \n");
                return 0;
            }
            result = first_number / second_number;
            result_second_part = result & 0x0000FFFF;
            result_first_part = (result >> 16) & 0x0000FFFF;
        }
        if (operation == DMOD) {
            result = first_number % second_number;
            result_second_part = result & 0x0000FFFF;
            result_first_part = (result >> 16) & 0x0000FFFF;
        }
        push(&forth_stack, result_second_part);
        push(&forth_stack, result_first_part);
    }
    return 1;
}

int processUnaryOperation(size_t operation) {
    if ((operation >= ADD1 && operation <= DIV2) || (operation >= ABS && operation <= NEGATE)) {
        short int number = pop(&forth_stack);
        short int result = 0;
        if (operation == ABS)
            result = abs(number);
        if (operation == NEGATE)
            result = number * (-1);
        if (operation == ADD1)
            result = number + 1;
        if (operation == SUB1)
            result = number - 1;
        if (operation == ADD2)
            result = number + 2;
        if (operation == SUB2)
            result = number - 2;
        if (operation == DIV2)
            result = number / 2;
        push(&forth_stack, result);
    }
    if (operation == DABS || operation == DNEGATE) {
        int number = pop(&forth_stack);
        number += pop(&forth_stack);
        short int result_second_part = 0;
        int result_first_part = 0;
        if (operation == DABS) {
            number = abs(number);
            result_second_part = (short int)number;
            result_first_part = number - result_second_part;
        }
        if (operation == DNEGATE) {
            number *= -1;
            result_second_part = (short int)number;
            result_first_part = number - result_second_part;
        }
        push(&forth_stack, result_second_part);
        push(&forth_stack, result_first_part);
    }
    return 1;
}

int processTernaryOperation(size_t operation) {
    int c = pop(&forth_stack);
    short int b = pop(&forth_stack);
    short int a = pop(&forth_stack);
    short int result = 0;
    if (c == 0) {
        fprintf(stderr, "ariphmetic error: div by 0 \n");
    }
    if (operation == MULDIV) {
        result = (a * b) / c;
    }
    if (operation == MULDIVMOD) {
        short int mod = (a * b) % c;
        push(&forth_stack, mod);
        result = (a * b) / c;
    }
    push(&forth_stack, result);
    return 1;
}

int processUnsigned(size_t operation) {
    if (operation == UMMUL) {
        unsigned short int first_number = (unsigned short int)pop(&forth_stack);
        unsigned short int second_number = (unsigned short int)pop(&forth_stack);
        unsigned int result = first_number * second_number;
        short unsigned int result_first_part = (unsigned short int) result;
        unsigned int result_second_part = result - result_first_part;
        push(&forth_stack, result_second_part);
        push(&forth_stack, result_first_part);
    }
    if (operation == UMDIVMOD) {
        unsigned short int first_number = (unsigned short int)pop(&forth_stack);
        unsigned int second_number = (unsigned int)pop(&forth_stack);
        if (first_number == 0) {
            fprintf(stderr, "ariphmetic error: div by 0 \n");
        }
        unsigned short int mod = second_number % first_number;
        int res = second_number / first_number;
        if (res > 65535) {
            fprintf(stderr, "overflow: the result %d doesn`t not fit in uint16 \n", res);
        }
        push(&forth_stack, mod);
        push(&forth_stack, (unsigned short int)res);
    }
    return 1;
}

int processAriphmetic(size_t operation) {
    if ((operation >= ADD && operation <= DIVMOD) || (operation >= DADD && operation <= DMOD)) {
        return processBinaryOperation(operation);
    }

    if ((operation >= ADD1 && operation <= DIV2) || (operation >= ABS && operation <= DNEGATE)) {
        return processUnaryOperation(operation);
    }

    if (operation == MULDIV || operation == MULDIVMOD) {
        return processTernaryOperation(operation);
    }

    if (operation == UMMUL || operation == UMDIVMOD) {
        return processUnsigned(operation);
    }
    return 0;
}

int processBoolean(size_t operation) {
    short int bool1 = pop(&forth_stack);
    short int res = 0;
    if (operation >= NOT && operation <= EQUAL0) {
        if (operation == NOT)
            res = !bool1;
        if (operation == LESS0) {
            if (bool1 < 0)
                res = -1;
            else
                res = 0;
        }
        if (operation == GREATER0) {
            if (bool1 > 0)
                res = -1;
            else
                res = 0;
        }
        if (operation == EQUAL0) {
            if (bool1 == 0)
                res = -1;
            else
                res = 0;
        }
    }
    short int bool2 = pop(&forth_stack);
    if (operation >= AND && operation <= EQUAL) {
        if (operation == AND)
            res = bool2 & bool1;
        if (operation == OR)
            res = bool2 | bool1;
        if (operation == XOR)
            res = bool2 ^ bool1;
        if (operation == LESS) {
            if (bool2 < bool1)
                res = -1;
            else
                res = 0;
        }
        if (operation == GREATER) {
            if (bool2 > bool1)
                res = -1;
            else
                res = 0;
        }
        if (operation == EQUAL) {
            if (bool1 == bool2)
                res = -1;
            else
                res = 0;
        }
    push(&forth_stack, res);
    }

    if (operation == ULESS) {
        unsigned short int n2 = (unsigned short int)pop(&forth_stack);
        unsigned short int n1 = (unsigned short int)pop(&forth_stack);
        short int res;
        if (n1 < n2)
            res = -1;
        else
            res = 0;
        push(&forth_stack, res);
    }
    return 1;
}

int executeWord(size_t word) {
    if (word == ONE_LINE_COMMENT) {
        return ONE_LINE_COMMENT;
    }
    if (word == DOC_COMMENT) {
        return DOC_COMMENT;
    }
    if (word == ADD_NEW_WORD) {
        return ADD_NEW_WORD;
    }

    if (word == END_NEW_WORD) {
        return END_NEW_WORD;
    }

    if (word >= ADD && word <= UMDIVMOD) {
        return processAriphmetic(word);
    }

    if (word >= DUP && word <= OUT2) {
        return processStackOperation(word);
    }

    if (word >= AND && word <= DULESS) {
        return processBoolean(word);
    }

    if (word == IF) {
        short int check_value = pop(&forth_stack);
        if (!check_value) {
            skip = TRUE;
        }
    }

    if (word == ELSE) {
        skip = !skip;
    }

    if (word == THEN) {
        skip = FALSE;
    }

    if (word == BEGIN) {
        inCycle = TRUE;
    }

    if (word == UNTIL) {
        inCycle = FALSE;
        short int check_value = pop(&forth_stack);
        while (check_value == 0) {
            iterateCycle(cycle);
            check_value = pop(&forth_stack);
        }
        cycle = NULL;
        freeCycle(cycle);
    }

    if (word == WHILE) {
        short int check_value = pop(&forth_stack);
        if (!check_value) {
            skip = TRUE;
            inCycle = FALSE;
            cycle = NULL;
            freeCycle(cycle);
        }
    }

    if (word == REPEAT) {
        if (cycle != NULL) {
           iterateCycle(cycle);
        }
        skip = FALSE;
    }
    return 0;
}

int processDefineWord(char* word) {
    struct commands* cmd = contains(dictionary, word);

    size_t commands_counter = 0;
    while (cmd != NULL) {
        processToken(cmd->command);
        cmd = cmd->next;
        ++commands_counter;
    }
    if (commands_counter == 0) {
        fprintf(stderr, "error while processing user define word: %s\n", word);
        return 0;
    }
    else
        return 1;
}

int isNumber(char* token) {
    int i;
    int len = strlen(token);
    for (i = 0; i < len; ++i) {
        if (!isdigit(token[i]) && token[i] != '.' && token[i] != '-') {
            return 0;
        }
    }
    char* position = strchr(token, '.');
    if (position == NULL) {
        /*process like short int*/
        short int res = (short int)atoi(token);
        push(&forth_stack, res);

    } else {
        /*process like int*/
        int res = atoi(token);
        short int first_part_res = res & 0x0000FFFF;
        short int second_part_res = (res >> 16) & 0x0000FFFF;
        push(&forth_stack, first_part_res);
        push(&forth_stack, second_part_res);
    }
    return 1;
}

int processToken(char* token) {
    /*token can be from reserve words or from user define*/
    size_t operation = defineConstant(token);
    if (skip == TRUE && operation != ELSE && operation != THEN && operation != REPEAT)
        return 0;
    if (inCycle == TRUE && operation != UNTIL && operation != REPEAT) {
        cycle = addToCycle(cycle, token);
    }
    if (operation == NOT_A_WORD) {
        if (isNumber(token)) {
            return 1;
        }
        else if (processDefineWord(token)) {
           return 1;
        }
        else {
            fprintf(stderr, "error while parsing: unknown word %s \n", token);
            return (-1);
        }
    } else {
        return executeWord(operation);
    }
    return 0;
}

int addNewWord(char* new_word, struct commands* commands) {
    addWord(&dictionary, new_word, commands);
    return 0;
}

int removeWord(char* wordToDel) {
    dictionary = remove_word(dictionary, wordToDel);
    return 0;
}

size_t defineConstant(char *word) {
    if (strcmp(word, "AND") == 0)
        return AND;
    if (strcmp(word, "OR") == 0)
        return OR;
    if (strcmp(word, "XOR") == 0)
        return XOR;
    if (strcmp(word, "NOT") == 0)
        return NOT;
    if (strcmp(word, "<") == 0)
        return LESS;
    if (strcmp(word, ">") == 0)
        return GREATER;
    if (strcmp(word, "=") == 0)
        return EQUAL;
    if (strcmp(word, "U<") == 0)
        return ULESS;
    if (strcmp(word, "0<") == 0)
        return LESS0;
    if (strcmp(word, "0>") == 0)
        return GREATER0;
    if (strcmp(word, "0=") == 0)
        return EQUAL0;
    if (strcmp(word, "D0=") == 0)
        return DEQUAL0;
    if (strcmp(word, "D<") == 0)
        return DLESS;
    if (strcmp(word, "D=") == 0)
        return DEQUAL;
    if (strcmp(word, "DU<") == 0)
        return DULESS;

    if (strcmp(word, "+") == 0)
        return ADD;
    if (strcmp(word, "-") == 0)
        return SUB;
    if (strcmp(word, "*") == 0)
        return MULT;
    if (strcmp(word, "/") == 0)
        return DIV;
    if (strcmp(word, "MOD") == 0)
        return MOD;
    if (strcmp(word, "/MOD") == 0)
        return DIVMOD;
    if (strcmp(word, "ABS") == 0)
        return ABS;
    if (strcmp(word, "NEGATE") == 0)
        return NEGATE;
    if (strcmp(word, "1+") == 0)
        return ADD1;
    if (strcmp(word, "1-") == 0)
        return SUB1;
    if (strcmp(word, "2+") == 0)
        return ADD2;
    if (strcmp(word, "2-") == 0)
        return SUB2;
    if (strcmp(word, "2/") == 0)
        return DIV2;
    if (strcmp(word, "*/") == 0)
        return MULDIV;
    if (strcmp(word, "*/MOD") == 0)
        return MULDIVMOD;
    if (strcmp(word, "D+") == 0)
        return DADD;
    if (strcmp(word, "D-") == 0)
        return DSUB;
    if (strcmp(word, "D*") == 0)
        return DMUL;
    if (strcmp(word, "D/") == 0)
        return DDIV;
    if (strcmp(word, "DABS") == 0)
        return DABS;
    if (strcmp(word, "DNEGATE") == 0)
        return DNEGATE;
    if (strcmp(word, "DMOD") == 0)
        return DMOD;
    if (strcmp(word, "UM*") == 0)
        return UMMUL;
    if (strcmp(word, "UM/MOD") == 0)
        return UMDIVMOD;


    if (strcmp(word, "DUP") == 0)
        return DUP;
    if (strcmp(word, "DROP") == 0)
        return DROP;
    if (strcmp(word, "SWAP") == 0)
        return SWAP;
    if (strcmp(word, "OVER") == 0)
        return OVER;
    if (strcmp(word, "ROT") == 0)
        return ROT;
    if (strcmp(word, "PICK") == 0)
        return PICK;
    if (strcmp(word, "ROLL") == 0)
        return ROLL;

    if (strcmp(word, "2DUP") == 0)
        return DUP2;
    if (strcmp(word, "2DROP") == 0)
        return DROP2;
    if (strcmp(word, "2SWAP") == 0)
        return SWAP2;
    if (strcmp(word, "2OVER") == 0)
        return OVER2;
    if (strcmp(word, "2ROT") == 0)
        return ROT2;

    if (strcmp(word, ".") == 0)
        return OUT;
    if (strcmp(word, "D.") == 0)
        return OUT2;

    if (strcmp(word, ":") == 0)
        return ADD_NEW_WORD;
    if (strcmp(word, ";") == 0)
        return END_NEW_WORD;

    if (strcmp(word, "\\") == 0 && strstr(word, "\\S") == NULL)
        return ONE_LINE_COMMENT;
    if (strcmp(word, "\\S") == 0)
        return DOC_COMMENT;
    if (strcmp(word, "FORGET") == 0)
        return FORGET;

    if (strcmp(word, "IF") == 0)
        return IF;
    if (strcmp(word, "ELSE") == 0)
        return ELSE;
    if (strcmp(word, "THEN") == 0)
        return THEN;

    if (strcmp(word, "BEGIN") == 0)
        return BEGIN;
    if (strcmp(word, "UNTIL") == 0)
        return UNTIL;
    if (strcmp(word, "WHILE") == 0)
        return WHILE;
    if (strcmp(word, "REPEAT") == 0)
        return REPEAT;

    return NOT_A_WORD;
}
