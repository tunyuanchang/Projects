typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* Partial_sort(Node*, int);
Node* Split_and_Swap(Node*, int, int);
