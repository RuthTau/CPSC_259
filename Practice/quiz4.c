#include <stdlib.h>
#include "quiz4-v4.h"

/*
 *  RECURSIVELY swaps the positions of the first and fourth nodes, and
 *  second and third nodes in each group of four nodes in a linked list.
 *  Effectively, reverses the order of each group of four nodes.
 *  This must be achieved by reassigning/relinking the next attribute
 *  of the list nodes. You may NOT overwrite the data attribute of
 *  existing nodes and you may NOT malloc or free existing nodes.
 *
 *  You may assume that the list length is a multiple of 4.
 *
 *  THIS MUST BE ACHIEVED RECURSIVELY TO EARN FULL CREDIT.
 *  THERE WILL BE A MANUALLY-GRADED COMPONENT WORTH APPROXIMATELY
 *  50% CREDIT FOR THIS PROGRAMMING QUESTION. A RECURSIVE SOLUTION
 *  (CORRECT OR OTHERWISE) WILL AUTOMATICALLY EARN THE MANUAL COMPONENT.
 * 
 *  Example:
 *  before:  A - B - C - D - E - F - G - H - I - J - K - L
 *  after:   D - C - B - A - H - G - F - E - L - K - J - I
 *
 *  @param list - pointer to the first node in a linked list to be rearranged.
 *  @return - pointer to the front of the rearranged list.
 */

struct node *head; // a head pointer 
struct node* Rearrange(struct node* list) {

 int i =0;
 if(list->next == NULL){ //nothing more in the list, base case
    head = list;
    return NULL;
 }
 else {
    struct node *temp = list;
    if ((i % 4) != 0){
     // new is a list stores the rearranged list
    struct node *new = Rearrange( temp->next); //trust that it will reverse recursion 
    //printf("%d", list->data); 
    //make sure that it reverse it

    //reverse pointer address order
    struct node *temp01 = temp->next; // make new pointer
    temp01->next = temp; //reverse pointer backwards to pop
    temp->next = NULL; //clear data of the original que
    i++;
    }
    // new will store all first 4 reverse node
    else{
        i = 0;
        head = list + 4;
    }
 }  
 
    return new;
}