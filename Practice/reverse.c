#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
};

struct Node *head; //global variable pointer

void Reverse(struct Node *list){
    if (list->next == NULL){
        head = list; //head pointer will point at current address
        return; //exit function when reached NULL
    }
 
    Reverse (list->next); //trust that it will reverse recursion 
    //printf("%d", list->data); 
    //make sure that it reverse it

    //reverse pointer address order
    struct Node *temp = list->next; // make new pointer
    temp->next = list; //reverse pointer backwards to pop
    list->next = NULL; //clear data of the original que
    
}

/* in a linked list , a NODE will store data and address of the next node*/
/* Address for NULL is 0 */
/* set up  HEAD, a pointer, points at the first address */

void ReversePrint (struct Node *list){
    if (list == NULL){
        return;
    }
    //else
    ReversePrint (list->next); //trust that it initially access the first node, it'll go to the next node after that
    printf("%d", list->data);
}