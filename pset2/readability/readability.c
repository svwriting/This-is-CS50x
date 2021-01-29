#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(){
    char* STR=get_string("Text:");
    int lenSTR=strlen(STR);
    int countL=0;
    int countS=0;
    int countPEQ=0;//P=Period(46), E=Exclamation Point(33), Q=Question Mark(63))
    for(int i=0;i<lenSTR;i++){
        if (STR[i]==' '){
            countS++;
        }else if(STR[i]==46 || STR[i]==33 || STR[i]==63){
            countPEQ++;
        }else if((STR[i]>='A' && STR[i]<='Z')||(STR[i]>='a' && STR[i]<='z')){
            countL++;
        }
    }
    double L=((double)countL/((double)countS+1));
    double S=((double)countPEQ/((double)countS+1));
    double judgeValue = 5.88 * L - 29.6 * S - 15.8;
    //printf("lenSTR=%d \ncountL=%d countS=%d countPEQ=%d \nL=%f S=%f judgeValue=%f\n",lenSTR,countL,countS,countPEQ,L,S,judgeValue);
    if (judgeValue>=16){
        printf("Grade 16+\n");
    }else if(judgeValue<1){
        printf("Before Grade 1\n");
    }else{
        printf("Grade %d\n",(int)round(judgeValue));
    }
    return 0;
}
