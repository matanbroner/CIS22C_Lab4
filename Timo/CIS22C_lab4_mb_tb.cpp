// TODO:
// add error checking to:
//   get input for arrays
// add comments
// clean code
//
// done:
// error checking on:
//   all integer menus
//   y/n menu

// CIS22C_lab4_mb_tb.cpp : Defines the entry point for the console application.
//

#include "Menu.h"

const int SORT_MAX_SIZE = 32;

int main()
{	
	try {
		menu(SORT_MAX_SIZE);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (const std::string& ex) {
		std::cout << ex << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error occurred" << std::endl;
	};

    return 0;
}
