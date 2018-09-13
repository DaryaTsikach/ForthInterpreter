#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word;

struct commands {
    struct commands* next;
    char* command;
};

struct Word {
    char* word;
    struct commands* commands;
    struct Word* next;
};

struct commands* add_new_command(struct commands* words, char* command);

struct Word* newWord(char* new_word, struct commands* commands);

int isEmptyDictionary(struct Word* dictionary);

size_t addWord(struct Word** dictionary, char* word, struct commands* commands);

struct commands* contains(struct Word* dictionary, char* new_word);

void freeList(struct commands* head);

struct Word* remove_word(struct Word* dictionary, char* word);

#endif // DICTIONARY_H
