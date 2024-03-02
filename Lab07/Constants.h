#include <string>
#pragma once

/*
* constants
*
* Used to keep track of the constants used in the program file
*/
namespace constants {
	const int ARRAY_SIZE = 25;	// The size of the array for the ordered list.
	const int MOVE_LEFT = -1;	// The integer value associated with a left movement.
	const int MOVE_RIGHT = 1;	// The int value associated with a right movement. 	
	const int QUIT_CHOICE = 3;

	const char NEWLINE_CHAR = '\n';				// The newline character
	const char SPACE_CHAR = ' ';				// The space character
	const std::string ONE_STR = "1";			// The string value for the number 1
	const std::string TWO_STR = "2";			// The string value for the number 2
	const std::string THREE_STR = "3";			// The string value for the number 3
	const int ASCII_TO_INT = 48;				// The number to convert ASCII values to integers
}