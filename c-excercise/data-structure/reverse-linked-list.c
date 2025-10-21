#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* head = NULL;
void Reverse()
{
    struct Node *current, *prev, *next;
    current = head;
    prev = NULL;
    
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

/*
 * Inserts a new node with the given 'data' at position 'n' in the linked list.
 * Parameters:
 *   data - the integer value to store in the new node.
 *   n    - the position (1-based index) at which to insert the new node.
 *          n must be between 1 and (length of list + 1), inclusive.
 *          If n is out of bounds, the function prints an error and does not insert.
 */
void Insert(int data, int n)
{
    struct Node* tmp1 = (struct Node*)malloc(sizeof(struct Node));
    if (tmp1 == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    tmp1->data = data;
    tmp1->next = NULL;
    if(n == 1) {
        tmp1->next = head;
        head = tmp1;
        return;
    }
    struct Node* tmp2 = head;
    for(int i = 0; i < n-2; i++) {
        if (tmp2 == NULL) {
            printf("Error: Position out of bounds\n");
            free(tmp1);
            return;
        }
        tmp2 = tmp2->next;
    }
    if (tmp2 == NULL) {
        printf("Error: Position out of bounds\n");
        free(tmp1);
        return;
    }
    tmp1->next = tmp2->next;
    tmp2->next = tmp1;
}

// Prints all elements in the linked list starting from the head node,
// displaying each node's data value followed by a space, and ends with a newline.
void Print()
{
    struct Node* temp = head;
    while (temp != NULL)
    {
        printf("%i ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void)
{
    Insert(2,1); // List: 2
    Insert(3,2); // List: 2,3
    Insert(4,1); // List 4,2,3
    Insert(5,4); // List 4,2,3,5
    Print();
    Reverse();
    Print();
    return 0;
}