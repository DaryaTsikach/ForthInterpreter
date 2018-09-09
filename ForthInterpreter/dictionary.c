#ifndef DICTIONARY_C
#define DICTIONARY_C
#include "dictionary.h"

struct Word* newWord(char* new_word, struct commands* commands) {
    struct Word* word = (struct Word*)malloc(sizeof(struct Word));
    word->word = new_word;
    word->commands = commands;
    word->next = NULL;
    return word;
}

int isEmptyDictionary(struct Word* dictionary) {
    return !dictionary;
}

void addWord(struct Word** dictionary, char* new_word, struct commands* commands) {
    struct Word* word = newWord(new_word, commands);
    word->next = *dictionary;
    *dictionary = word;
}

struct commands* contains(struct Word* dictionary, char* new_word) {
    if (dictionary == NULL)
        return NULL;
    struct Word* current_word = dictionary;

    while (strcmp(new_word, current_word->word) != 0) {
        if (current_word->next == NULL)
            return NULL;
        else
            current_word = current_word->next;
    }
    return current_word->commands; //for now
}

struct commands* add_new_command(struct commands* words, char* command) {
    if (words == NULL) {
        words = malloc(sizeof(struct commands));
        words->next = NULL;
        words->command = malloc(sizeof(char) * strlen(command));
        strcpy(words->command, command);
        return words;
    }
    struct commands* current = words;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(struct commands));
    current->next->command = malloc(sizeof(char) * strlen(command));
    strcpy(current->next->command, command);
    current->next->next = NULL;
    return words;
}

void freeList(struct commands* head) {
   struct commands* tmp;
   while (head != NULL) {
       tmp = head;
       head = head->next;
       free(tmp->command);
       free(tmp);
   }
}

struct Word* remove_word(struct Word *dictionary, char *word) {
    if (dictionary == NULL) {
        return NULL;
    }
    struct Word* tmp = dictionary;
    struct Word* prev = NULL;
    while (tmp != NULL) {
        if (strcmp(tmp->word, word) == 0) {
            if (prev != NULL) {
                prev->next = tmp->next;
            } else {
                dictionary = tmp->next;
            }
            free(tmp);
            break;
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return dictionary;
}

#endif // DICTIONARY_C
