#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>

using namespace std;

//maxprofit =  max profit of last node + profit of current node or 0;
//maxweight = weight of last node + SUM<int i=current level, k-1>(weight[i]);
//bound = maxprofit + SUM<int i=current level, k-1>(profit[i]) + (W-maxweight)pw[k];

typedef struct{
    int level;
    int profit;
    int weight;
    float bound;
} node;

bool operator<(node a, node b){
    return a.bound < b.bound;
}

int N, W;
int cntD=0;
int maxProfit=0;
node maxNode;

int p[501];
int w[501];
float pw[501];
bool bestset[501] = {false,false,false,false,false};//정답.
bool include[501] = {false,false,false,false,false};//포함여부
int numset[501] = {0};//뭐지

float bound(node);
bool promising(int);
void knapsack_dfs(int,int,int);
int knapsack_bfs(int,int);
int knapsack_best();

int main(){
    srand(time(NULL));
    N=500;
    W = 45;
    printf("N : 500 W : %d\n", W);
    
    for(int i=1; i<=500; i++){
        p[i] = (rand()%10)*10;
        w[i] = rand()%20 + 1;
        pw[i] = p[i]/w[i];
        //printf("i : %d p : %d w : %d pw : %f\n",i, p[i], w[i], pw[i]);
    }
    
    for(int i=1; i<=N; i++){
        for(int j=i;j<=N; j++){
            if(pw[i] < pw[j]){
                int a = p[i];
                p[i] = p[j];
                p[j] = a;
                a = pw[i];
                pw[i] = pw[j];
                pw[j] = a;
                a = w[i];
                w[i] = w[j];
                w[j] = a;
            }
        }
        //printf("p : %d w : %d pw : %d\n", p[i], w[i], pw[i]);
    }
    
    knapsack_dfs(0,0,0);
    printf("dfs  < maxProfit : %d number of visit node : %d\n", maxProfit, cntD);
    printf("bfs  < maxProfit : %d number of visit node : %d\n", maxProfit, knapsack_bfs(N,W));
    printf("best < maxProfit : %d number of visit node : %d\n", maxProfit, knapsack_best());
}

void knapsack_dfs(int i, int profit, int weight){
    //printf("LEVEL : %d , Profit : %d, Weight : %d \n",i,profit,weight);
    if(weight <= W && profit > maxProfit){
        maxProfit = profit;
        numset[i] = i;
        for(int tmp = 1; tmp <= N; tmp ++)
            bestset[tmp] = include[tmp];
    }
    
    if(promising(i)){
        include[i+1] = true;
        knapsack_dfs(i+1, profit + p[i+1], weight + w[i+1]);
        include[i+1] = false;
        knapsack_dfs(i+1, profit,weight);
    }
    cntD++;
}

int knapsack_bfs(int n, int maxW){
    int cnt=0;
    maxProfit=0;
    queue<node> Q;
    node u, v;
    v.level = 0; v.profit = 0; v.weight = 0; maxProfit = 0;
    Q.push(v);
    cnt++;
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        u.level = v.level + 1;
        u.profit= v.profit + p[u.level];
        u.weight= v.weight + w[u.level];
        //printf("u.profit = %d, u.weight = %d\n",u.profit, u.weight);
        if((u.weight <= W) && (u.profit > maxProfit))
            maxProfit = u.profit;
        if(bound(u) > maxProfit){//유망
            Q.push(u);
            cnt++;
        }
        else cnt++; //안유망
        
        u.weight = v.weight;
        u.profit = v.profit;
        if(bound(u) > maxProfit){ //유망
            Q.push(u);
            cnt++;
        }
        else cnt++; //안유망
    }
    
    return cnt;
}

int knapsack_best(){
    priority_queue<node> pq;
    int cntNode=1;
    
    node v, u;
    v.level = 0; v.profit = 0; v.weight = 0;
    v.bound = bound(v);
    pq.push(v);
    
    maxProfit = 0;
    maxNode = v;
    //printf("visit [level : %d profit : %d weight : %d bound : %f]\n", 0, v.profit, v.weight, v.bound);
    
    while(!pq.empty()){
        v = pq.top();
        pq.pop();
        
        if(v.bound > maxProfit){
            u.level = v.level+1;
            u.weight = v.weight + w[u.level];
            u.profit = v.profit + p[u.level];
            if(u.weight <= W && u.profit > maxProfit) maxProfit = u.profit;
            u.bound = bound(u);
            if(u.bound > maxProfit) pq.push(u);
            //printf("visit [level : %d  profit : %d weight : %d bound : %f]\n", u.level, u.profit, u.weight, u.bound);
            
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = bound(u);
            if(u.bound > maxProfit) pq.push(u);
            //printf("visit [level : %d  profit : %d weight : %d bound : %f]\n", u.level, u.profit, u.weight, u.bound);
            cntNode += 2;
        }
    }
    
    return cntNode;
}

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
    //printf(" Promising? Profit : %d, Weight : %d\n",profit,weight);
    if(weight >= W) return false;
    else {
        j = i+1;
        bound = (float)profit;
        totalWeight = weight;
        while((j <= N) && (totalWeight + w[j] <= W)){
            totalWeight = totalWeight + w[j];
            bound = bound + (float)p[j];
            j++;
        }
        k = j;
        if(k <= N)
            bound = bound + (float)((W - totalWeight) * (p[k]/w[k]));
        //printf(" Bound : %f\n\n", bound);
        return (bound>(float)maxProfit);
    }
}

float bound(node u){
    int j,k;
    int totweight;
    float result;
    if(u.weight >= W) return 0;
    else {
        result = u.profit;
        j = u.level+1;
        totweight = u.weight;
        while(j <= N && totweight + w[j] <= W){
            totweight = totweight + w[j];
            result = result +p[j];
            j++;
        }
        k=j;
        if(k <= N) result = result + (W-totweight)*pw[k];
    }
    
    return result;
}
