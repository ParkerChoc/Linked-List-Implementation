/******************************************************
** Program: Node.hpp
** Author: Parker Choc
** Date: 06/06/2021
** Description: Node class
** Input: none
** Output: none
******************************************************/

#ifndef H_Node
#define H_Node

template <class T>
class Node
{
    public: 
        T val;
        Node* next;
        
        /*********************************************************************  
        ** Functions: Node()
        ** Description: constructs the Node class 
        ** Parameters: none
        ** Pre-Conditions: none
        ** Post-Conditions: constructs a Node class
        *********************************************************************/
        Node()  
        {
            this->val = 0;  
            this->next = nullptr;
        }
        
        /*********************************************************************  
        ** Functions: Node()
        ** Description: constructs the Node class 
        ** Parameters: const T &val
        ** Pre-Conditions: the value the node has which is of class T
        ** Post-Conditions: constructs a Node class with given value
        *********************************************************************/
        Node(const T &val)
        {
            this->val = val;
            this->next = nullptr;
        }
};

#endif