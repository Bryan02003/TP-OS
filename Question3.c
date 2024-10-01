#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>

typedef struct Node 
{
    int data;
    struct Node* next;
}Node;

Node* create_linked_list(int n)
{
    Node* head=NULL;
    Node* temp = NULL;

    for(int i=1;i<=n;i++)
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data=i;
        new_node->next=NULL;

        if (head==NULL)
        {
            head=new_node;
        }
        else
        {
            temp->next=new_node;
        }
        temp=new_node;
    }
    return head;
}

void display(Node* head)
{
    while(head !=NULL)
    {
        printf("<%p> %d-> ", (void*)head,head->data);
        head=head->next;
    }
    printf("NULL\n");
}

int size_list(Node* head)
{
    int count = 0;
    while(head !=NULL)
    {
        count++;
        head=head->next;
    }
}

int main()
{
    Node* linked_list=create_linked_list(6);
    printf("Création de la liste\n");
    display(linked_list);

    return 0;
}


