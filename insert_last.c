#include "invert.h"

/* Function to insert the data to single linked list */
int insert_last(Slist** head, char data[]) {
    Slist *node = createNode(data);
    if (node == NULL) {
        return FAILURE;
    }
    if (*head == NULL) {
        *head = node;
        return SUCCESS;
    }
    Slist* temp = *head;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = node;
    return SUCCESS;
}

/* Function to create new node */
Slist* createNode(char data[]) {
    Slist* node = malloc(sizeof(Slist));
    if (node == NULL) {
        return NULL;
    }
    strcpy(node->data, data);
    node->link = NULL;
    return node;
}