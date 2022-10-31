#include <stdio.h>
#include <stdlib.h>

struct LinkedList
{
    int data;
    struct LinkedList *next;
};
struct LinkedList *headd  = NULL;
typedef struct LinkedList *Node;

Node CreateNewNode(int el)
{
    Node newNode = (Node)malloc(sizeof(struct LinkedList));
    newNode->data = el;
    newNode->next= NULL;
    return newNode;
}
void AddTail(int el)
{
    Node temp = CreateNewNode(el);
    if(headd==NULL)
        {
            headd = temp;
            return;
        }
    Node p = headd;
    while( p->next != NULL)
        p = p->next;
    p->next = temp;
}
int Delhead()
{
    if(headd == NULL)
        return 0;
    Node p = headd;
    int a = p->data;
    headd = p->next;
    free(p);
    return a;
}
