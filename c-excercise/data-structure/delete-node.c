#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* head = NULL;
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

void Delete(int n)
{
    struct Node* tmp1 = head;
    if (n == 1)
    {
        head = tmp1->next;
        free(tmp1);
        return;
    }
    for (int i = 0; i < n-2; i++)
    {
        tmp1 = tmp1->next;
    }
    struct Node* tmp2 = tmp1->next;
    tmp1->next = tmp2->next;
    free(tmp2);
    
}

int main(void)
{
    Insert(2,1);
    Insert(5,2);
    Insert(6,3);
    Insert(3,2);
    Print();
    int n;
    printf("Enter a position\n");
    scanf("%i", &n);
    Delete(n);
    Print();
}