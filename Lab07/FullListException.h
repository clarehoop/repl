#include <iostream>
#pragma once

/*
* FullListException
*
* An exception class to handle when a list is full
*/
class FullListException : public std::exception {
public:
	const char* FullList() {
		return "Oops! Your list is full. Please remove some items before trying to add to the list again.";
	}
};