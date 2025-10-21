#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node {
    int index;
    int number;
    struct node *next;
} node;

int main(int argc,char *argv[])
{
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->index = i;
        n->number = number;
        n->next = list;
        list = n;
    }

    node *ptr = list;
    if (ptr == NULL)
    {
        printf("Empty List!\n");
    }
    printf("-------------------------------------------------\n");
    while (ptr != NULL)
    {
        printf("Node %p | index=%d value=%d | next=@-%p\n",
                (void *)ptr, ptr->index, ptr->number, (void *)ptr->next);
        ptr = ptr->next;
    }
    printf("-------------------------------------------------\n");

    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
