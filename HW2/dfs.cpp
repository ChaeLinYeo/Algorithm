#include <stdio.h>
#include <stdlib.h>
//#define N 4
//#define MAX_WEIGHT 16
//int p[N+1] = {0, 40, 30, 50, 10};
//int w[N+1] = {0, 2, 5, 10, 5};
#define N 5
#define MAX_WEIGHT 13
int p[N+1] = {0, 20, 30, 35, 12, 3};
int w[N+1] = {0, 2, 5, 7, 3, 1};

int maxProfit = 0;
bool bestset[N+1] = {false};
bool include[N+1] = {false};
int numset[N+1] = {0};

int cnt = 0;
void knapsack(int, int, int);
bool promising(int);

bool promising(int i){
    int j, k;
    int totalWeight;
    float bound;
    int weight = 0, profit = 0;
    for(int tmp = 1; tmp <= i; tmp ++){
            if(include[tmp] == true){
                    weight = weight + w[tmp];
                    profit = profit + p[tmp];
            }
    }
    printf(" Promising? Profit : %d, Weight : %d\n",profit,weight);
    if(weight >= MAX_WEIGHT) return false;
    else {
            j = i+1;
            bound = (float)profit;
            totalWeight = weight;
            while((j <= N) && (totalWeight + w[j] <= MAX_WEIGHT)){
                    totalWeight = totalWeight + w[j];
                    bound = bound + (float)p[j];
                    j++;
            }
            k = j;
            if(k <= N)
                bound = bound + (float)((MAX_WEIGHT - totalWeight) * (p[k]/w[k]));
            printf(" Bound : %f\n\n", bound);
            return (bound>(float)maxProfit);
    }
}

void knapsack(int i, int profit, int weight){
    printf(" LEVEL : %d , Profit : %d, Weight : %d \n",i,profit,weight);
    if(weight <= MAX_WEIGHT && profit > maxProfit){
            maxProfit = profit;
            numset[i] = i;
            for(int tmp = 1; tmp <= N; tmp ++)
                bestset[tmp] = include[tmp];
    }
 
    if(promising(i)){
            include[i+1] = true;
            knapsack(i+1, profit + p[i+1], weight + w[i+1]);
            include[i+1] = false;
            knapsack(i+1, profit,weight);
    }
    cnt++;
		// printf("\n");
}

int main(){
    knapsack(0,0,0);
    for(int tmp = 1 ; tmp <= N ; tmp++)
        printf("%d번째 : %d\n",tmp,bestset[tmp]);
    printf("MAXPROFIT : %d$ \n\n",maxProfit);
    printf("total_num_of_nodes_visited : %d\n", cnt);
    return 0;
}
