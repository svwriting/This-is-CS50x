#include <stdio.h>
#include <cs50.h>

int main(){
    int money=-1;
    while (money<0 || money%1>0 ){
        money=get_float("Change owed:")*1000/10;
    }
    int coins[]={25,10,5,1};
    int N=0;
    for(int i=0;money!=0 || i<sizeof(coins)/sizeof(coins[0]);i++){
        N+=money/coins[i];
        money%=coins[i];
    }
    printf("%d\n",N);
    return 0;
}