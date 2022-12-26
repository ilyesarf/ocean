#include <stdio.h>
#include <stdlib.h>

int * collatz(int n){
	//todo: use linked lists instead
	int *steps;
	steps = (int *)malloc(sizeof(int)*50);
	
	int id = 0;
	steps[id] = n;

	while(n != 1){

		if ((n%2)==0){
			n /= 2;
		}else {
			n = (n*3)+1;
		}
		
		id++;
		steps[id] = n;
	}
	
	return steps;	
} 

int main(int argc, const char *argv[]){
	int n;
		
	n = atoi(argv[1]);
	
	
	int * steps = collatz(n);
	
	for (int i = 0; i <= 50-1; i++){
		printf("%d ", steps[i]);
	}
	
	printf("\n");

	return 0;
}
