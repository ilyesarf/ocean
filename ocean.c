#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include "ocean.h"

int pack(int data){
    return htons(data);
}

int unpack(int packed_data){
    return ntohs(packed_data);
}

int client(int input){
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

    int packed_input = pack(input);
    if (send(sockfd, &packed_input, sizeof packed_input, 0) < 0){
        perror("Can't send data to server");
        return -3;
    }

    close(sockfd);
    return 0;
}

int server(){
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

    struct sockaddr cli_addr;
    socklen_t sin_size;
    int cli_sfd;
    
    while (1){
        sin_size = sizeof cli_addr;
        cli_sfd = accept(sockfd, (struct sockaddr *)&cli_addr, &sin_size);
        if (cli_sfd == -1){
            perror("Can't accept connection");
            return -4;
        }

        int input;
        if (recv(cli_sfd, &input, sizeof input, 0) < 0){
            perror("Can't recieve data");
            return -5;
        }

        input = unpack(input);
        printf("Client sent %d\n", input);
    }

    close(sockfd);
    return 0;
}
