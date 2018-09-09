#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "stdio.h"
#include "constants.h"
#include "stack.h"
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "dictionary.h"

int processStackOperation(const size_t operation);
int processBinaryOperation(size_t operation);
int processUnaryOperation(size_t operation);
int processTernaryOperation(size_t operation);
int processAriphmetic(size_t operation);
int processDefineWord(char* word);
int processBoolean(size_t operation);
int executeWord(size_t word);

int isNumber(char* token);

int processToken(char* token);
size_t defineConstant(char* word);

int addNewWord(char* new_word, struct commands* commands);
int removeWord(char* wordToDel);

#endif // COMMAND_INTERPRETER_H
