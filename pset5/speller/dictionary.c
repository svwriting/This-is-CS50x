// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>

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

int dsize=0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int sl=strlen(word);
    char word_[sl];
    strcpy(word_,word);
    for(int i=0;i<sl;i++){
        word_[i]=tolower(word[i]);
    }
    int index=hash(word_);
    node *temp_=table[index];
    while(temp_){
        if (!strcmp(temp_->word,word_)){
            return true;
        }else{
            temp_=temp_->next;
        }
    }
    return false;
}



//first letter
unsigned int hash_fl(const char *word){
    int i=tolower(word[0])-97;
    return i;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int index;
    index=hash_fl(word);//first letter
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *reader=fopen(dictionary,"r");
    if(!reader){
        printf("Can't open/find the file :(\n");
        return false;
    }
    char buffer[LENGTH];
    while(fscanf(reader,"%s",buffer)!=EOF){
        dsize++;
        int index=hash(buffer);
        node *temp_=malloc(sizeof(node));
        strcpy(temp_->word,buffer);
        temp_->next=table[index];
        table[index]=temp_;
    }
    fclose(reader);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dsize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i=0;i<26;i++){
        node *temp_=table[i];
        while(temp_){
            temp_=table[i]->next;
            free(table[i]);
            table[i]=temp_;
        };
        free(table[i]);
    }
    return true;
}
