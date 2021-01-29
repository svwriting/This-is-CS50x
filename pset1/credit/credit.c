#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(){
    long Number;
    do{
        Number=get_long("Number:");
    }while (false);
    char* strAns="INVALID";
    int Nl=log10(Number)+1;
    if(Nl!=13 && Nl!=16 && Nl!=15){
            printf("%s\n",strAns);
            return 0;
    }
    int array_Num[Nl];
    for(int i=0;i<Nl;i++){
        array_Num[i]=Number%10;
        Number/=10;
    }
    int oddSum=0;
    for(int i=0;i<Nl;i+=2){
        oddSum+=array_Num[i];
    }
    int evenxSum=0;
    for(int i=1;i<Nl;i+=2){
        int Numix2=array_Num[i]*2;
        if(Numix2<10){
            evenxSum+=Numix2;
        }else{
            evenxSum+=Numix2/10+Numix2%10;
        }
    }
    if((oddSum+evenxSum)%10==0){
        switch(Nl){
            case 13:
                if (array_Num[Nl-1]==4){
                    strAns="VISA";
                }
                break;
            case 15:
                if (array_Num[Nl-1]==3 && (array_Num[Nl-2]==4 || array_Num[Nl-2]==7)){
                    strAns="AMEX";
                }
                break;
            case 16:
                if (array_Num[Nl-1]==4){
                    strAns="VISA";
                }else if(array_Num[Nl-1]==5 && array_Num[Nl-2]>=1 && array_Num[Nl-2]<=5){
                    strAns="MASTERCARD";
                }
                break;
        }
    }
    printf("Nl:%d oddSum:%d evenxSum:%d\n",Nl,oddSum,evenxSum);
    printf("Header:%d%d\n",array_Num[Nl-1],array_Num[Nl-2]);
    printf("%s\n",strAns);
    return 0;
}