/******************************************************
** Program: driver.cpp
** Author: Parker Choc
** Date: 06/06/2021
** Description: driver program for assignment 5. Calls
**      functions from the linked_list.hpp file based
**      on user input.
** Input: charactors entered by the user on what they
**      wish to do with the linked list, ocasionally
**      numbers to enter as well if they choose   
** Output: linked list functions called based on what
**      the user wishes to do with their linked list
******************************************************/
#include <iostream>
#include "Linked_list.hpp"

using namespace std;

/*********************************************************************  
** Functions: add()
** Description: calls the three linked list functions that add to the
**      linked list after getting a value to add (and maybe an index) 
** Parameters: Linked_list<T> &l, char input
** Pre-Conditions: the linked list, and the user input (determines how
**      they selected to add a value)
** Post-Conditions: a linked list modified by having a value added
*********************************************************************/
template <class T>
void add(Linked_list<T> &l, char input)
{
    int length;
    T value;
    cout << "Enter value: ";
    cin >> value;
    switch(input)
    {
        case 'f':
            length = l.push_front(value);
            break;
        case 'b':
            length = l.push_back(value);
            break;
        case 'i':
            cout << "What index do you want to insert?\n";
            cout << "Acceptable indexes: (0-" << l.get_length() << ")\n";
            unsigned int answer;
            do
            {
                cout << "index: ";
                cin >> answer;
                if ((answer < 0) || (answer > l.get_length()))
                    cout << "Out of range\n";
            } while ((answer < 0) || (answer > l.get_length()));
            length = l.insert(value, answer);
            break;
    }
    cout << "New length: " << length << endl;
}

/*********************************************************************  
** Functions: user_input()
** Description: displays the options the user has and returns a char
**      of which the user inputs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: a char that is user input, after a menu is printed
**      to the screen
*********************************************************************/
char user_input()
{
    char answer;
    cout << "\nHere are your options\n";
    cout << "(l) - get length of linked list\n";
    cout << "(p) - print linked list\n";
    cout << "(c) - clear linked list\n";
    cout << "(f) - push front linked list\n";
    cout << "(b) - push back linked list\n";
    cout << "(i) - insert into linked list\n";
    cout << "(a) - sort: ascending order (merge)\n";
    cout << "(d) - sort: decending order (selection)\n";
    cout << "(z) - count all primes in linked list\n";
    cout << "(q) - quit the program\n";
    cout << "Option: ";
    cin >> answer;
    cout << endl;
    return answer;
}

/*********************************************************************  
** Functions: do_stuff()
** Description: calls a function to execute based on the user input
** Parameters: Linked_list<T> &l
** Pre-Conditions: the linked list that will be used in the functions
** Post-Conditions: whatever the user selects to do with the linked list
*********************************************************************/
template <class T>
void do_stuff(Linked_list<T> &l)
{
    do
    {
        char input = user_input();
        if ((input == 'f') || (input == 'b') || (input == 'i'))
            add(l, input);
        switch(input)
        {
            case 'l' :
                cout << "Length: " << l.get_length() << endl;
                break;
            case 'p' :
                l.print();
                break;
            case 'c' :
                cout << "Linked list cleared\n";
                l.clear();
                break;
            case 'a' :
                cout << "Sorted in acending order\n";
                l.sort_ascending();
                break;
            case 'd' :
                cout << "Sorted in decending order\n";
                l.sort_decending();
                break;
            case 'z' :                
                cout << "Total prime numbers: " << l.num_primes() << endl;
                break;
            case 'q' :
                return; //exits program
            default :
                if ((input != 'f') && (input != 'b') && (input != 'i'))
                    cout << "invalid input\n";
                break;
        }
    } while (true);   //loop forever
}

/*********************************************************************  
** Functions: main()
** Description: creates a linked list of a type that the user selects, 
**      then calls another function to get user input and interact
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: nothing
*********************************************************************/
int main()
{
    bool input;
    cout << "Using int or unisgned int?\n";
    cout << "(0 - int) (1 - unsigned int)\n";
    cin >> input;

    if (input)
    {
        Linked_list<unsigned int> l;
        do_stuff(l);
    }
    else
    {
        Linked_list<int> l;
        do_stuff(l);
    }
    return 0;
}