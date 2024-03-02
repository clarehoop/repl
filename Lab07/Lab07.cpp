// Lab07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OrderedList.h"
#include "MiddleOrderedList.h"
#include "NullSpotOrderedList.h"

/*
* make_type_choice()
*
* Checks and stores valid entry for users type choice
*
* Parameters: None
*
* Returns: int of users choice
*/
int make_type_choice() {
    std::string choice{}; // Initialize a variable to hold the user's choice

    // Ask the user to select a number until a valid entry is given
    if (choice != ONE_STR && choice != TWO_STR && choice != THREE_STR) {
        // Present the user with options
        std::cout << "\nEnter the number associated with one of the following choices:" << std::endl;
        std::cout << "Press 1 for User Test" << std::endl;
        std::cout << "Press 2 for Automated Test" << std::endl;
        std::cout << "Press 3 to quit" << std::endl;

        // Get the input from the user
        std::getline(std::cin, choice); // getline is needed so that the getline in the reversing user input
    }

    // Return the result
    return choice[0] - ASCII_TO_INT; // The 0th index of the string is taken because getline requires a string
}
/*
* make_user_choice()
*
* Checks and stores valid entry for users choice to add or remove
*
* Parameters: None
*
* Returns: int of users choice
*/
int make_user_choice() {
    std::string choice{}; // Initialize a variable to hold the user's choice

    // Ask the user to select a number until a valid entry is given
    if (choice != ONE_STR && choice != TWO_STR && choice != THREE_STR) {
        // Present the user with options
        std::cout << "\nEnter the number associated with one of the following choices:" << std::endl;
        std::cout << "Press 1 to add an item to the list and display current state" << std::endl;
        std::cout << "Press 2 to remove an item from the list and display current state" << std::endl;
        std::cout << "Press 3 to quit" << std::endl;

        // Get the input from the user
        std::getline(std::cin, choice); // getline is needed so that the getline in the reversing user input
    }

    // Return the result
    return choice[0] - ASCII_TO_INT; // The 0th index of the string is taken because getline requires a string
}
/*
* UserChoiceAdd()
*
* If a user wants to add, adds to each type of Ordered list.
*
* Parameters: Int pointer of the value to add
*
* Returns: N/A
*/
/*
void UserChoiceAdd(int* valueToAdd, OrderedList<int> o, MiddleOrderedList<int> m, NullSpotOrderedList<int> n){
    o.AddItem(valueToAdd);
	o.printValues();
    m.AddItem(valueToAdd);
    m.printValues();
    n.AddItem(valueToAdd);
	n.printValues();
    
	
}
*/
/*
* userChoiceRemove()
*
* If a user wants to remove, removes a value from each type of Ordered list.
*
* Parameters: Int pointer of the value to remove
*
* Returns: N/A
*/
/*
void userChoiceRemove(int* valueToRemove, OrderedList<int> o, MiddleOrderedList<int> m, NullSpotOrderedList<int> n){
	o.RemoveItem(valueToRemove);
	o.printValues();
	m.RemoveItem(valueToRemove);
	m.printValues();
	n.RemoveItem(valueToRemove);
	n.printValues();
}
*/
/*
* automatedChoice()
*
* Runs the automated adding and subtracting from all instances of different ordered lists.
* Used a random number to add and remove.
*
* Parameters: N/A
*
* Returns: N/A
*/
void automatedChoice(){
    int randNum=0;
    OrderedList<int> o = OrderedList<int>();
    MiddleOrderedList<int> m = MiddleOrderedList<int>();
    NullSpotOrderedList<int> n = NullSpotOrderedList<int>();
    srand(0);
    for(int i =0; i<100;i++){
		randNum = (1 + rand() % 100);
        int* insertNum = new int(randNum);
        if (i%3 == 0 && i%5 == 0 && !o.isFull()){
			o.AddItem(insertNum);
			m.AddItem(insertNum);
			n.AddItem(insertNum);
        }
        else if(i % 3 != 0 && i % 5 != 0 && !o.isEmpty() ){
			o.RemoveItem(insertNum);
			m.RemoveItem(insertNum);
			n.RemoveItem(insertNum);
        }
    }
    std::cout << "------------------The final totals------------------" << std::endl;
    o.printValues();
    m.printValues();
    n.printValues();

}
int main()
{
    OrderedList<int> o = OrderedList<int>();
    MiddleOrderedList<int> m = MiddleOrderedList<int>();
    NullSpotOrderedList<int> n = NullSpotOrderedList<int>();
    int typeChoice = make_type_choice();
    int userChoice{};
    int value{};
    while (typeChoice != QUIT_CHOICE) {
        if (typeChoice == 1) {
            userChoice = make_user_choice();
            while (userChoice != QUIT_CHOICE) {
                if (userChoice == 1) {
                    std::cout << "Enter an integer you want to add to the list." << std::endl;
                    std::cin >> value;
                    int* add = new int(value);
                    //UserChoiceAdd(add,o,m,n);o.AddItem(valueToAdd);
                    o.AddItem(add);
                    o.printValues();
                    m.AddItem(add);
                    m.printValues();
                    n.AddItem(add);
                    n.printValues();
                }
                if (userChoice == 2) {
                    std::cout << "Enter an integer you want to remove from the list." << std::endl;
                    std::cin >> value;
                    int* remove = new int(value);
                    //userChoiceRemove(remove,o,m,n);
                    o.RemoveItem(remove);
                    o.printValues();
                    m.RemoveItem(remove);
                    m.printValues();
                    n.RemoveItem(remove);
                    n.printValues();
                }
                make_user_choice();
            }
        }
        if (typeChoice == 2) {
            automatedChoice();
        }
        make_type_choice();
    }
  

   /*
    NullSpotOrderedList<int> o = NullSpotOrderedList<int>();
    
    int* one = new int(1);
    int* two = new int(2);
    int* three = new int(3);
    int* five = new int(5);
    int* six = new int(6);
    int* ten = new int(10);
    int* eleven = new int(11);
    int* twelve = new int(12);
    int* thirteen = new int(13);
    int* fourteen = new int(14);
    int* fifteen = new int(15);
    int* sixteen = new int(16);



    o.AddItem(five);

    o.AddItem(ten);

    o.AddItem(six);

    o.AddItem(eleven);

    o.AddItem(three);

    o.AddItem(two);

    o.AddItem(one);

    o.AddItem(twelve);

    o.AddItem(fourteen);

    o.AddItem(fifteen);
    o.printValues();


    o.AddItem(sixteen);
    o.printValues();

    o.AddItem(thirteen);
    o.printValues();

    /*std::cout << "--------------time to remove---------------- " << std::endl;
    o.RemoveItem(five);
    o.printValues();

    o.RemoveItem(six);
    o.printValues();

    o.RemoveItem(eleven);
    o.printValues();

    o.makeEmpty();
    o.printValues();
    */

	
    
}


