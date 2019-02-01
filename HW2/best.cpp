#include <stdio.h>
#include <vector>
#include <queue>

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

int p[101];
int w[101];
float pw[101];

int N, W;
int maxProfit;
node maxNode;

float bound(node);

int knapsack(){
    priority_queue<node> pq;
    int cntNode=1;
    
    node v, u;
    v.level = 0; v.profit = 0; v.weight = 0;
    v.bound = bound(v);
    pq.push(v);
    
    maxProfit = 0;
    maxNode = v;
    printf("visit [level : %d profit : %d weight : %d bound : %f]\n", 0, v.profit, v.weight, v.bound);
    
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
            printf("visit [level : %d  profit : %d weight : %d bound : %f]\n", u.level, u.profit, u.weight, u.bound);
            
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = bound(u);
            if(u.bound > maxProfit) pq.push(u);
            printf("visit [level : %d  profit : %d weight : %d bound : %f]\n", u.level, u.profit, u.weight, u.bound);
            cntNode += 2;
        }
    }
    
    return cntNode;
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

int main(){
    scanf("%d %d", &N, &W);
    
    for(int i=1; i<=N; i++){
        scanf("%d %d", &p[i], &w[i]);
        pw[i] = p[i]/w[i];
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
    }
    int num = knapsack();
    printf("maxProfit : %d \nnumber of visit node : %d\n", maxProfit, num);
}
