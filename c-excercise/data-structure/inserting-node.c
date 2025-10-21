#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

struct Node{
    int data;
    struct Node* next;
};


struct Node* Insert(struct Node* head, int x);
void Print(struct Node* head);

int main(void) 
{
    struct Node *head = NULL;
    printf("How long your list should be? \n");
    int n,x,i;
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the number: \n");
        scanf("%d", &x);
        head = Insert(head, x);
        Print(head);
    }
    struct Node* ptr = head;
    while (ptr != NULL)
    {
        struct Node* next = ptr->next;
        free(ptr);
        ptr = next;
    }
    
    return 0;
}

struct Node* Insert(struct Node* head, int x)
{
    struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
    tmp->data = x;
    tmp->next = NULL;
    if(head != NULL) tmp->next = head;
    head = tmp;
    return head; 
}

void Print(struct Node* head)
{
    struct Node* tmp = head;
    printf("List is: ");
    while (tmp != NULL)
    {
        printf(" %i", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}