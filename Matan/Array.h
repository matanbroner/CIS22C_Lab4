#pragma once
#include <string>
#include <fstream>
#include <iostream>

template <typename T>
class Array;

template <typename T>
std::ostream& operator<<(std::ostream& output, Array<T>&);

template <typename T>
std::ofstream& operator<<(std::ofstream& outFile, Array<T>&);


template <typename T>
class Array
{
private:
    int size; // size of the array to be held
    T* arrayContainer; // pointer used to create array
    
public:
    Array(int);
    Array(Array&);
    
    T &operator[](int index);
    void operator=(Array&);
    bool setIndex(int, T); // set a value at a given index
    T getIndex(int); // retrieve a value at a given index
    int getSize(); // gets size of array
    ~Array();
    
};

template <typename T>
Array<T>::Array(int size)
{
    this->size = size;
    this->arrayContainer = new T[this->size]();
}
template <typename T>
Array<T>::Array(Array& arr)
{
    this->size = arr.size;
    this->arrayContainer = new T[this->size]();
    for (int i = 0; i < this->size; i++)
    {
        this->arrayContainer[i] = arr[i];
    }
}

template <typename T>
T& Array<T>::operator[](int index)
{
    if (index >= this->size)
        throw std::out_of_range("bad index");
    return this->arrayContainer[index];
}

template <typename T>
int Array<T>::getSize()
{
    return this->size;
}

template <typename T>
bool Array<T>::setIndex(int index, T data)
{
    if (index >= 0 && index <= (this->size - 1))
    {
        this->arrayContainer[index] = data;
        return true;
    }
    
    else
    {
        throw "INDEXING ERROR";
        return false;
    }
}

template <typename T>
T Array<T>::getIndex(int index)
{
    if (index >= 0 && index <= (this->size - 1))
    {
        return this->arrayContainer[index];
    }
    
    else
    {
        throw "INDEXING ERROR";
    }
}

template <typename T>
std::ostream& operator<<(std::ostream &output, Array<T>& arr)
{
    for (int i = 0; i < arr.getSize(); i++)
        output << "[" << arr[i] << "] ";
    output << std::endl;
    return output;
}

template <typename T>
std::ofstream& operator<<(std::ofstream &outFile, Array<T>& arr)
{
    for (int i = 0; i < arr.getSize(); i++)
        outFile << "[" << arr[i] << "] ";
    outFile << std::endl;
    return outFile;
}

template <typename T>
void Array<T>::operator=(Array<T> &arr)
{
    if (this->size != arr.size)
        throw "No viable transfer of elements in arrays of nonequal sizes";
    for (int i = 0; i < this->size; i++)
        this->arrayContainer[i] = arr.arrayContainer[i];
}

template <typename T>
Array<T>::~Array()
{
    delete[] this->arrayContainer; //--> This throws an exception, I wanted to show correct deletion of dynamic memory...
}
