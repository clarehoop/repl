#include "Constants.h"
#include "EmptyListException.h"
#include "FullListException.h"
#pragma once

using namespace constants;

template <class T>

class OrderedList {
protected:
	// -------------- Protected member variables -------------- //

	T* values[ARRAY_SIZE];	// An array of values
	int moves{};			// The number of times data was moved
	int comparisons{};		// The number of times data was compared
	int curr_num_items{};	// The current number of items in the list

	/*
	* ShiftEntries
	* 
	* Recursively moves the entries to the right to make room for an addition
	* 
	* Parameters: an integer associated with the location to begin moving entries at
	* 
	* Returns: None
	*/
	virtual void ShiftEntriesAdd(int additionSpot) {
		// If the next spot in the list is a null pointer, add the item to the list and exit
		// This is the only exit condition for the function
		if (values[additionSpot + 1] == nullptr) {
			moves++; // Add to the number of moves made
			values[additionSpot + 1] = values[additionSpot]; // Update the next position in the list
			return; // Exit the function
		}
		// If the data at the spot to add is not null
		if (values[additionSpot + 1] != nullptr) {
			moves++; // Increment the number of moves made
			ShiftEntriesAdd(additionSpot + 1); // Move the spot again
			values[additionSpot + 1 ] = values[additionSpot]; // Update the next position in the list
		}
	}

	/*
	* ShiftEntriesRemove
	* 
	* Move the entries to the left to remove an item
	* 
	* Parameters: an integer associated with the spot to remove
	* 
	* Returns: None
	*/
	void ShiftEntriesRemove(int removeSpot) {
		// Move items to the left until the end location is reached
		for (int i = removeSpot; i < curr_num_items; i++) {
			values[i] = values[i + 1]; // Update the current position to the next location
			moves++;
		}
		values[curr_num_items] = nullptr; // Update the last item to be a null pointer

		// Subtract for the first object since in the for loop it is counted as move 
		moves--;
	}
		
public:
	/*
	* Constructor
	* 
	* Initialize the list to be null pointers
	*/
	OrderedList() {
		// Set every element in the array to be a null pointer
		for(int i = 0; i < ARRAY_SIZE; i++){
			values[i] = nullptr;
		}
	}

	/*
	* AddItem
	* 
	* Add an item to the list in the correct location to make it an ordered list
	* 
	* Parameters: an item to add with the type of the template
	* 
	* Returns: None
	*/
	virtual void AddItem(T* itemToAdd){
		// If the list is full, throw an exception and exit the function
		if (isFull()) {
			try {
				throw FullListException();
			}
			catch (FullListException e) {
				e.FullList();
			}
			return;
		}
		
		// The addition will be successful, so increment the number of items currently in the list
		curr_num_items++;


		// If there are no elements in the array, add it to the beginning
		if (curr_num_items-1 == 0) {
			values[0] = itemToAdd;
			return;
		}

		// If the item to add is less than the item at the beginning, shift the entries and add it to the beginning
		if(*itemToAdd < *values[0]) {
			ShiftEntriesAdd(0);
			values[0] = itemToAdd;
			return;
		}

		// Otherwise, the correct location is somewhere else in the list
		// Loop through all of the items in the list until, 
		for(int i = 0; i < curr_num_items; i++) {
			comparisons++; // Add to the number of comparisons made
			if (values[i + 1] == nullptr) {
				values[i + 1] = itemToAdd;
				break;
			}
			if(*values[i+1] > *itemToAdd) {
				ShiftEntriesAdd(i+1);
				values[i+1] = itemToAdd;
				break;
				
			}
		}
	}
	virtual void RemoveItem(T* itemToRemove){
		// If the list is empty, throw an exception
		if (isEmpty()) {
			try {
				throw EmptyListException();
			}
			catch (EmptyListException e) {
				e.EmptyList();
			}
			return;
		}
		for (int i = 0; i < curr_num_items; i++) {
			
			//Find the removed item in the list.
			if (*values[i] == *itemToRemove){
				comparisons++;
				//Move every item left of the item removed to the left once.
				ShiftEntriesRemove(i);
				curr_num_items--;
				break;
			}
		}
	}

	/*
	* isEmpty
	* 
	* Determine if the list is currently empty
	* 
	* Parameters: None
	* 
	* Returns: a boolean for if the list is currently empty
	*/
	bool isEmpty(){
		return curr_num_items == 0;
	}

	/*
	* isFull
	*
	* Determine if the list is currently full
	*
	* Parameters: None
	*
	* Returns: a boolean for if the list is currently full
	*/
	bool isFull(){
		return curr_num_items == ARRAY_SIZE;
	}

	/*
	* makeEmpty
	*
	* empty the array by setting the current number of items to 0
	*
	* Parameters: None
	*
	* Returns: None
	*/
	void makeEmpty(){
		for (int i = 0; i < ARRAY_SIZE; i++) {
			values[i] = nullptr;
		}
		curr_num_items = 0;
	}

	/*
	* printValues
	*
	* Print the values in the array, moves, and comparions.
	*
	* Parameters: None
	*
	* Returns: None
	*/
	virtual void printValues() {
		std::cout << ">>>>>>>>>>>>>>>>>>>>>Task 1<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

		// Print values in the array
		for(int i = 0; i < curr_num_items; i++) {
			std::cout << *values[i] << " ";
		}
		std::cout << "\n" << std::endl;

		// Print moves and comparisons
		std::cout << "Moves: " << moves << "\nComparisons: " << comparisons << "\n" << std::endl;
	}
};