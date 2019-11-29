// Declares a dictionary's functionality

#ifndef DICTIONARY_H
// MX: if nothing defined before #ifndef, use "#define DICTIONARY_H" until #endif.
// MX: if #inndef, the rest of the codes (upto #endif) will not be executed.
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define CHILD_SIZE 27

typedef struct dict
{
    // char* character; // Do I really need to store the word in here?
    bool is_word; // the solution uses bool.
    int size;
    //struct dict *previous;
    struct dict *path[CHILD_SIZE]; // Including the apostrophe
}
dict_trie;

dict_trie* create_node(void);
// NOT dict_trie create_node(void); it should return a pointer. do not miss the asterisk.
// the data type dict_trie* means the type is an address of dict_trie.
// creates a note for a trie

bool free_node(dict_trie *dictionary);
//to implement recursion to unload the dictionary

// Prototypes
bool check(const char *word);
//for the input pointer, check the word
// Returns true if word is in dictionary else false


bool load(const char *dictionary);
//for the input pointer, load dic
// Loads dictionary into memory, returning true if successful else false

unsigned int size(void);
//what is unsigned int? "unsigned int" allows a higher range of integers.
// Returns number of words in dictionary if loaded else 0 if not yet loaded


bool unload(void);
//to unload the dic
// Unloads dictionary from memory, returning true if successful else false

#endif // DICTIONARY_H
