/******************************************************
** Program: sorting_&_algorithms.hpp
** Author: Parker Choc
** Date: 06/06/2021
** Description: functions for sorting linked lists
** Input: depends on the funciton. Only 3 are really
**      meant to be called and those functinos are 
**      is_prime(), ll_selection_recursive(), and 
**      ll_merge_recursive_asc().
** Output: depends on function. 
******************************************************/

#ifndef H_sorting
#define H_sorting
#include "Node.hpp"

/*********************************************************************  
** Functions: is_prime()
** Description: returns whether the passed number is prime or not 
** Parameters: T number
** Pre-Conditions: the number I am checking
** Post-Conditions: true or false (whether its prime)
*********************************************************************/
template <class T>
bool is_prime(T number)
{
    //algorithm inspired by: 
    //https://stackoverflow.com/questions/4424374/determining-if-a-number-is-prime

    //gotta deal with the smaller numbers
    if (number <= 1)    //weed out negative numbers too (they cannot be prime)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0) //it is even
        return false;
    //I can do fewer comparisons if I put i * i in the for loop
    //same goes with incrementing by 2, because a prime num will never be even
    for(int i = 3; (i * i) <= number; i += 2)
        if(number % i == 0) //can't be evenly divisible by any number
            return false;
    return true;
}

/*********************************************************************  
** Functions: swap()
** Description: swaps two nodes 
** Parameters: Node<T>** a_ptr_ref, Node<T>* a, Node<T>* b_ptr, Node<T>* b
** Pre-Conditions: a pointer to a pointer to the node before a, a pointer
**      to the node a, a pointer to the node before b, and a pointer
**      to the node b
** Post-Conditions: the two nodes are now swapped. Everything that
**      a pointed to and that pointed to a has been exchanged with that
**      of node b.
*********************************************************************/
template <class T>
void swap(Node<T>** a_ptr_ref, Node<T>* a, Node<T>* b_ptr, Node<T>* b)
{
    /*
    **  The reason that the first passed value is a double pointer is 
    **  becuase it might be the head of the linked list, and by definition
    **  its the first so nothing points to it. Not yet at least unitil it
    **  becomes pointed to after swapping
    **
    **  pointer to pointer to node before a
    **  pointer to node a
    **  pointer to node before b
    **  pointer to node b
    */
    
    //Swap before node pointers
    *a_ptr_ref = b;
    b_ptr->next = a;
 
    //Swap next Node pointers
    Node<T>* temp = b->next;
    b->next = a->next;
    a->next = temp;
    
    //inspiration: 
    //https://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/
}

/*********************************************************************  
** Functions: ll_selection_recursive()
** Description: sorts the linked list in either ascending or decending
**      order
** Parameters: Node<T>* head, bool ascending
** Pre-Conditions: the head pointer of the linked list, and a bool
**      that determines whether I am sorting ascending or decending
** Post-Conditions: a sorted linked list in ascending or decending 
**      order. Calls itself recursively to do this.
*********************************************************************/
template <class T>
Node<T>* ll_selection_recursive(Node<T>* head, bool ascending)
{
    //ascending variable tells if I am sorting decending or ascending
    if (head == nullptr)    //end of the list
        return head;    //Base case
    /*
    **  result: Node pointer that will store the min or max val
    **  b_result: a pointer to the node before the min/max node
    **  location: where I am at now in the linked list
    */
    Node<T>* result = head;
    Node<T>* b_result = nullptr;
    Node<T>* location = head;
    if (ascending)
        while (location->next != nullptr)
        {
            if (result->val < location->next->val)
            {
                result = location->next;   //reassign max val
                b_result = location;       //point to the node before max
            }
            location = location->next;  //go to the next element in the list
        }
    else
        while (location->next != nullptr)
        {
            if (result->val > location->next->val)
            {
                result = location->next;   //reassign max val
                b_result = location;       //point to the node before max
            }
            location = location->next;  //go to the next element in the list
        }
    /*
    **  I want the head to be the maximum/minimum so that when I call this fucntion
    **  again, I call it with a linked list that is after the head. Everything
    **  beyond the head where I build up sorted vals in the beginning of the
    **  linked list
    */
    if (result != head)
        swap(&head, head, b_result, result);

    head->next = ll_selection_recursive(head->next, ascending);
    return head;
    //Inspiration:
    //https://www.geeksforgeeks.org/recursive-selection-sort-singly-linked-list-swapping-node-links/
}

/*
**  Selection sort above
**  Merge sort below
*/

/*********************************************************************  
** Functions: split()
** Description: splits two linked lists into two equal pieces. (1 away
**      from each other if the linked list has an odd num of values)
** Parameters: Node<T>** first, Node<T>** second, Node<T>* head
** Pre-Conditions: the first and second node pointers to pointers.
**      These are only here to be modified by this function. The
**      head of the linked list is also passed so I know where to
**      start.
** Post-Conditions: a linked list that is split into two pieces, that
**      the parameters first and second now point to their respective
**      pieces of the linked list.
*********************************************************************/
template <class T>
void split(Node<T>** first, Node<T>** second, Node<T>* head)
{
    /*
    **  This will modify first and second to be node pointers to the first 
    **  part and second part of a list that is split in half
    */
    Node<T>* location = head;   //where I am at now
    int midpoint = 0;
    while (location != nullptr) //finding the length so I can get midpoint
    {
        midpoint++;
        location = location->next;
    }
    Node<T>* middle = head;
    for (int i = 0; i < (midpoint / 2) - 1; i++)    //find middle of linked list
        middle = middle->next;
    *second = middle->next; //second half starts after midpoint
    *first = head; //first half of the list is just the head
    middle->next = nullptr;
}

/*********************************************************************  
** Functions: combine()
** Description: combines the two passed linked lists into one linked
**      list that is returned. Also sorts as it combines.
** Parameters: Node<T>* a, Node<T>* b
** Pre-Conditions: two linked lists of any size to be combined
** Post-Conditions: a combined linked list made of a and b that
**      also happens to be sorted in ascending order
*********************************************************************/
template <class T>
Node<T>* combine(Node<T>* a, Node<T>* b)
{
    //Base case: either a or b is empty (means other one is full)
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;
    /*
    **  Recursively combine the a and b linked lists until 
    **  I have only one (which is returned)
    **  Note: this function only works with lists that are already sorted
    */
    Node<T>* sorted_list;
    if (a->val < b->val)
    {
        sorted_list = a;    //a is the next element because its less than b
        sorted_list->next = combine(a->next, b);
    }
    else 
    {
        sorted_list = b;    //b is the next because it is less than a
        sorted_list->next = combine(a, b->next);
    }
    return sorted_list;
}

/*********************************************************************  
** Functions: ll_merge_recursive_asc()
** Description: recursively sorts a linked list that is passed in the
**      form of a pointer to a node pointer which is the head of the 
**      linked list.
** Parameters: Node<T>** head_ptr
** Pre-Conditions: a reference to the head pointer of the linked list
** Post-Conditions: this function calls itself several times, but what
**      it returns is ultimately nothing because its void. What it does
**      though is modify the passed pointer pointer by soring the list
**      after it in ascending order.
*********************************************************************/
template <class T>
void ll_merge_recursive_asc(Node<T>** head_ptr) //breaks with lists of 0
{
    /*
    **  Steps:
    **  1) split the list into pieces until the list is completely
    **      divided into nodes each on thier own
    **  2) combine/sort each of the lists into a larger list until I only
    **      have one list left which is my sorted list
    ** 
    **  both split() and combine() functions work on any size of 
    **  linked list. This is what allows this function to be so
    **  simple.
    */

    Node<T>* head = *head_ptr;
    Node<T>* a;
    Node<T>* b;

    //Base case: a sublist (or list) is of length 1
    if (head->next == nullptr)
    {
        return;
    }

    //a is the head of one half sublist and b the second half
    split(&a, &b, head);    //pass by reference so that the data can be modified
 
    ll_merge_recursive_asc(&a); //pass by reference so that the data can be modified
    ll_merge_recursive_asc(&b); //pass by reference so that the data can be modified

    /*
    **  keep splitting up a and b until however many sublists there are
    **  each have a length of 1
    */

    //combine both sublists into one sorted sublist
    *head_ptr = combine(a, b);  //this also sorts

    //Some inspiration:
    //https://www.geeksforgeeks.org/merge-sort-for-linked-list/
}

#endif