/*
 File:         linkedlist.c
 Purpose:      Implements the linked list functions whose prototypes
               are declared in the linked_list.h header file
 Author:       Ruth Tau and Tessa Clement
 Student Numbers: 37100518 and 61619698
 CS Accounts:     tyy and tessa42
 Date:            21 Oct 2022
*/

#define _CRT_SECURE_NO_WARNINGS

 /* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/******************************************************************
 PLEASE EDIT THIS FILE

 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/

 /*
  Returns a pointer to a new, empty linked list of struct node.
  PRE:       NULL (no pre-conditions)
  POST:      NULL (no side-effects)
  RETURN:    A pointer to a new, empty linked list of struct node (NULL)
  */
node* create_linked_list()
{
    return NULL;
}

/*
 Returns a dynamically allocated struct node that contains the specified
 struct airplane. Note that the string attributes of the newly created
 node's struct airplane must be specially copied (refer to lab 2).
 The node's next pointer doesn't point to anything
 PARAM:     plane, a struct airplane
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a dynamically allocated struct node a) that contains
            the specified struct airplane, and b) whose next pointer points to NULL
 */
node* create_node(airplane plane)
{
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node != NULL) {
        new_node->plane = plane;
        new_node->next = NULL;
    }

    return new_node;
}

/*
 Prepends a struct node passed as a parameter to the list passed as a
 parameter, and returns a pointer to the result.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     new_node is a pointer to a struct node
 PRE:       new_mode is not null
 POST:      The specified struct node is added to the beginning of the list
            and its next pointer points to the node that used to be first
 RETURN:    A pointer to a linked list which contains all of the nodes
            of the list passed as a parameter, plus a prepended node
 */
node* prepend_node(node* list, node* new_node)
{
    new_node->next = list;
    list = new_node;
    return list;
}

/*
 Deletes the first struct node in the specified list, and returns a pointer to
 the shortened list. Be aware of nested allocations!
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL
 POST:      The list passed as a parameter has one fewer node, and the dynamically
            allocated memory which contained that removed node has been freed
 RETURN:    IF the list is empty
            THEN NULL
            ELSE a pointer to the shortened list
 */
node* delete_node(node* list)
{
    node* delet_list = list;
    if (list){
  
        list = list->next;
        free(delet_list);
    }
    return list;
}

/*
 Returns the number of nodes in the specified linked list of struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    The length of the specified list, an int
 */
int get_length(node* list)
{
    int length = 0;
    while (list != NULL) {
        length++;
        list = list->next;
    }
    return length;
}

/*
 Deletes an entire list.  This function iterates along a list and deallocates the
 memory containing each struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The memory containing all of the nodes in the list has been freed
 RETURN:    an empty list (NULL)
 */
node* delete_list(node* list)
{
    int length = get_length(list);
    node* current = list;

    //case for only one element
    if (length == 1) {
        delete_node(current);
        return NULL;
    }
    else if (list != NULL) {
       

        //delet the middle portion
        for (int i = 1; i < length; i++) {

            current = delete_node(current);
            current = current->next;

        }
        //delet the last node
        current = delete_node(current);
        return current;
    }
    else {
        return list;
    }
}

/*
 Prints the data stored in a node.  For the struct airplane in the node,
 prints the fields on separate lines.  For each field, prints the field name
 and the field value.  For the pointer, prints "Link = NULL\n" if the pointer points
 to null, else prints "Link points to address xxx\n", where xxx is the pointer address
 in hexademical.
 If node_to_print is NULL, prints "The node is empty\n".
 PARAM:     node_to_print is a pointer to a (possibly null) struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about node_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_node(node* node_to_print)
{
    if (node_to_print == NULL) {
        printf("The node is empty\n");
    }
    else {
        printf("Flight number: %d\n", node_to_print->plane.flight_number);
        printf("City origin: %s\n", node_to_print->plane.city_origin);
        printf("City destinatio: n%s\n", node_to_print->plane.city_destination);
        printf("Priority: %d\n", node_to_print->plane.priority);
        printf("Maxium speed (kph): %d\n", node_to_print->plane.maximum_speed_kph);
        printf("Cruising altitude: %d\n", node_to_print->plane.cruising_altitude);
        printf("Plane capacity: %d\n", node_to_print->plane.capacity);
    }

}

/*
 Prints the data stored in all nodes in the specified list to print.
 For each node, prints the data inside the node the same way that it
 is printed by print_node.  If the list is empty, a suitable message
 is printed to standard output.
 PARAM:     node_to_print is a pointer to a (possibly empty) linked list of
            struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about list_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_list(node* list_to_print)
{
    int length = get_length(list_to_print);
    if (length == 0) {
        printf("The node is empty\n");
    }
    else {
        for (int i = 0; i < length; i++) {
            print_node(list_to_print);
            list_to_print = list_to_print->next;
        }
        print_node(list_to_print);
    }
    return;


}

/*
 Reverses a list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The order of the nodes in the list passed as a parameter has been
            reversed
 RETURN:    a list of struct node that is the reverse of the list passed as a
            parameter
 */
node* reverse(node* list)
{
    // function for one list only, no need to list.next
    int length = get_length(list);
    struct node* end, *start, *temp;

    // first write all uniqute cases

    if (length == 0 || length == 1) {
        return list;
    }
    else if (length == 2) {
        end = list; 
        temp = list->next;
        temp->next = end; //start = end

        
        end->next = NULL; //terminate te list as it ends with null
        return temp;

    }
    else if (length == 3) {
        end = list;
        temp = list->next;
        start = temp->next;

        end->next = NULL; //mid is NULL
        temp->next = end; //start = end
        start->next = temp; 

        return start;
    }
    else {

        end = list;
        temp = list->next;
        start = temp->next;

        end->next = NULL;
        temp->next = end; //start = end

        end = temp;   //end = temp
        temp = start;   //temp = start

        //move pointer to next position
        start = start->next;

        // while not reach end, list not null
        while (start->next != NULL) {
            temp->next = end; //start = end
            temp = start;
            end = temp;
            start = start->next;
        }



    // end case           

        temp->next = end;
        start->next = temp;
        return start;
    }

}

/*
 Removes every node from the list which contains an airplane destined for
 the city name passed in the second parameter.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     destination_city is a pointer to a null-terminated array of char
 PRE:       NULL (no pre-conditions)
 POST:      Any struct node in the list which contains an airplane struct
            destined for the destination_city is removed from the list, and
            the memory deallocated
 RETURN:    a list of struct node that does not contain any struct node that
            has an airplane destined for the destination_city
 */
node* remove_from_list(node* list, char* destination_city)
{
    int length = get_length(list);
    airplane temp;

    node* current = list;
    node* prev = list;
    node* start = list;
    node* standing = list;

    if (length == 0) {
        return list;
    }
    else if (length == 1) {
        
        temp = list->plane;
        if (strcmp(temp.city_destination,destination_city) == 0)
            delete_list(list);       
        else return list;
    }
    else { //length case > 1

        temp = list->plane;

        for (int i = 0; i < length; i++) {
            if (i == 1 && (strcmp(temp.city_destination, destination_city) == 0) ){
                start = current->next; //move to next 
            }
            else if(i > 0 && (strcmp(temp.city_destination, destination_city) == 0)) { 
                standing = current->next; // temp store the next pointer as standing
                prev->next = delete_node(current); //delet current
                current = standing; // current is replaced by next value
                temp = current->plane; //update the current char of city in list
            }
            else { // no match and no delet require, just shift to next list
                prev = current;
                current = current->next;
                temp = current->plane;
            }
                
        }
        // check for the last node
        if (strcmp(temp.city_destination, destination_city) == 0) {
            prev->next = NULL;
            delete_node(current);
        }



        return start;
    }
}

/*
 Returns a reference to the nth node (but does not remove it ) in the
 specified list.  If the list is too short, returns NULL.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list
            THEN a pointer to the nth node
            ELSE NULL
 */
node* retrieve_nth(node* list, int ordinality)
{
    int length = get_length(list);
    node* current = list;
    node* prev = list;

    if (ordinality <= length) {
        for (int i =0 ; i < ordinality; i++) {
            prev = current;
            current = current->next;  //shifting to next node
        }
        return prev;
    }
    else {
        return NULL;
    }
}

/*
 Inserts the specified node into the specified list of nodes at the specified
 ordinality.  For example, if ordinality = 1, this is a simple prepend_node
 operation.  If ordinality = 3, then when this function is finished, the third
 node in the list will be the node_to_insert.  If the ordinality = the length
 of the list + 1, then the node_to_insert is appended to the end of the list.
 If the ordinality > 1 + length of the list, the function returns a pointer
 to the unchanged list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 PRE:       node_to_insert is NEVER a null (it is always a correct node pointer)
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list + 1
            THEN a pointer to the list which contains the node_to_insert in the
      correct location
            ELSE a pointer to the unchanged list
 */
node* insert_nth(node* list, node* node_to_insert, int ordinality)
{
    int length = get_length(list);
    node* pos = list;
    node* prev = list;

    if (ordinality == 1) {
       return  prepend_node(list, node_to_insert);
    }
    else if (ordinality == length+1) {
       

        while (pos)
        {
            prev = pos;
            pos = pos->next;
        }

        prev->next = node_to_insert;
        node_to_insert->next = NULL;

        return list;
    }
    else if (ordinality > length + 1) {
        return list;
    }
    else { //case of <=
        pos = retrieve_nth(list, ordinality);
        prev = retrieve_nth(list, ordinality - 1);
        node_to_insert->next = pos;
        prev->next = node_to_insert;
        return list;

    }
}