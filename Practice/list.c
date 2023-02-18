#include <stdlib.h>
#include "linkedlist-v6.h"

/*
 *  Splits the contents of a null-terminated, singly-linked list with
 *  head pointer by cutting every second and third node out into another linked list.
 *  This must be achieved by reassigning/relinking the next attribute
 *  of the list nodes. You may NOT overwrite the data attribute of
 *  existing nodes and you may NOT malloc or free existing nodes.
 *
 *  Note that list2 is a double-pointer type.
 *  Think of this as a struct node* passed by reference (we want to modify
 *  the actual parameter).
 *
 *  Assume that the length of list1 is divisible by 3.
 *
 *  @param list1 - pointer to the first node in the (possibly empty) list which will be split
 *  @param list2 - reference to the actual pointer which will be the front of the list containing
 *                 the removed nodes.
 *                 Will be modified by this procedure
 *  @pre - list1 has length which is divisible by 3.
 *  @return - pointer to the front of the first list.
 */

/*typedef struct node {
    int data;
    struct node* next;
} node;*/



struct node* Split(struct node* list1, struct node** list2) {
  //get length

   struct node *temp = list1;

  int length = 0;
  for(int i =0; list1 != NULL; i++){
    length++;
    list1 = list1 -> next;
  }
    
  //get increment of 3
  for(int j=0; j < (length/3); j++){

        //move 1st element
        list1 = list1 -> next;
       *list2 = list1;
       (*list2)->data = list1 -> data;

       //move 2nd element
        list1 = list1 -> next;
       *list2 = (*list2)->next;
       *list2 = list1;
       (*list2)->data = list1 -> data;

       //update next postition
       *list2 = (*list2)->next;
       list1= list1 -> next;
       temp = temp-> next;
       temp = list1;

 }

    list1= temp;

  return list1, *list2;
}