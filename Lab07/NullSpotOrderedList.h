#include "Constants.h"
#include "EmptyListException.h"
#include "FullListException.h"
#include "OrderedList.h"
#pragma once

using namespace constants;

template <class T>
class NullSpotOrderedList :public OrderedList<T> {
private:
	// -------------- Private member variables -------------- //
	int low{};			// The index lowest potential spot to add an item, used for recursive ShiftEntriesAdd()
	int lastEntry{};	// The index of the last entry in the list

	// -------------- Private member functions -------------- //
	/*
	* findLastEntry
	*
	* Find the index of the last entry in the list
	*
	* Parameters: None
	*
	* Returns: the index of the last non-null value in the list
	*/
	int findLastEntry() {
		// Look at every itme in the array starting at the last and moving back...
		for (int i = ARRAY_SIZE - 1; i > 0; i--) {

			// If the current item is not a nullptr, add to comparisons and return the index
			if (this->values[i] != nullptr) { 
				this->comparisons++;
				return i;
			}
		}
	}

	/*
	* ShiftEntriesAdd
	*
	* Recursively moves the entries to make room for an addition
	*
	* Parameters: an integer associated with the location to begin moving entries at
	*
	* Returns: None
	*/
	void ShiftEntriesAdd(int additionSpot) override {
	    // If the addition spot is the last spot in the array, use this special case
		if (additionSpot >= ARRAY_SIZE) {

			// Find the last null value in the array and shift everything down one spot based off of its position
			ShiftEntriesFromEnd();
			
			return; // Exit the function
		}
		// If the next spot in the list is a null pointer, add the item to the list and exit
		if (this->values[additionSpot] == nullptr) {
			return; // Exit the function											
		}
		// If the data at the spot to add is not null
		if (this->values[additionSpot] != nullptr) {
			this->moves++; // Increment the number of moves made

			ShiftEntriesAdd(additionSpot + 1); // Move the spot again

			/* 
			* Weird issue here where the moves and c omaprisonwould get set to a garbage number after this assignment. 
			* This temp assignment is a fix for the problem. Potentialy will look into it later. 
			*/
			int tempMoves = this->moves;
			int tempCompares = this->comparisons;
			this->values[additionSpot + 1] = this->values[additionSpot]; // Update the next position in the list
			this->moves = tempMoves;
			this->comparisons = tempCompares;
		}
	}

public:
	/*
	* AddItem
	*
	* Add an item to the list starting from a middle refrence point.
	* When the item is added, it is added so it is in ascending order 
	* numerically or alphabetically.
	*
	* Parameters: Pointer to the item to add.
	*
	* Returns: None
	*/
	void AddItem(T* itemToAdd) override {
		// If the list is full, throw an exception
		if (this->isFull()) {
			try {
				throw FullListException();
			}
			catch (FullListException e) {
				std::cout << e.FullList() << std::endl;
			}
			return;
		}

		// Add to empty list condition
		if (this->curr_num_items == 0) {
			this->values[0] = itemToAdd; // Add the value to the first open location in the list

			// Update values for next call
			low = 0; // Set the low to the first index
			lastEntry = (ARRAY_SIZE + low)/2; // Update the last entry to be the next place to potentially add a value
			this->curr_num_items++; // Increment the current number of values in the list

			return; // Exit the function
		}

		// Condition if the value to add is smaller than the value in index 0.
		if(*itemToAdd < *this->values[0]){
			// Shift all entries at starting at 0
			this->ShiftEntriesAdd(0);

			// Add it to the array along with the other values to keep track of array info
			this->comparisons++;
			this->values[0] = itemToAdd;
			this->curr_num_items++;

			return; // Exit the function
		}

		// Base case check for nullptr or squish
		if (this->values[lastEntry] == nullptr || (lastEntry - low) == 1 || (lastEntry - low) == 0) {
			// Shift any potential entries out of this spot ant add the item
			ShiftEntriesAdd(lastEntry);
			this->values[lastEntry] = itemToAdd;

			// Set values for next call
			lastEntry = findLastEntry();
			low = 0;
			this->curr_num_items++;

			return; // Exit the function
		}

		// Case for lower than last entry
		if (*this->values[lastEntry] > *itemToAdd) {
			// Update tracking values 
			this->comparisons++;
			lastEntry = (lastEntry + low) / 2;

			// Call the function with the update values
			AddItem(itemToAdd);
		}

		// Case for higher than last entry
		if (*this->values[lastEntry] < *itemToAdd) {
			// Update the tracking values
			this->comparisons++;
			low = lastEntry;
			lastEntry = (ARRAY_SIZE + low) / 2;

			// Call the function again with the update values
			AddItem(itemToAdd);
		}
	}

	/*
	* RemoveItem
	*
	* Removes the desired item and shifts the array back together.
	*
	* Parameters: Pointer to the item to remove.
	*
	* Returns: None
	*/
	void RemoveItem(T* itemToRemove) override {
		// If the list is empty, throw an exception
		if (this->isEmpty()) {
			try {
				throw EmptyListException();
			}
			catch (EmptyListException e) {
				std::cout << e.EmptyList() << std::endl;
			}
			return;
		}

		// Look through every item in the array...
		for (int i = 0; i < ARRAY_SIZE; i++) {
			// If the value is a null pointer, skip the comparisons
			if (this->values[i] == nullptr) {
				continue;
			}

			// Add one to the comparisons made										
			this->comparisons++;

			// If the value at the current index is the one to remove, remove it
			if (*this->values[i] == *itemToRemove) {
				//Set item removed to null and find last entry
				this->values[i] = nullptr;
				lastEntry = findLastEntry();

				// Subtract from the total curr items
				this->curr_num_items--;
				return; // Exit the function
			}
		}
	}
	/*
	* ShiftEntriesFromEnd
	*
	* Shifts the array to allow an entry to be added in the last spot
	*
	* Parameters: 
	*
	* Returns: None
	*/
	void ShiftEntriesFromEnd() {
		// If the list is empty, throw an exception
		if (this->isEmpty()) {
			try {
				throw EmptyListException();
			}
			catch (EmptyListException e) {
				std::cout << e.EmptyList() << std::endl;
			}
			return;
		}

		// Look through every item in the array starting at the end
		for (int i = ARRAY_SIZE-1; i >= 0; i--) {
			// If the value is a nullptr, shift all items that we previously looked at down one spot and exit 
			if (this->values[i] == nullptr) {
				for (int j = i; j < ARRAY_SIZE-1; j++) {
					// Update moves and move values
					this->moves++;
					this->values[j] = this->values[j+1];
				}
				return; // Exit the funciton
			}
		} 
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
	void printValues() override {
		std::cout << ">>>>>>>>>>>>>>>>>>>>>Task 3<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

		// Print the array
		for (int i = 0; i < ARRAY_SIZE; i++) {
			// If the value is a null pointer, print a blank spot
			if (this->values[i] == nullptr) {
				std::cout << " _ ";
			}
			// Else, print the value that is stored in that pointer
			else {
				std::cout << *this->values[i] << " ";
			}
		}
		std::cout << "\n" << std::endl;

		// Print moves and comparisons
		std::cout << "Moves: " << this->moves << "\nComparisons: " << this->comparisons << std::endl;
	}
};
