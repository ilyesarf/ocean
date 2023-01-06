#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../ocean/ocean.h"


int main(int argc, char *argv[]){
    clock_t start = clock();

    int sockfd;
    sockfd = init_client();
    
    int input;
    if (argc > 1){
        input = atoi(argv[argc-1]);
    } else{
        input = 10;
    }

    send_input(sockfd, input);

    int size = recv_size(sockfd);

    int steps[size];
    recv_steps(sockfd, size, steps);
    
    close(sockfd);

    for (int i = 0; i < size; i++){
        printf("%d ", steps[i]);
    }

    clock_t end = clock();
    
    printf("\nExecution time: %f seconds\n", (double)(end - start)/CLOCKS_PER_SEC);
    return 0;
}
