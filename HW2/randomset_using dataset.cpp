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

int p[500] = {661, 535, 3, 166, 792, 232, 902, 132, 161, 785, 77, 348, 815, 834, 439, 195, 702, 974, 775, 704, 450, 206, 822, 740, 997, 664, 577, 41, 59, 415, 42, 848, 952, 960, 953, 905, 348, 455, 409, 133, 162, 626, 803, 941, 228, 256, 886, 143, 788, 543, 165, 140, 208, 182, 201, 183, 507, 163, 567, 300, 96, 110, 478, 254, 748, 625, 970, 745, 229, 826, 917, 504, 352, 595, 504, 166, 508, 168, 97, 524, 273, 682, 422, 670, 224, 433, 603, 653, 634, 564, 878, 208, 102, 148, 345, 653, 462, 199, 223, 790, 741, 928, 459, 71, 850, 527, 135, 379, 416, 754, 390, 332, 902, 802, 228, 471, 742, 779, 63, 727, 558, 650, 785, 125, 52, 971, 930, 336, 821, 903, 606, 45, 66, 642, 870, 471, 375, 25, 40, 649, 860, 900, 576, 977, 244, 428, 329, 39, 351, 454, 309, 48, 168, 364, 307, 543, 561, 221, 978, 361, 832, 542, 455, 468, 696, 654, 274, 141, 82, 371, 570, 115, 343, 126, 392, 188, 527, 5, 826, 684, 882, 500, 144, 667, 540, 45, 166, 869, 559, 905, 861, 314, 246, 177, 106, 568, 681, 770, 98, 560, 178, 320, 461, 471, 923, 382, 510, 468, 293, 493, 426, 679, 555, 611, 322, 366, 999, 428, 693, 843, 790, 423, 818, 598, 723, 325, 530, 475, 679, 731, 809, 926, 477, 970, 630, 672, 894, 187, 3, 574, 963, 797, 320, 531, 759, 445, 524, 918, 743, 362, 779, 391, 404, 578, 328, 330, 999, 295, 600, 452, 376, 539, 711, 454, 217, 11, 551, 701, 13, 156, 483, 477, 194, 954, 902, 14, 251, 673, 497, 655, 918, 254, 672, 468, 431, 199, 664, 366, 296, 111, 498, 74, 485, 481, 487, 20, 65, 919, 780, 671, 690, 422, 391, 890, 902, 11, 892, 752, 799, 365, 437, 836, 375, 529, 138, 728, 78, 220, 504, 565, 628, 709, 697, 649, 14, 694, 920, 877, 878, 215, 632, 224, 209, 53, 36, 901, 473, 910, 658, 498, 644, 406, 255, 737, 764, 696, 1000, 270, 559, 3, 707, 772, 688, 887, 737, 864, 346, 990, 340, 892, 779, 469, 255, 559, 966, 858, 871, 784, 486, 633, 290, 815, 523, 435, 911, 253, 785, 882, 970, 161, 514, 3, 552, 940, 73, 313, 858, 436, 497, 708, 82, 161, 955, 171, 539, 664, 911, 184, 783, 50, 185, 996, 648, 292, 534, 245, 265, 155, 279, 436, 911, 900, 931, 10, 413, 729, 177, 742, 969, 11, 880, 947, 37, 318, 91, 583, 615, 44, 772, 450, 438, 886, 309, 264, 93, 338, 374, 225, 593, 937, 923, 124, 378, 124, 701, 522, 281, 431, 165, 226, 396, 519, 592, 144, 967, 575, 844, 821, 898, 557, 99, 143, 723, 136, 687, 52, 809, 37, 189, 80, 842, 532, 696, 703, 857, 613, 38, 818, 60, 456, 3, 715, 134, 34, 364, 937, 838, 486, 511, 298, 95, 696, 397, 289, 286, 678, 31, 65, 732, 888};
int w[500] = {380, 474, 833, 176, 779, 268, 503, 941, 735, 486, 28, 977, 121, 901, 571, 923, 144, 367, 526, 461, 72, 315, 405, 57, 812, 702, 613, 650, 402, 346, 986, 479, 421, 852, 959, 784, 874, 577, 900, 561, 13, 698, 720, 242, 356, 274, 292, 985, 498, 83, 771, 565, 656, 995, 675, 572, 439, 790, 225, 4, 18, 609, 988, 427, 366, 950, 344, 34, 753, 40, 160, 299, 912, 111, 386, 828, 227, 633, 911, 486, 170, 986, 115, 423, 308, 278, 624, 757, 302, 278, 486, 64, 805, 966, 659, 570, 105, 870, 434, 709, 435, 1, 31, 206, 238, 143, 733, 481, 591, 299, 744, 848, 744, 72, 906, 832, 215, 974, 755, 437, 331, 531, 883, 732, 767, 663, 499, 758, 982, 22, 915, 133, 166, 9, 27, 899, 14, 835, 977, 908, 420, 28, 299, 652, 717, 329, 915, 112, 458, 380, 657, 362, 489, 846, 143, 217, 180, 377, 246, 445, 335, 968, 394, 617, 95, 900, 838, 195, 952, 920, 118, 108, 867, 731, 93, 336, 289, 414, 6, 607, 545, 660, 710, 478, 622, 649, 481, 209, 562, 987, 133, 947, 271, 674, 320, 117, 43, 487, 112, 86, 209, 571, 368, 851, 982, 2, 534, 206, 372, 713, 357, 273, 51, 770, 871, 189, 677, 73, 219, 468, 780, 356, 557, 143, 351, 612, 271, 338, 190, 143, 928, 741, 605, 404, 936, 733, 225, 913, 49, 824, 818, 3, 679, 75, 248, 38, 17, 460, 859, 872, 127, 237, 729, 763, 160, 587, 333, 958, 39, 632, 735, 656, 570, 220, 599, 332, 528, 180, 895, 892, 520, 50, 65, 718, 726, 928, 856, 583, 671, 970, 922, 258, 149, 18, 411, 618, 86, 942, 252, 53, 346, 326, 887, 104, 498, 45, 265, 276, 201, 252, 827, 819, 984, 995, 55, 89, 594, 362, 307, 337, 661, 274, 374, 851, 929, 486, 853, 13, 254, 945, 493, 768, 194, 461, 960, 825, 446, 756, 582, 682, 410, 536, 236, 45, 946, 772, 556, 583, 331, 9, 687, 699, 667, 255, 819, 390, 824, 660, 919, 396, 805, 946, 887, 537, 756, 29, 651, 53, 910, 324, 292, 203, 256, 373, 266, 592, 982, 5, 613, 726, 567, 390, 181, 333, 156, 292, 923, 163, 155, 994, 56, 490, 213, 169, 929, 240, 842, 240, 856, 196, 732, 136, 477, 663, 219, 719, 524, 304, 45, 220, 989, 93, 764, 635, 981, 600, 565, 763, 842, 492, 961, 113, 648, 358, 507, 165, 440, 5, 397, 884, 381, 57, 693, 249, 3, 809, 546, 106, 988, 531, 41, 621, 147, 272, 729, 996, 349, 599, 504, 539, 304, 671, 657, 290, 190, 931, 437, 158, 652, 443, 656, 900, 92, 226, 486, 122, 165, 847, 161, 12, 260, 835, 605, 125, 506, 35, 128, 299, 580, 764, 445, 498, 612, 76, 742, 642, 956, 395, 271, 885, 772, 281, 319, 180, 489, 739, 308, 950, 797, 507, 538, 349, 520, 497, 735, 770, 427, 87, 128, 88};

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
    W = 1000;
    printf("N : 500 W : %d\n", W);
    


    for(int i=1; i<=500; i++){
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
