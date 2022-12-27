typedef struct Node {
    int data;
    struct Node* next;
} Node;

extern int client(int n);

extern int server();