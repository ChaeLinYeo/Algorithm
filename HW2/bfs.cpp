#include <stdio.h>
#include <stdlib.h>
#define N 4
#define MAX_WEIGHT 16
const int p[N+1] = {0, 40, 30, 50, 10};
const int w[N+1] = {0, 2, 5, 10, 5};

using namespace std;
struct node;
struct node{
    node* next;
    int level;
	int profit;
	int weight;
};

struct queue_of_node{
    node* first;
	node* last;
};

void knapsack(int n, int maxW, int &maxprofit);
float bound(node u);
void enqueue(queue_of_node &Q, node);
void dequeue(queue_of_node &Q, node &);
bool empty(queue_of_node &Q);
void initialize(queue_of_node &Q);
int cnt = 0;

bool empty(queue_of_node &Q){
    if(Q.first == NULL && Q.last == NULL) return true;
	else return false;
}

void initialize(queue_of_node &Q){
	Q.first = (node*)malloc(sizeof(node*));
	Q.last = (node*)malloc(sizeof(node*));
	Q.first = NULL;
	Q.last = NULL;
}
 
void enqueue(queue_of_node &Q, node inputNode){
	node* n = (node*)malloc(sizeof(node*));
	n ->level = inputNode.level;
	n ->profit = inputNode.profit;
	n ->weight = inputNode.weight;
	n ->next = NULL;
	if(empty(Q) == true){
		Q.first = n;
		Q.last = n;
	}
	else{
		while(Q.last->next != NULL) Q.last->next = n;

		Q.last -> next = n;
		Q.last = Q.last -> next;
	}
}


void dequeue(queue_of_node &Q, node &v){
    node* n = (node*)malloc(sizeof(node*));
	if(empty(Q) == true) return;
	else{
		if(Q.first == Q.last)
		{
			v.level = Q.first ->level;
			v.profit = Q.first -> profit;
			v.weight = Q.first -> weight;
			Q.last = NULL;
			free(Q.first);
			Q.first = NULL;
		}
		else{
			v.level = Q.first ->level;
			v.profit = Q.first -> profit;
			v.weight = Q.first -> weight;
			n = Q.first;
			Q.first = Q.first -> next;
			n -> next = NULL;
			free(n);
		}
	}
}


void knapsack(int n, int maxW, int &maxprofit){
	queue_of_node Q;
	node u, v;
	initialize(Q);
	v.level = 0; v.profit = 0; v.weight = 0; maxprofit = 0;
	enqueue(Q,v);
	cnt++;
	while(!empty(Q)){
		dequeue(Q,v);
		u.level = v.level + 1;
		u.profit= v.profit + p[u.level];
		u.weight= v.weight + w[u.level];
		printf("u.profit = %d, u.weight = %d\n",u.profit, u.weight);
		if((u.weight <= MAX_WEIGHT) && (u.profit > maxprofit))
			maxprofit = u.profit;
		if(bound(u) > maxprofit){
			enqueue(Q,u);
			cnt++;
		}
		else cnt++;
		u.weight = v.weight;
		u.profit = v.profit;
		if(bound(u) > maxprofit){
			enqueue(Q,u);
			cnt++;
		}
		else cnt++;
	}
}

float bound(node u){
	int j,k;
	int totalWeight;
	float result;
	if(u.weight >= MAX_WEIGHT) return 0;
	else{
		result = u.profit;
		j = u.level + 1;
		totalWeight = u.weight;
		while((j<=N) && (totalWeight + w[j] <= MAX_WEIGHT)){
			totalWeight = totalWeight + w[j];
			result = result + p[j];
			j++;
		}
		k = j;
		if(k <= N)
		result = result + (MAX_WEIGHT - totalWeight) * (p[k]/w[k]);
		printf("bound(result) : %.1f\n", result);
		return result;
	}
}

int main(){
	int answer = 0;
	knapsack(N,MAX_WEIGHT,answer);
	printf("\nMAXPROFIT : %d$\n",answer);
	printf("total_num_of_nodes_visited : %d\n", cnt);
	return 0;
}
