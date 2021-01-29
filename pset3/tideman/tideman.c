#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    //int voter_count = get_int("Number of voters: ");//------------------------------------------OOOOOOOOO
    //int voter_count = 5;//--------------------------------------------------------------------1XXXXXXXX
    //char *v[5][3]={{"A","C","B"},{"A","C","B"},{"B","C","A"},{"B","C","A"},{"C","A","B"}};//--1XXXXXXXX
    //int voter_count = 9;//--------------------------------------------------------------------2XXXXXXXX
    //char *v[9][3]={{"A","B","C"},{"A","B","C"},{"A","B","C"},{"B","C","A"},{"B","C","A"},{"C","A","B"},{"C","A","B"},{"C","A","B"},{"C","A","B"}};//--2XXXXXXXX
    int voter_count = 9;//--------------------------------------------------------------------3XXXXXXXX
    char *v[9][4]={{"A","D","B","C"},{"A","D","B","C"},{"A","D","B","C"},{"B","C","A","D"},{"B","C","D","A"},{"C","D","A","B"},{"C","D","A","B"},{"C","D","A","B"},{"C","D","A","B"}};//--3XXXXXXXX

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            //string name = get_string("Rank %i: ", j + 1);//---------------------------------OOOOOOOOO
            string name = v[i][j];//----------------------------------------------------------XXXXXXXXX

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    //XX/*
    printf(">preferences[]:\n");
    for(int i=0;i<candidate_count;i++){
        for(int j=0;j<candidate_count;j++){
            printf(" %d",preferences[i][j]);
        }
        printf(" \n");
    }
    printf(">pairs:\n ");
    int pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            printf("%s%s(%d) ",candidates[pairs[pi].winner],candidates[pairs[pi].loser],preferences[pairs[pi].winner][pairs[pi].loser]);
            pi++;
        }
    }
    //XX*/
    sort_pairs();
    lock_pairs();
    //XX/*
    printf("\n>pairs_sort:\n ");
    pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            printf("%s%s(%d) ",candidates[pairs[pi].winner],candidates[pairs[pi].loser],preferences[pairs[pi].winner][pairs[pi].loser]);
            pi++;
        }
    }
    printf("\n>locked[][]:\n");
    for(int i=0;i<candidate_count;i++){
        for(int j=0;j<candidate_count;j++){
            printf(" %s",locked[i][j]?"true ":"false");
        }
        printf(" \n");
    }
    //XX*/
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for(int i=0;i<candidate_count;i++){
        if(strcmp(candidates[i],name)==0){
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = candidate_count*(candidate_count-1)/2;
    int pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=0;j<candidate_count;j++){
            if(preferences[i][j]>preferences[j][i]){
                pairs[pi].winner=i;
                pairs[pi].loser=j;
                pi++;
            }
        }
    }
    /*
    pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            for(int ij=0;ij<candidate_count;ij++){
                if(ij!=pairs[pi].winner && ij!=pairs[pi].loser){
                    if(locked[ij][pairs[pi].winner]==false || locked[pairs[pi].loser][ij]==false){
                        locked[pairs[pi].winner][pairs[pi].loser]=true;
                    }else{
                        pairs[pi].winner=0;
                        pairs[pi].loser=0;
                    }
                }
            }
            pi++;
        }
    }
    */
    return;
}

// Sort pairs in decreasing order by strength of victory
void swap(int i,int j){
    pair temp_=pairs[i];
    pairs[i]=pairs[j];
    pairs[j]=temp_;
}
void partition(int left,int right){
    int pivoti=(left+right)/2;
    swap(pivoti,right);
    int i=right-1;
    int j=left;
    for(;i>=j;i--){
        //printf("<-[%d] %s%s(%d)\n",i,candidates[pairs[i].winner],candidates[pairs[i].loser],preferences[pairs[i].winner][pairs[i].loser]);
        if(preferences[pairs[i].winner][pairs[i].loser]>=preferences[pairs[right].winner][pairs[right].loser]){
            for(;j<i;j++){
                //printf("[%d]-> %s%s(%d)\n",j,candidates[pairs[j].winner],candidates[pairs[j].loser],preferences[pairs[j].winner][pairs[j].loser]);
                if(preferences[pairs[j].winner][pairs[j].loser]<=preferences[pairs[right].winner][pairs[right].loser]){
                    swap(i,j);
                    pivoti=i;
                    j++;
                    break;
                }
            }
        }
    }
    swap(pivoti,right);
    if(left<pivoti-1){
        partition(left,pivoti-1);
    }
    if(right>pivoti+1){
        partition(pivoti+1,right);
    }
    return;
}
void quicksort_for_pairs(){
    int pn=(candidate_count-1)*candidate_count/2;
    partition(0,pn-1);
    return;
}
void Msort(int left,int right);
void Mmargin(int left1,int right1,int left2,int right2);
void Msort(int left,int right){
    int tlen=right-left+1;
    printf("s%d\n",tlen);
    if(tlen==1){
    }else if(tlen%2==1){
        Msort(left,right-1);
        Mmargin(left,right-1,right,right);
    }else{
        tlen/=2;
        int right1=left+tlen-1;
        int left2=right1+1;
        Msort(left,right1);
        Msort(left2,right);
        Mmargin(left,right1,left2,right);
    }
    return;
}
void Mmargin(int left1,int right1,int left2,int right2){
    printf("M^ ");
    int pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            printf("%s%s(%d) ",candidates[pairs[pi].winner],candidates[pairs[pi].loser],preferences[pairs[pi].winner][pairs[pi].loser]);
            pi++;
        }
    }
    printf("\n");
    //////////////////////////
    int rlen=right2-left1+1;
    pair pairs_[rlen];
    int i1=left1;
    int i2=left2;
    printf("");
    for(int i=left1;i<=right2;i++){
        printf("");
        if(i1>right1){
            pairs_[i]=pairs[i2];
            i2++;
        }else if(i2>right2){
            pairs_[i]=pairs[i1];
            i1++;
        }else if(preferences[pairs[i1].winner][pairs[i1].loser]>preferences[pairs[i2].winner][pairs[i2].loser]){
            pairs_[i]=pairs[i1];
            i1++;
        }else{
            pairs_[i]=pairs[i2];
            i2++;
        }
    }
    for(int i=left1;i<=right2;i++){
        pairs[i]=pairs_[i];
    }
    
    printf("Mv ");
    pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            printf("%s%s(%d) ",candidates[pairs[pi].winner],candidates[pairs[pi].loser],preferences[pairs[pi].winner][pairs[pi].loser]);
            pi++;
        }
    }
    printf("\n");
    //////////////////////////
    return;
}
void marginsort_for_pairs(){
    int pn=(candidate_count-1)*candidate_count/2;
    Msort(0,pn-1);
    return;
}
void sort_pairs(void)
{
    // TODO
    //quicksort_for_pairs();
    marginsort_for_pairs();
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //printf("#locked[0][0]=%s\n",locked[0][0]?"true":"false");
    // TODO
    int pi=0;
    for(int i=0;i<candidate_count;i++){
        for(int j=i+1;j<candidate_count;j++){
            for(int ij=0;ij<candidate_count;ij++){
                if(ij!=pairs[pi].winner && ij!=pairs[pi].loser){
                    if(locked[ij][pairs[pi].winner]==false || locked[pairs[pi].loser][ij]==false){
                        locked[pairs[pi].winner][pairs[pi].loser]=true;
                    }/*else{
                        pairs[pi].winner=0;
                        pairs[pi].loser=0;
                    }*/
                }
            }
            pi++;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int wi;//winner index
    for(int j=0;j<candidate_count;j++){
        bool allfalse=true;
        for(int i=0;i<candidate_count;i++){
           if(locked[i][j]){
               allfalse=false;
               break;
           }
        }
        if(allfalse){
            wi=j;
        }
    }
    printf("%s\n",candidates[wi]);
    return;
}

