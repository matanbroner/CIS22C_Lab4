
/*
 ArrayManager class
 This class is responsible for creating an array of user given size and type, opening an output file stream, sorting the array, and providing the output file to the sorting class for record keeping of all sorts that occur.
 */

#ifndef ArrayManager_h
#define ArrayManager_h

#include "ArraySorter.h"
#include <ctime>

template <typename T>
class ArrayManager
{
private:
    const int SORT_MAX_SIZE = 32; // max size an array can take for sorting to operate
    std::ofstream outputFile; // the location of the output file
    
    /*
     This method takes an Array object instance and loops over each index for user to input a value into it
     Pre: Array
     Post: Array filled with new values
     Return: true if filling Array was succesful
     */
    bool readIntoArray(Array<T>&);
    
    /*
     This method calls a number of sorting functions in the ArraySorter class on the given Array object instance being managed by the class. It appends titles to the output file before each sort and feeds both the Array and output file to the methods for sorting.
     Pre: Array
     Post: outputFile is appended to
     Return: none
     */
    void sortAndExport(Array<T>&);
    
    /*
     This method takes a string and both writes it to the console and to the given output file.
     Pre: string
     Post: string is appended to output file
     Return: none
     */
    static void printUI(std::ofstream&, std::string);
public:
    
    // Constructor tajes a size for the Array and a string file address for the output file
    ArrayManager(int, std::string);
    
    // Destructor closes the output file stream
    ~ArrayManager();
};

template <typename T>
ArrayManager<T>::ArrayManager(int size, std::string fileAddress)
{
    this->outputFile.open(fileAddress, std::ios_base::app); // open the output file with given addess
    if (!this->outputFile.is_open()) // if the file is open
        std::cout << "OUTPUT FILE WAS NOT OPENED -- NO LOGGING WILL TAKE PLACE..." << std::endl;
    if (size <= SORT_MAX_SIZE) // if the given size is legal
    {
        // create an Array of type T, read values into it, and sort it
        Array<T> classArr(size);
        if(readIntoArray(classArr))
            sortAndExport(classArr);
    }
    else // if size is over the legal limit
    {
        // Create array of max legal size, read into it, and sort it
        std::cout << "Your chosen size of '" << size << "' is too large, creating " << typeid(T).name() << " array of size " << SORT_MAX_SIZE << std::endl;
        Array<T> classArr(SORT_MAX_SIZE);
        if(readIntoArray(classArr))
            sortAndExport(classArr);
        }
}

template <typename T>
bool ArrayManager<T>::readIntoArray(Array<T> &arr)
{
    for (int i = 0; i < arr.getSize(); i++) // iterate over each index
    {
        std::cout << "index [" << i <<"] --> ";
        std::cin >> arr[i];
        while (std::cin.fail()) // input verification
        {
            std::cout << "Illegal values given for index [" << i << "] -- reinput value\n--> ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes illegal value
            std::cin >> arr[i];
        }
    }
    return true;
}

template <typename T>
void ArrayManager<T>::sortAndExport(Array<T>& arrayToSort)
{
    Array<T> temp = arrayToSort; // holds unsorted array for repeated sorting
    
    // writes the date and time array was sorted for record keeping, and appends unsorted array to output file
    time_t now = time(0);
    this->outputFile << "SORTED ON: " << ctime(&now) << std::endl;
    this->outputFile << "UNSORTED ARRAY\n______________\n" << arrayToSort << std::endl;
    
    
    // preforms insertion sort and appends to output file
    printUI(this->outputFile, "\nINSERTION SORT\n\nSTART ");
    ArraySorter<T>::InsertionSort(arrayToSort, 0, arrayToSort.getSize()-1, this->outputFile);
    printUI(this->outputFile, "END\n");
    
    // preforms merge sort and appends to output file, this method directly changes original array
    printUI(this->outputFile, "MERGE SORT\n\nSTART");
    ArraySorter<T>::MergeSort(arrayToSort, 0, arrayToSort.getSize()-1, this->outputFile);
    printUI(this->outputFile, "END\n");
    
    arrayToSort = temp; // revert array to unsorted format for further sorting
    
    // preform quick sort and appends to output file
    printUI(this->outputFile, "QUICK SORT\n\nSTART ");
    ArraySorter<T>::QuickSort(arrayToSort, 0, arrayToSort.getSize()-1, this->outputFile);
    printUI(this->outputFile, "END\n");
}

template <typename T>
void ArrayManager<T>::printUI(std::ofstream &outFile, std::string message)
{
    std::cout << message << std::endl; // print to console
    outFile << message << std::endl; // appends to output file
}


template <typename T>
ArrayManager<T>::~ArrayManager()
{
    this->outputFile.close(); // close the output file stream
}

#endif /* ArrayManager_h */
