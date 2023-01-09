typedef struct Node {
    int data;
    struct Node* next;
} Node;

extern int init_client();

extern int init_server();

extern void send_input(int sockfd, int input);

extern void recv_input(int sockfd, int* cli_sfd, int* input);

extern int recv_size(int sockfd);

extern void send_size(int cli_sfd, int size);

extern void recv_steps(int sockfd, int size, int steps[]);

extern void send_steps(int cli_sfd, int number);

