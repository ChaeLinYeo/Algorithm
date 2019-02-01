#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
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

// int p[1001];
// int w[1001];
// float pw[1001];

int p[101] = {0, 20, 30, 35, 12,3};
int w[101] = {0, 2, 5, 7, 3, 1};
float pw[101] = {0, 10, 6, 5, 4, 3};

int N, W;
int maxProfit;
node maxNode;

float bound(node);

long long knapsack_monte(){
   srand(time(NULL));
   int num = rand()%(N-1);
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
         if(num != 0){
            int ran = rand()%2;
            if(ran == 1){
               u.level = v.level+1;
               u.weight = v.weight + w[u.level];
               u.profit = v.profit + p[u.level];
               if(u.weight <= W && u.profit > maxProfit) maxProfit = u.profit;
               u.bound = bound(u);
               if(u.bound > maxProfit) pq.push(u);
            } else{
               num--;
               u.weight = v.weight;
               u.profit = v.profit;
               u.bound = bound(u);
               if(u.bound > maxProfit) pq.push(u);
            }
            cntNode++;
         } else{
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
   }
   
   return cntNode;
}

bool isPromissing(node u, int maxProfit){
   if(maxProfit > u.bound) return false;
   if(u.weight > W) return false;
   if(u.profit == u.bound) return false;

   return true;
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

int knapsack(){
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

int main(){
   long long rrr=0;
   long long rrrr=0;
   W=13;
   N=5;

   // for(int i=1; i<=N; i++){
   //    for(int j=i;j<=N; j++){
   //       if(pw[i] < pw[j]){
   //          int a = p[i];
   //          p[i] = p[j];
   //          p[j] = a;
   //          a = pw[i];
   //          pw[i] = pw[j];
   //          pw[j] = a;
   //          a = w[i];
   //          w[i] = w[j];
   //          w[j] = a;
   //       }
   //    }
   //    //printf("p : %d w : %d pw : %d\n", p[i], w[i], pw[i]);
   // }

   for(int k=0; k<10; k++){
      // srand(time(NULL));
      // N=10;
      // W = 20;
      //printf("N : %d W : %d\n", N, W);
      
      // for(int i=1; i<=N; i++){
      //    p[i] = (rand()%10)*10;
      //    w[i] = rand()%10 + 1;
      //    pw[i] = p[i]/w[i];
      //    // printf("i : %d p : %d w : %d pw : %f\n",i, p[i], w[i], pw[i]);
      // }
      
      // for(int i=1; i<=N; i++){
      //    for(int j=i;j<=N; j++){
      //       if(pw[i] < pw[j]){
      //          int a = p[i];
      //          p[i] = p[j];
      //          p[j] = a;
      //          a = pw[i];
      //          pw[i] = pw[j];
      //          pw[j] = a;
      //          a = w[i];
      //          w[i] = w[j];
      //          w[j] = a;
      //       }
      //    }
      //    // printf("p : %d w : %d pw : %d\n", p[i], w[i], pw[i]);
      // }
      
      long long result = 0;
      // long long real_result = 0;
      for(int i =0; i<100000; i++){
         long long r = knapsack_monte();
         result +=r ;
         // r = knapsack();
         // real_result += r;
         //printf("%lld   ", r);
      }
      // long long result = knapsack();
      //printf("average number of visit node : %lld / %lld\n", result/1000, real_result/1000);
      rrr += result/100000;
      // rrrr += real_result/10000;
      // rrr += result;
   }

   printf("all average number of visit node : %lld\n", rrr/10);
   // printf("%d\n", knapsack_monte());
}
