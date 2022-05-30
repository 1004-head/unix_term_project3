#ifndef LINKEDLIST_NODE_H
#define LINKEDLIST_NODE_H
struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
};
typedef struct Node Node;
#endif //LINKEDLIST_NODE_H