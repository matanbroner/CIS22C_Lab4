/*
 === Lab 4: Sort an Array 3 Ways ===
 This lab utilizes the Array ADT and has the user provide a type of data value, and inout for each array index.
 The program sorts the array 3 ways recursively and logs the sorting steps both to the console and a provided output file path.
 Input validation is implemented.
 
 Partners: Matan Broner and Timo Bitterli
 Matan rating for Timo: 0
 */

#include "ArraySorter.h"
#include "ArrayManager.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>


/*
 This method allows the user to handle cin.fail() cases repeatedly from outside their driver program. It takes a variable to be read into by reference and has the user provide input until valid.
 Pre: template type variable for input
 Post: variable filled
 Return: variable value
 */
template <typename T>
T invalidInputHandler(T& inputNeeded);

using namespace std;
int main(int argc, const char * argv[]) {
    
    string fileAddress;
    int menuChoice = 0, arraySize = 0;
    string userInput = "";
    
    cout << "=== Lab 4 -- Array Sorter ===" << endl << endl;
    
    cout << "File address for log: ";
    getline(cin, fileAddress);
    if (cin.fail())
        invalidInputHandler<string>(fileAddress);
    
    do
    {
        cout << "\nType of array to create and sort: " << endl;
        cout << "[1] -- int\n[2] -- double\n[3] -- char\n[4] -- string" << endl;
        cout << "--> ";
        cin >> menuChoice;
        while (cin.fail() || (menuChoice < 1 && menuChoice > 4))
            invalidInputHandler<int>(menuChoice);
        cin.ignore(); // clear newline
        cout << "\nSize of array to be created (Note: max size is 32) --> ";
        cin >> arraySize;
        if (cin.fail())
            invalidInputHandler<int>(arraySize);
        cin.ignore(); // clear newline
    
        switch(menuChoice) // determine the type of array to be created
        {
            case 1: ArrayManager<int>(arraySize, fileAddress); break;
            case 2: ArrayManager<double>(arraySize, fileAddress); break;
            case 3: ArrayManager<char>(arraySize, fileAddress); break;
            case 4: ArrayManager<string>(arraySize, fileAddress); break;
        }
    
        cout << "You can find a log of your sorts in the file you provided... " << endl;
    
        cout << "Continue to a new array?...(Y/N)\n--> ";
        cin >> userInput;
        while (userInput != "Y" && userInput != "N")
        {
            cout << "invalid... --> ";
            cin >> userInput;
        }
        
        system("clear");
        
        if (userInput == "N")
            break;
        cin.ignore();
    }
    while (true);
    
    cout << "Goodbye!" << endl;
    
    
    
    return 0;
}

template <typename T>
T invalidInputHandler(T& inputNeeded)
{
    do
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes illegal value
        cout << "invalid input... --> ";
        cin >> inputNeeded;
    }
    while (cin.fail());
    return inputNeeded;
}
