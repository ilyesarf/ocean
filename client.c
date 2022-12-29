#include <stdlib.h>
#include <stdio.h>
#include "ocean.h"


int main(int argc, char *argv[]){

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
    printf("%lu\n", sizeof(steps));    
    close(sockfd);

    for (int i = 0; i < size; i++){
        printf("%d ", steps[i]);
    }
    
    return 0;
}