#include <iostream>
#pragma once

/*
* EmptyListException
*
* An exception class to handle when a list is empty
*/
class EmptyListException : public std::exception {
public:
	const char* EmptyList() {
		return "Oops! Your list is empty. Please add some items before trying to remove from the list again.";
	}
};