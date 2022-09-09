/******************************************************
** Program: Linked_list.hpp
** Author: Parker Choc
** Date: 06/06/2021
** Description: Linked list class
** Input: depends on function. Some requre indexes, some
**      values to be added
** Output: has ability to print itself to the screen
******************************************************/

#ifndef H_Linked_list
#define H_Linked_list

#include <iostream>
#include "Node.hpp"
#include "sorting_&_algorithms.hpp"
using std::cout;

template <class T>
class Linked_list
{
    private:
        unsigned int length;
        Node<T>* head;
    public:
        
        /*********************************************************************  
        ** Functions: Linked_list()
        ** Description: constructs the Linked_list class 
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: constructs a Linked_list class
        *********************************************************************/
        Linked_list()
        {
            this->length = 0;
            this->head = nullptr;
        }
        
        /*********************************************************************  
        ** Functions: clear()
        ** Description: deletes all allocated memory and resets the linked list
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: now empty linked list
        *********************************************************************/
        void clear()
        {
            length = 0;
            Node<T>* a = head;
            Node<T>* b;
            while (a != nullptr)
            {
                b = a->next;
                delete a;
                a = b;
            }
            head = nullptr;
        }

        /*********************************************************************  
        ** Functions: ~Linked_list()
        ** Description: Linked_list destructor
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: destroys linked list
        *********************************************************************/
        ~Linked_list()
        {
            clear();
        }

        /*********************************************************************  
        ** Functions: find()
        ** Description: returns a node pointer to the member of the linked list
        **      in the index position.
        ** Parameters: int index
        ** Pre-Conditions: index value that is inside of the linkde list 
        **      otherwise there will be an error
        ** Post-Conditions: returns a node pointer based on the passed index
        *********************************************************************/
        Node<T>* find(int index)
        {
            Node<T>* temp = head;
            for (int i = 0; i < index; i++)
                temp = temp->next;
            return temp;
        }        
        
        /*********************************************************************  
        ** Functions: get_length()
        ** Description: returns the length of the linked list 
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: returns length
        *********************************************************************/
        int get_length()
        {
            return length;
        }       
        
        /*********************************************************************  
        ** Functions: push_front()
        ** Description: adds a node to the linked list at the beginning 
        ** Parameters: T data
        ** Pre-Conditions: the data that will fill the new node
        ** Post-Conditions: adds a node to the linked list
        *********************************************************************/
        unsigned int push_front(T data)
        {
            Node<T>* temp = new Node<T>(data);
            temp->next = head;
            head = temp;
            length++;
            return length;
        }

        /*********************************************************************  
        ** Functions: push_back()
        ** Description: adds a node to the linked list at the end 
        ** Parameters: T data
        ** Pre-Conditions: the data that will fill the new node
        ** Post-Conditions: adds a node to the linked list
        *********************************************************************/
        unsigned int push_back(T data)
        {
            length++;
            Node<T>* temp = new Node<T>(data);
            if (head == nullptr)
                head = temp;
            else
                find(length - 2)->next = temp;
            return length;
        }
        
        /*********************************************************************  
        ** Functions: insert()
        ** Description: adds a node to the linked list at the passed index
        ** Parameters: T data, unsigned int location
        ** Pre-Conditions: the data that will fill the new node, the location 
        **      that the node should be inserted into the linked list
        ** Post-Conditions: adds a node to the linked list
        *********************************************************************/
        unsigned int insert(T data, unsigned int location)
        {
            if (location == 0)  //inserting at the beginning
                length = push_front(data);
            else
            {
                length++;
                Node<T>* previous = find(location - 1);
                Node<T>* new_node = new Node<T>(data);
                new_node->next = previous->next;
                previous->next = new_node;
            }
            return length;
        }

        /*********************************************************************  
        ** Functions: print()
        ** Description: goes through the linked list and prints the value in
        **      each node
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: prints to the sceen the linked list
        *********************************************************************/
        void print()
        {
            Node<T>* temp = head;
            for (unsigned int i = 0; i < length; i++)
            {
                cout << temp->val << "\n";
                temp = temp->next;
            }
        }

        /*********************************************************************  
        ** Functions: sort_ascending()
        ** Description: sorts the linked list in ascending order 
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: a linked list sorted where the smallest value is
        **      the head and the largest is at the end
        *********************************************************************/
        void sort_ascending()
        {
            if (length > 1) //Don't sort the list if it is too small
                ll_merge_recursive_asc(&head);
        }

        /*********************************************************************  
        ** Functions: sort_decending()
        ** Description: sorts the linked list in decending order 
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: a linked list sorted where the largest value is
        **      the head and the smallest is at the end
        *********************************************************************/
        void sort_decending()
        {
            if (length > 1) //Don't sort if the list is too small
                head = ll_selection_recursive(head, 1);
        }

        /*********************************************************************  
        ** Functions: num_primes()
        ** Description: returns the number of primes in the linked list
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: returns an integer telling how many primes are in
        **      the linked list
        *********************************************************************/
        int num_primes()
        {
            int total = 0;
            Node<T>* temp = head;
            while (temp != nullptr)
            {
                if (is_prime(temp->val))
                    total++;
                temp = temp->next;
            }
            return total;
        }
};
#endif