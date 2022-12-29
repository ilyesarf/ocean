#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "ocean.h"

//helpers
int pack(int data){
    return htons(data);
}

int unpack(int packed_data){
    return ntohs(packed_data);
}

//client side
int init_client(){
    int sockfd;
    struct sockaddr_in cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        perror("Socket not created");
        return -1;
    }

    cli.sin_addr.s_addr = inet_addr("127.0.0.1");
    cli.sin_family = AF_INET;
    cli.sin_port = htons(1337);

    if (connect(sockfd, (struct sockaddr *)&cli, sizeof(cli)) < 0){
        close(sockfd);
        perror("Can't connect to server");
        return -2;
    } 

    return sockfd;
}

void send_input(int sockfd, int input){
    int packed_input = pack(input);

    if (send(sockfd, &packed_input, sizeof packed_input, 0) < 0){
        perror("Can't send data to server");
    }
}

int recv_size(int sockfd){
    int packed_size;
    if (recv(sockfd, &packed_size, sizeof packed_size, 0) < 0){
        perror("Can't recieve size");
        return -1;
    }

    int size = unpack(packed_size);

    return size;
}

void recv_steps(int sockfd, int size, int steps[]){
    for (int i = 0; i < size; i++){
        int packed_number;
        if (recv(sockfd, &packed_number, sizeof packed_number, 0) < 0){
            perror("Can't recieve number");
        }

        steps[i] = unpack(packed_number);        
    }
}

//server side
int init_server(){
    int sockfd;
    struct sockaddr_in srv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        perror("Socket not created");
        return -1;
    }

    srv.sin_addr.s_addr = INADDR_ANY;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(1337);

    if (bind(sockfd, (struct sockaddr *)&srv, sizeof(srv)) < 0){
        perror("Can't open port");
        return -2;
    }

    if (listen(sockfd, 2) < 0){
        perror("Can't listen !!");
        return -3;
    }
 
    return sockfd;
}

void recv_input(int sockfd, int* cli_sfd, int* input){
    struct sockaddr cli_addr;
    socklen_t sin_size;
    
    sin_size = sizeof cli_addr;

    *cli_sfd = accept(sockfd, (struct sockaddr *)&cli_addr, &sin_size);
    if (*cli_sfd == -1){
        perror("Can't accept connection");
    }

    int packed_input;
    if (recv(*cli_sfd, &packed_input, sizeof packed_input, 0) < 0){
        perror("Can't recieve data");
    }

    *input = unpack(packed_input);
}    

void send_size(int cli_sfd, int size){
    int packed_size = pack(size);

    if (write(cli_sfd, &packed_size, sizeof packed_size) < 0){
        perror("Can't send size to client");
    }

}

void send_steps(int cli_sfd, int size, Node* head){
    Node* current = head;

    for (int i = 0; i < size; i++){
        //printf("%d ", current->data);
        if (current != NULL){
            int packed_number = pack(current->data);
            if (write(cli_sfd, &packed_number, sizeof packed_number) < 0){
                perror("Can't send step");
            }
            
            current = current->next;
        }
    }
}