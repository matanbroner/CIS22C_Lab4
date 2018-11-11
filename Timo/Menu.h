#ifndef Menu_h
#define Menu_h

#include "Array.h"
#include "Sort.h"
#include <iostream>
#include <fstream>
#include <string>

void menu(const int);

std::ostream& operator<<(std::ostream&, std::string&);
std::ostream& operator<<(std::ostream&, const std::string&);

template<typename T>
void performSorts(Array<T>& arr, int size, std::ofstream& output) {

	Array<T> quick(size);
	Array<T> merge(size);

	for (int i = 0; i < size; i++) {
		//insertion[i] = a[i];
		quick[i] = arr[i];
		merge[i] = arr[i];
	}

	system("cls||clear");
	output << "Array before sort:" << std::endl << arr;

	std::cout << "Performing all sorts on array:" << std::endl << arr << std::endl;

	output << "Insertion sort:" << std::endl;
	std::cout << "Insertion sort:" << std::endl;
	insertionSort(arr, size, output);
	output << "Array after insertion sort:" << std::endl << arr;
	std::cout << "Array after insertion sort:" << std::endl << arr;
	std::cout << std::endl;

	output << "Quick sort:" << std::endl;
	std::cout << "Quick sort:" << std::endl;
	quickSort(quick, 0, size - 1, output);
	output << "Array after quick sort:" << std::endl << quick;
	std::cout << "Array after quick sort:" << std::endl << quick;
	std::cout << std::endl;

	output << "Merge sort:" << std::endl;
	std::cout << "Merge sort:" << std::endl;
	mergeSort(merge, 0, size - 1, output);
	output << "Array after merge sort:" << std::endl << merge;
	std::cout << "Array after merge sort:" << std::endl << merge;
	std::cout << std::endl;
};

std::ostream& operator<<(std::ostream& output, std::string& msg)
{
	output << msg.c_str();

	return output;
}

std::ostream& operator<<(std::ostream& output, const std::string& msg)
{
	output << msg.c_str();

	return output;
}

void menu(const int SORT_MAX_SIZE) {
	std::ofstream output;
	std::string filename = "CIS22C_lab4_mb_tb_output.txt";
	output.open(filename, std::ofstream::out | std::ofstream::app);

	if (!output.is_open()) {
		std::cout << "Error creating file \"" << filename << "\" for writing" << std::endl;
	}
	else {
		output << "CIS22C Lab4: Sorting int, double, char, or string arrays in descending order with insertion, quick, and merge sorts." << std::endl;
		output << "Matan Broner and Timo Bitterli" << std::endl;

		output << std::endl;
		output << "-----------------------" << std::endl;
		output << "start of program output" << std::endl;
		output << "-----------------------" << std::endl;
		output << std::endl;

		bool loop = true;  // use instead of input for easier readability of code
		int input = 0;
		int size = 0;
		Array<int> intarr;
		Array<double> doublearr;
		Array<char> chararr;
		Array<std::string> stringarr;

		bool error = false;

		do {
			size = 0;

			do {
				std::cout << "Warning: error checking is WIP." << std::endl;
				std::cout << "Please enter type of data:" << std::endl;
				std::cout << "[1]: int" << std::endl;
				std::cout << "[2]: double" << std::endl;
				std::cout << "[3]: char" << std::endl;
				std::cout << "[4]: string" << std::endl;
				std::cout << "[0]: exit program" << std::endl;

				try {
					std::cin >> input;
					if (std::cin.fail()) {	// catch nonint
						std::cin.clear();	// clear error flag
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
						error = true;	// loop
						throw std::exception("Input is invalid. Please try again with an integer value.\n");
					}
					else if (input > 4 || input < 0) {
						error = true;
						throw std::exception("Input out of range. Please enter an integer on the menu.\n");
					}
					else {
						error = false;
					}
				}
				catch (const std::exception& ex) {
					system("cls||clear");
					std::cout << ex.what() << std::endl;
				}
				catch (...) {
					system("cls||clear");
					std::cout << "Unknown error occurred" << std::endl;
				};
			} while (error == true);

			if (input > 0 && input < 5) {
				do {
					std::cout << "Please enter number of data inputs (max " << SORT_MAX_SIZE << "):" << std::endl;
					try {
						std::cin >> size;
						if (std::cin.fail()) {	// catch nonint
							std::cin.clear();	// clear error flag
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
							error = true;	// loop
							throw std::exception("Input is invalid. Please try again with an integer value.\n");
						}
						else if (size > SORT_MAX_SIZE || size < 2) {
							error = true;
							throw std::exception("Invalid size. Please enter a value between [2,32]\n");
						}
						else {
							error = false;
						}
					}
					catch (const std::exception& ex) {
						system("cls||clear");
						std::cout << ex.what() << std::endl;
					}
					catch (...) {
						system("cls||clear");
						std::cout << "Unknown error occurred" << std::endl;
					};
				} while (error == true);

				std::cout << "Please enter the inputs one at a time delimited with returns:" << std::endl;
			}


			//  for type specified, get array elements, then call sorts
			//  if loop is repeated, delete old array
			if (input == 1) {
				if (intarr.getSize() != 0)
					intarr.deleteArray();
				intarr.setSize(size);
				int getinput = 0;
				for (int i = 0; i < size; i++) {
					std::cin >> getinput;
					intarr[i] = getinput;
					getinput = 0;
				}
				output << "Performing sorts on int array:" << std::endl;
				performSorts(intarr, size, output);
			}
			else if (input == 2) {
				if (doublearr.getSize() != 0)
					doublearr.deleteArray();
				doublearr.setSize(size);
				double getinput = 0;
				for (int i = 0; i < size; i++) {
					std::cin >> getinput;
					doublearr[i] = getinput;
					getinput = 0;
				}
				output << "Performing sorts on double array:" << std::endl;
				performSorts(doublearr, size, output);
			}
			else if (input == 3) {
				if (chararr.getSize() != 0)
					chararr.deleteArray();
				chararr.setSize(size);
				char getinput = ' ';
				for (int i = 0; i < size; i++) {
					std::cin >> getinput;
					chararr[i] = getinput;
					getinput = ' ';
				}
				output << "Performing sorts on char array:" << std::endl;
				performSorts(chararr, size, output);
			}
			else if (input == 4) {
				if (stringarr.getSize() != 0)
					stringarr.deleteArray();
				stringarr.setSize(size);
				std::string getinput = "";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				for (int i = 0; i < size; i++) {
					std::getline(std::cin, getinput);
					stringarr[i] = getinput;
					getinput = "";
				}
				output << "Performing sorts on string array:" << std::endl;
				performSorts(stringarr, size, output);
			}
			else if (input == 0) {
				loop = false;
			}

			if (input != 0) {
				char prompt = ' ';
				do {
					std::cout << "Would you like to create another array? (y\\n)" << std::endl;

					try {
						std::cin >> prompt;
						if (std::cin.fail()) {	// catch nonint
							std::cin.clear();	// clear error flag
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
							throw std::exception("Input is invalid. Please ente y or n\n");
							error = true;
						}
						else {
							prompt = tolower(prompt);

							if (prompt == 'y' || prompt == 'n') {
								error = false;
							}
							else {
								error = true;
								throw std::exception("Input is invalid. Please enter y or n\n");
							}
						}
					}
					catch (const std::exception& ex) {
						system("cls||clear");
						std::cout << ex.what() << std::endl;
					}
					catch (...) {
						system("cls||clear");
						std::cout << "Unknown error occurred" << std::endl;
					};
				} while (error == true);
				if (prompt == 'n' || prompt == 'N') {
					loop = false;
				}
				else {
					system("cls||clear");
					output << std::endl << "User called for another sort" << std::endl;
				}
			}
		} while (loop);

		output << std::endl;
		output << "---------------------" << std::endl;
		output << "end of program output" << std::endl;
		output << "---------------------" << std::endl << std::endl;
		output.close();
	}
}



#endif
