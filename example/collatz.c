
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../ocean.h"

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    return node;
}

void collatz(int n, Node** head, int* size) {

    Node* node = create_node(n);
    node->next = *head;
    *head = node;    
	Node* current = *head;

    *size = 1;
	while (n != 1){
		if (n%2 == 0){
			n = n/2;
		} else {
			n = 3*n+1;
		}

        *size = *size + 1;
		current->next = create_node(n);
		current = current->next;
	}
}

int main(int argc, char* argv[]) { 
    int sockfd = init_server();
    
    printf("Listening on %d...\n", sockfd);
    while(1){
        int cli_sfd, input;
        recv_input(sockfd, &cli_sfd, &input);

        int size;

        Node* head = NULL;
        collatz(input, &head, &size);

        send_size(cli_sfd, size);

        send_steps(cli_sfd, size, head);
        close(cli_sfd);
    }

    close(sockfd);
    return 0;
}	
