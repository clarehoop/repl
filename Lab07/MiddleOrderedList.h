#include "Constants.h"
#include "EmptyListException.h"
#include "FullListException.h"
#include "OrderedList.h"
#pragma once

using namespace constants;

template <class T>
class MiddleOrderedList:public OrderedList<T> {
private:
	// Member variables
	int low{};
	int mid{};
	int high{};

public:
	/*
	* AddItem
	*
	* Add an item to the list starting from a middle refrence point. 
	* When the item is added, it is added so it is in order numerically
	* or alphabetically. 
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
				e.FullList();
			}
			return;
		}

		// Update the middle value
		mid = (high + low) / 2; 

		// Right spot
		if (this->values[low] == nullptr) {
			this->values[low] = itemToAdd;

			// Update variables for return
			this->curr_num_items++;
			high = this->curr_num_items;
			low = 0;
			return;
		}
		// middle of list case
		else if (low == mid) {
			if (*this->values[low] > *itemToAdd) {
				low--;
			}
			this->ShiftEntriesAdd(low);
			this->values[low+1] = itemToAdd;

			// Update variables for return
			this->curr_num_items++;
			high = this->curr_num_items;
			low = 0;
			this->moves--;
			return;
		}
		// Greater than case
		else if (*this->values[mid] < *itemToAdd){
			this->comparisons++;
			low = mid + 1; // Update the low value
			AddItem(itemToAdd);
		}
		//Less than case (lower half)
		else if(*this->values[mid] > *itemToAdd){
			this->comparisons++;
			high = mid - 1;
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
	void RemoveItem(T* itemToRemove) override{
		// If the list is empty, throw an exception
		if (this->isEmpty()) {
			try {
				throw EmptyListException();
			}
			catch (EmptyListException e) {
				e.EmptyList();
			}
			return;
		}

		// Look through every item in the array...
		for (int i = 0; i < this->curr_num_items; i++) {
			//Find the removed item in the list.
			if (*this->values[i] == *itemToRemove) {
				// Add one to the comparisons made
				this->comparisons++;

				//Move every item left of the item removed to the left once.
				this->ShiftEntriesRemove(i);

				// Subtract from the tota curr items
				this->curr_num_items--;
				break;
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
	void printValues() override{
		std::cout << ">>>>>>>>>>>>>>>>>>>>>Task 2<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

		// Print values in the array
		for(int i = 0; i < this->curr_num_items; i++) {
			std::cout << *this->values[i] << " ";
		}
		std::cout << "\n" << std::endl;

		// Print moves and comparisons
		std::cout << "Moves: " << this->moves << "\nComparisons: " << this->comparisons << "\n" << std::endl;
	}

};

