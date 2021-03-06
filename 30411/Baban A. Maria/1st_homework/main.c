#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
} NodeT;

NodeT *head;
NodeT *tail;

void addFirst(int code)
{
    NodeT *elem;
    if (head==NULL)
    {
        head=(NodeT *)malloc(sizeof(NodeT));
        head->data=code;
        head->next=NULL;
        tail=head;
    }
    else
    {
        elem=(NodeT *)(malloc (sizeof(NodeT)));
        elem->next=head;
        elem->data=code;
        head=elem;
    }
}
void AddLast(int data)
{
    NodeT *elem;

    if (head==NULL)
    {
        head=(NodeT*)malloc(sizeof(NodeT));
        head->data=data;
        head->next=NULL;
    }
    else if (tail==NULL)
    {
        tail=(NodeT*)malloc(sizeof(NodeT));
        tail->data=data;
        head->next=tail;
        tail->next=NULL;
    }
    else
    {
        elem=(NodeT *)malloc(sizeof(NodeT));
        tail->next=elem;
        tail=elem;
        elem->next=NULL;
        elem->data=data;
    }
}

void RemoveFirst(void)
{
    NodeT *elem;
    if (head!=NULL)
    {
        elem=head;
        head=head->next;
        free(elem);
        if (head==NULL)
            tail=NULL;
    }
}

void RemoveLast(void)
{
    NodeT *prev;
    NodeT *curr;

    prev = NULL;
    curr = head;
    if (curr!=NULL)
    {
        while (curr!=tail)
        {
            prev=curr;
            curr=curr->next;
        }
        if (curr==head)
        {
            head=tail=NULL;
        }
        else
        {
            prev->next=NULL;
            tail=prev;
        }
        free(curr);
    }
}

void RemoveNodeX (int data)
{
    NodeT *prev;
    NodeT *curr;

    prev = NULL;
    curr = head;

    while (curr!=NULL)
    {
        if (curr->data==data)
            break;
        prev=curr;
        curr=curr->next;
    }
    if (curr!=NULL)
    {
        if (curr==head)
        {
            head=head->next;
            free(curr);
            if (head==NULL)
                tail=NULL;
        }
        else
        {
            prev->next=curr->next;
            if (curr==tail)
                tail=prev;
            free(curr);
        }
    }
}
void DeleteList(void)
{
    NodeT *elem;

    while (head!=NULL)
    {
        elem=head;
        head=head->next;
        free(elem);
    }
    tail = NULL;
    head = NULL;
}


void printListFront(FILE *f, int n)
{
    NodeT*aux=head;
    int i;

    i=0;
    while ((aux!=NULL)&&(i < n))
    {
        fprintf(f, "%d ", aux->data);
        aux=aux->next;
        i++;
    }
}

void PrintListLast(FILE *f, int n)
{
    NodeT *aux = head;
    int i,j;

    i=0;
    while (aux!=NULL )
    {
        aux=aux->next;
        i++;
    }
    aux=head;
    j=0;
    while ((aux!=NULL)&&(j<(i-n)))
    {
        aux=aux->next;
        j++;
    }
    while (aux!=NULL)
    {
        fprintf(f, "%d ", aux->data);
        aux=aux->next;
    }
}

void printList(FILE *f)
{
    NodeT *aux=head;

    while (aux!=NULL)
    {
        fprintf(f, "%d ", aux->data);
        aux=aux->next;
    }
}

int main()
{
    FILE *fd;
    FILE *f;
    char txts[20];
    int code;
    fd = fopen("input.txt", "r");
    if (fd==NULL)
    {
        perror("Cannot open file!");
        return -200;
    }
    f = fopen("output.txt", "w");
    if (f==NULL)
    {
        perror("Cannot create file!");
        return-100;
    }
    while(fscanf(fd,"%s %d\n", txts, &code) > 0)
    {
        if (strcmp(txts, "AF") == 0)
        {
            addFirst(code);
        }
        else if (strcmp(txts, "AL") == 0)
        {
            AddLast(code);
        }
        else if (strcmp(txts, "DF") == 0)
        {
            RemoveFirst();
        }
        else if (strcmp(txts, "DL") == 0)
        {
            RemoveLast();
        }
        else if (strcmp(txts, "DOOM_THE_LIST") == 0)
        {
            DeleteList();
        }
        else if (strcmp(txts, "DE") == 0)
        {
            RemoveNodeX(code);
        }
        else if (strcmp(txts, "PRINT_ALL") == 0)
        {
            printList(f);
            fprintf(f, " \n");
        }
        else if (strcmp(txts, "PRINT_F") == 0)
        {
            printListFront(f, code);
            fprintf(f, " \n");
        }
        else if (strcmp(txts, "PRINT_L") == 0)
        {
            PrintListLast(f, code);
            fprintf(f, " \n");
        }
    }
    fclose(fd);
    fclose(f);
    return (0);
}
