#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "stdio.h"
#include "constants.h"
#include "stack.h"
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "dictionary.h"

size_t processStackOperation(const size_t operation);
size_t processBinaryOperation(size_t operation);
size_t processUnaryOperation(size_t operation);
size_t processTernaryOperation(size_t operation);
size_t processAriphmetic(size_t operation);
size_t processDefineWord(char* word);
size_t processBoolean(size_t operation);

size_t executeWord(size_t word);
size_t isNumber(char* token);
size_t processToken(char* token);
size_t defineConstant(char* word);

size_t addNewWord(char* new_word, struct commands* commands);
size_t removeWord(char* wordToDel);

void dealWithException(size_t exception);

#endif // COMMAND_INTERPRETER_H
