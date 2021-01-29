#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checkRep(int i,char *str){
    for(int j=0;j<i;j++){
        if (str[j]==str[i]){
            return true;
        }
    }
    return false;
}

int main(int argc, char *arv[])
{
    //printf("%i %s\n" ,argc ,arv[1]);
    if(argc!=2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if(strlen(arv[1])!=26)
    {
        printf("Key must contain 26 different letters.\n");
        return 1;
    }
    char *key = arv[1];
    for (int i=0;i<26;i++){
        if(((key[i]<'A' || key[i]>'Z')&&(key[i]<'a' || key[i]>'z')) || checkRep(i,key))
        {
            if (checkRep(i,key)){
                printf("X");
            }
            printf("Key must contain 26 different letters.%c\n",key[i]);
            return 1;
        }else{
            key[i]=toupper(key[i]);
        }
    }
    char *STR = get_string("plaintext:");
    printf("ciphertext:");
    int lenSTR = strlen(STR);
    char array_STR[lenSTR];
    
    for (int i = 0 ; i < lenSTR; i++)
    {
        if (STR[i] >= 'A' && STR[i] <= 'Z')
        {
            printf("%c", key[STR[i] - 65]);
            //printf("(%d %d)",STR[i],key);
        }
        else if (STR[i] >= 'a' && STR[i] <= 'z')
        {
            printf("%c", key[STR[i] - 97]+32);
            //printf("(%d %d)",STR[i],key);
        }
        else
        {
            printf("%c", STR[i]);
        }
    }
    printf("\n");
    return 0;
}//hello, world