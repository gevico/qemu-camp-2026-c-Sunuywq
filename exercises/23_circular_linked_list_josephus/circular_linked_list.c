#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) return NULL;
    
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = NULL;
    
    Node* current = head;
    for (int i = 2; i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        current->next = new_node;
        current = new_node;
    }
    
    // 连接成环
    current->next = head;
    return head;
}

void free_list(Node* head) {
    if (!head) return;
    
    Node* current = head;
    Node* next;
    
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != head && current != NULL);
}
