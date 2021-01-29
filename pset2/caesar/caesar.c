#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *arv[])
{
    //printf("%i %s\n" ,argc ,arv[1]);
    if(argc!=2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i=0;i<strlen(arv[1]);i++){
        if(!isdigit(arv[1][i])){
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(arv[1]);
    char *STR = get_string("plaintext:");
    printf("ciphertext:");
    int lenSTR = strlen(STR);
    char array_STR[lenSTR];
    
    for (int i = 0 ; i < lenSTR; i++)
    {
        if (STR[i] >= 'A' && STR[i] <= 'Z')
        {
            printf("%c", (STR[i] - 65 + key) % 26 + 65);
            //printf("(%d %d)",STR[i],key);
        }
        else if (STR[i] >= 'a' && STR[i] <= 'z')
        {
            printf("%c", (STR[i] - 97 + key) % 26 + 97);
            //printf("(%d %d)",STR[i],key);
        }
        else
        {
            printf("%c", STR[i]);
        }
    }
    printf("\n");
    return 0;
}//be sure to drink your Ovaltine