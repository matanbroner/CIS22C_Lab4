
/*
 ArraySorter class
 This class is responsible for all sorting mechanisms in the program and has the functionality of writing each step in the sorting proccesses to both the console and a given open output file.
 */

#ifndef ArraySorter_h
#define ArraySorter_h

#include "Array.h"

template <typename T>
class ArraySorter
{
private:
    
    /*
    This method merges two halves of an array whilst comparing the values at each index
     after the start of the array and after the middle of the array. It is used in
     recursivley sorting an array by the merge sort method.
     Pre: Array, start index, end index, middle index
     Post: Array is partially sorted using comparison of the values at the given indeces
     Return: none
     */
    static void mergeForMergeSort(Array<T>&, int, int, int);
    
    /*
     This method chooses a pivoting point in a given array, and continually swaps the values in the array if they are larger than said point. The value is then moved to the front of the array. It is used in recursively sorting an array using the quick sort method.
     Pre: Array, start index, end index
     Post: Array is partially sorted with pivot point moved to the front.
     Return: index of the highest value found in the array
     */
    static int partitionForQuickSort(Array<T>&, int, int);
    
    /*
     This method is used to print an Array object's contents to the console while also writing the contents to an output file.
     Pre: ofstream, Array
     Post: array printed to screen and output file appended
     Return: none
     */
    static void printArray(std::ofstream&, Array<T>&);
    
    /*
     This method swaps an Array's contents at two given indeces
     Pre: Array, index 1, index 2
     Post: values in Array's contents swapped at two given indeces
     Return: none
     */
    static void swap(Array<T>&, int, int);
public:
    
    /*
     This method is an implementation of a sorting algorithm which finds the largest value in an array, moves it to the front of the array, and then recursively does the same on the array while starting at one index forward. Base case is that the starting index + 1 should be less than or equal to end index.
     Pre: Array, start index, end index, ofstream
     Post: Array is sorted in descending order, with output file appended
     Return: none
     */
    static void InsertionSort(Array<T>, int, int, std::ofstream& file);
    
    /*
     This method is an implementation of a sorting algorithm which breaks an array into increasingly smaller arrays, then sorts the arrays in descending order. The method works recursviely and so once the array is small enough, it sorts them upwards on the stack, until full sized array is sorted.
     Pre: Array, start index, end index, ofstream
     Post: Array is sorted in descending order. Output file is appended
     Return: none
     */
    static void MergeSort(Array<T>&, int, int, std::ofstream& file);
    
    /*
     This method is an implementation of a sorting algorithm which sorts an array's contents in descending order by recursivley choosing a pivoting point in an the array, and moving values around said point. It does so by breaking the array into smaller and smaller arrays whilst choosing pivoting points.
     Pre: Array, start index, end index, ofstream
     Post: Array is sorted in descending order
     Return: none
     */
    static void QuickSort(Array<T>&, int, int , std::ofstream& file);
};

template <typename T>
void ArraySorter<T>::printArray(std::ofstream &outFile, Array<T>& array)
{
    std::cout << array << std::endl; // print array to console
    outFile << array << std::endl; // append array to file
}

template <typename T>
void ArraySorter<T>::InsertionSort(Array<T> array, int start, int end, std::ofstream& file)
{
    T value = array[start]; // take the value at the start of the array
    int current = start; // hold index of saved value
    
    // Find index current within the sorted subset array[0 to start-1]
    // where element arr[start] belongs
    while (current > 0 && array[current - 1] < value)
    {
        array[current] = array[current - 1]; // move values front one index
        current--;
    }
    
    array[current] = value; // set start of the array with value held
    
    // Subarray array[current to start-1] is shifted right by one position --> array[current+1..start]
    
    printArray(file, array); // output array at current recursion and append to file
    
    if (start + 1 <= end) { // if shrinking the array further is possible
        InsertionSort(array, start + 1, end, file); // sort again with one index forward from current start
    }
}


template <typename T>
void ArraySorter<T>::MergeSort(Array<T>& array ,int start, int end, std::ofstream& file)
{
    int middle;
    
    if (start < end) // if the indeces called on are still legal
    {
        middle = (start + end) / 2; // find middle index
        
        MergeSort(array, start, middle, file); // call a new sort array from start to middle
        MergeSort(array,middle + 1, end, file); // call a new sort from middle + 1 to end
        
        mergeForMergeSort(array, start, end, middle); // merge the two halves of the sorted arrays
        printArray(file, array); // print array and append to output file
    }
}

template <typename T>
void ArraySorter<T>::mergeForMergeSort(Array<T>& array, int start, int end, int middle)
{
    int startLeft = start, startRight = middle + 1, mergeIndex = 0; // find two start indeces on two halves of given array
    T temp[(end - start) + 1]; // create a temporary array with needed size
        
    while(startLeft <= middle && startRight <= end) // traverse both halves of array
    {
        // find the higher of the two values with the indeces in both halves
        // set temp array at current index with the higher value
        if(array[startLeft] > array[startRight])
            temp[mergeIndex++] = array[startLeft++];
        else
            temp[mergeIndex++] = array[startRight++];
    }
    
    while(startLeft <= middle) // fill temp with the rest of the values from array left half
    {
        temp[mergeIndex++] = array[startLeft++];
    }
        
    while(startRight <= end) // fill temp with the rest of the values from array right half
    {
        temp[mergeIndex++] = array[startRight++];
    }
        
    for(startLeft = start; startLeft <= end; startLeft++)
    {
        array[startLeft] = temp[startLeft - start]; // set array values to temp array values
    }
        
    return;
}

template <typename T>
void ArraySorter<T>::QuickSort(Array<T>& array, int start, int end, std::ofstream& file)
{
    if (start < end) // if the array bounds are still legal
    {
        int partitionIndex = partitionForQuickSort(array, start, end); // find the pivot point
        
        // Separately sort elements before
        // partition and after pivot point
        QuickSort(array, start, partitionIndex - 1, file);
        QuickSort(array, partitionIndex + 1, end, file);
        printArray(file, array); // write array to console and append to output file
    }
}

template <typename T>
int ArraySorter<T>::partitionForQuickSort(Array<T>& array, int start, int end)
{
    T pivotPoint = array[start]; // determine pivot element for comparison
    int highIndex = start;  // Index of larger element
    
    for (int index = start + 1; index <= end; index++)
    {
        // If current element is larger than pivot
        if (array[index] > pivotPoint)
        {
            highIndex++;    // increment index of smaller element
            swap(array, index, highIndex); // swap the values at the larger value index and current index
        }
    }
    swap(array, highIndex, start); // swap values at larger value index and array start
    return highIndex; // return the index of the higher element
}

template <typename T>
void ArraySorter<T>::swap(Array<T>& array, int index1, int index2)
{
    T temp = array[index1]; // store value
    array[index1] = array[index2]; // change value at first index
    array[index2] = temp; // change value at second index
}

#endif /* ArraySorter_h */
