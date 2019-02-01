#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	srand(time(NULL));
	for(int i = 0 ; i<500 ; i++){
		int random = rand()%1000+1;
		printf("%d, ", random);
	}
	printf("\n");
}
