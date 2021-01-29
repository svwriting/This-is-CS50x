#include <stdio.h>
#include <cs50.h>

int main(){
    int hight=0;
    while (hight>8 || hight<1){
        hight=get_int("Height:");
    }
    char* Str_s="        ";
    char* Str_d="########";
    for(int i=1;i<=hight;i++){
        printf("%.*s",hight-i,Str_s);
        printf("%.*s",i,Str_d);
        printf("  ");
        printf("%.*s",i,Str_d);
        printf("\n");
        //printf("%.*s%.*s  %.*s\n",hight-i,"        ",i,"########",i,"########");
    }
    return 0;
}