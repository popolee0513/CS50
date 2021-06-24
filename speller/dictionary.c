// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include<string.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int number =0;
// Returns true if word is in dictionary, else false
bool  check(const char *word)
{

    char *check= malloc(strlen(word) + 1);
    int index = hash(word);
    for(int i = 0 , n =strlen(word);i<n ; i++)
    {
        check[i] = tolower(word[i]);
        }

    node *list = table[index];

    while (list != NULL)
    {
        char *cur = list->word;
        if (strcmp(cur, check) == 0){
           return true;
        }
        else{
           node *temp = list->next;
           list = temp;
        }

    }
    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    char check = tolower (word[0]);

    return check - 97;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    char words[46];
    while(fscanf(file, "%s", words) != EOF){
           number +=1;
           int index =  words[0]-97;

           node *n =malloc(sizeof(node));
           strcpy (n-> word ,words);
           n->next = NULL;
           if (table[index]==NULL ){
               table[index] =n;
           }

           else if   (table[index]-> next == NULL) {
               table[index]->next =n;
           }
           else {

           node *temp =table[index]->next;
           n->next = temp;
           table[index]->next=n;
           }

    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return number;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i=0 ; i<N ; i++){
        node *list =table[i];
         while (list != NULL)
    {
        // We point to the next node first
        node *tmp = list->next;
        // Then, we can free the first node
        free(list);
        // Now we can set the list to point to the next node
        list = tmp;
        // If list is null, when there are no nodes left, our while loop will stop
    }


    }
    return true;
}
