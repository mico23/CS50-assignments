// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h> // PRINT?
#include <stdlib.h> // FILE?
#include <string.h>

#include <stdbool.h>

#include "dictionary.h"

// we can't execute code outside of functions.
// the only thing you can do at global scope is declaring variables (and initialize them with compile-time constants).
// dict_trie* root = malloc(1* sizeof(dict_trie)); // this will not work because malloc is a function;
dict_trie* root = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    dict_trie* trav = root;
    // TODO
    for (int i = 0; i < strlen(word); i++)
    {
        int c = word[i];
        if (isalpha(c) || c == '\'')
        {
            if (isupper(c))
            {
                c = tolower(c);
            }

            int location = c%97;
            if (location == 39)
            {
                if (!trav->path[26])
                {
                    return false;
                }
                else
                {
                    trav = trav->path[26];
                }
            }
            else
            {
                if (!trav->path[location])
                {
                    return false;
                }
                else
                {
                    trav = trav->path[location];
                }
            }
        }
        else
        {
            return false;
        }
    }
    return trav->is_word;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        // fclose(dict); //if dict is NULL, nothing to be closed?
        return false;
    }

    root = create_node();
    if (root == NULL)    // double check the syntex
    {
        printf("Run out of memory");
        return false;
    };

    dict_trie* trav = root;
    int location = 0;
    int index = 0;
    int counter = 0;

    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // printf("Debug load - a character read: %i. \n", c);
        // Allow only alphabetical characters and apostrophes
        // (c == '\'' && index > 0) means only append apostrophes when it is not the begining of the word.
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            if (c == 39)
            {
                location = 26;
                index++;
            }
            else
            {
                location = c%97;
                index++;
            }

            // To check if the path exists
            if (!trav->path[location])
            {
                dict_trie *node = create_node();
                if (node == NULL)
                {
                    printf("Run out of memory! \n");
                    return false;
                }
                else
                {
                    trav->path[location] = node;
                    trav = trav->path[location];
                    trav->is_word = false;

                }
            }
            else if (trav->path[location] != NULL)
            {
                trav = trav->path[location];
            }
        }

        // We must have found a whole word
        else if (index > 0)
        {
            //Set is_word to true, after a word is successfuly loaded
            trav->is_word = true; //double check here

            // Prepare for next word
            index = 0;

            //reset TRAV
            trav = root;

            //count words
            counter ++;
        }

       // printf("Debug load - a character checked/loaded. \n");
    }

    // undo everything if an error occurs
    if (ferror(dict))
    {
        fclose(dict);
        printf("Error reading %s.\n", dictionary);
        unload();
        return false;
    }

    // close the dictionary after loading
    fclose(dict);

    // assign the total count of words to root->size
    root->size = counter;
    // printf("Debug: This is the size of the dictionary: %i \n", root->size);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return root->size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    if (free_node(root))
        return true;
    else
        return false;
}


dict_trie* create_node(void)
{

    dict_trie *node = malloc(1*sizeof(dict_trie));
    if (!node)
    {
        printf("Run out of memory! \n");
    }
    else
    {
        node->is_word = false;
        node->size = 0;
        // node->previous = NULL;
        for (int i = 0; i < CHILD_SIZE; i ++)
        {
            node->path[i] = NULL;
        }
    }

    return node; // returns the address of node.
}

bool free_node(dict_trie* node)
{
    if (!node)
        return false;

    for (int i = 0; i < CHILD_SIZE; i ++)
    {
        free_node(node->path[i]);
    }

    free(node);
    return true; // double check this line
}