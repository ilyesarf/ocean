
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    return node;
}

void collatz(int n, Node** head) {
    Node* node = create_node(n);
    node->next = *head;
    *head = node;    
	Node* current = *head;

	while (n != 1){
		if (n%2 == 0){
			n = n/2;
		} else {
			n = 3*n+1;
		}

		current->next = create_node(n);
		current = current->next;
	}
}

int main(int argc, char* argv[]) {
    int n = 10;
    if (argc > 1) {
		n = atoi(argv[1]);    // Read n from the command line if provided
    }

    Node* head = NULL;
    collatz(n, &head);
    Node* current = head;

    while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
    }

    printf("\n");
    return 0;

}	