// DESCENDING ORDER SORTS:

// sorts taken from https://www.geeksforgeeks.org/ and edited

#ifndef Sort_h
#define Sort_h

#include "Array.h"
#include <iostream>
#include <fstream>

// sorts are descending only

template<typename T>
void insertionSort(Array<T>&, int, std::ofstream&);

template<typename T>
void swap(T*, T*);
template<typename T>
int partition(Array<T>&, int, int);
template<typename T>
void quickSort(Array<T>&, int, int, std::ofstream&);

template<typename T>
void merge(Array<T>&, int, int, int);
template<typename T>
void mergeSort(Array<T>&, int, int, std::ofstream&);

// function definitions
template<typename T>
void insertionSort(Array<T>& arr, int n, std::ofstream& output)
{
	// Base case 
	if (n <= 1)
		return;

	// Sort first n-1 elements 
	insertionSort(arr, n - 1, output);

	// Insert last element at its correct position 
	// in sorted array. 
	T last = arr[n - 1];
	int j = n - 2;

	/* Move elements of arr[0..i-1], that are
	greater than key, to one position ahead
	of their current position */
	while (j >= 0 && arr[j] <= last)
	{
		arr[j + 1] = arr[j];
		j--;
	}
	arr[j + 1] = last;

	output << arr;
	std::cout << arr;
}

template<typename T>
void swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

template<typename T>
int partition(Array<T>& arr, int low, int high, std::ofstream& output)
{
	T pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] >= pivot)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
			output << arr;
			std::cout << arr;
		}
	}
	swap(&arr[i + 1], &arr[high]);

	return (i + 1);
}

template<typename T>
void quickSort(Array<T>& arr, int low, int high, std::ofstream& output)
{	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int index = partition(arr, low, high, output);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, index - 1, output);
		quickSort(arr, index + 1, high, output);
	}
}

template<typename T>
void merge(Array<T>& arr, int l, int m, int r, std::ofstream& output)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	//int L[n1], R[n2];
	Array<T>L(n1);
	Array<T>R(n2);

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] > R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	output << arr;
	std::cout << arr;
}

template<typename T>
void mergeSort(Array<T>& arr, int l, int r, std::ofstream& output)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m, output);

		mergeSort(arr, m + 1, r, output);

		merge(arr, l, m, r, output);
	}
}

#endif


// ASCENDING ORDER SORTS:

//#ifndef Sort_h
//#define Sort_h
//
//#include "Array.h"
//#include <iostream>
//#include <fstream>
//
//template<typename T>
//void insertionSort(Array<T>&, int, std::ofstream&);
//
//template<typename T>
//void swap(T*, T*);
//template<typename T>
//int partition(Array<T>&, int, int);
//template<typename T>
//void quickSort(Array<T>&, int, int, std::ofstream&);
//
//template<typename T>
//void merge(Array<T>&, int, int, int);
//template<typename T>
//void mergeSort(Array<T>&, int, int, std::ofstream&);
//
//// function definitions
//template<typename T>
//void insertionSort(Array<T>& arr, int n, std::ofstream& output)
//{
//	// Base case 
//	if (n <= 1)
//		return;
//
//	// Sort first n-1 elements 
//	insertionSort(arr, n - 1, output);
//
//	// Insert last element at its correct position 
//	// in sorted array. 
//	T last = arr[n - 1];
//	int j = n - 2;
//
//	/* Move elements of arr[0..i-1], that are
//	greater than key, to one position ahead
//	of their current position */
//	while (j >= 0 && arr[j] > last)
//	{
//		arr[j + 1] = arr[j];
//		j--;
//	}
//	arr[j + 1] = last;
//
//	output << arr;
//	std::cout << arr;
//}
//
//template<typename T>
//void swap(T* a, T* b)
//{
//	T temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//template<typename T>
//int partition(Array<T>& arr, int low, int high)
//{
//	T pivot = arr[high];    // pivot 
//	int i = (low - 1);  // Index of smaller element 
//
//	for (int j = low; j <= high - 1; j++)
//	{
//		// If current element is smaller than or 
//		// equal to pivot 
//		if (arr[j] <= pivot)
//		{
//			i++;    // increment index of smaller element 
//			swap(&arr[i], &arr[j]);
//		}
//	}
//	swap(&arr[i + 1], &arr[high]);
//	return (i + 1);
//}
//
//template<typename T>
//void quickSort(Array<T>& arr, int low, int high, std::ofstream& output)
//{
//	output << arr;
//	std::cout << arr;
//
//	if (low < high)
//	{
//		/* pi is partitioning index, arr[p] is now
//		at right place */
//		int index = partition(arr, low, high);
//
//		// Separately sort elements before 
//		// partition and after partition 
//		quickSort(arr, low, index - 1, output);
//		output << arr;
//		std::cout << arr;
//
//		quickSort(arr, index + 1, high, output);
//	}
//}
//
//template<typename T>
//void merge(Array<T>& arr, int l, int m, int r, std::ofstream& output)
//{
//	int i, j, k;
//	int n1 = m - l + 1;
//	int n2 = r - m;
//
//	/* create temp arrays */
//	//int L[n1], R[n2];
//	Array<T>L(n1);
//	Array<T>R(n2);
//
//	/* Copy data to temp arrays L[] and R[] */
//	for (i = 0; i < n1; i++)
//		L[i] = arr[l + i];
//	for (j = 0; j < n2; j++)
//		R[j] = arr[m + 1 + j];
//
//	/* Merge the temp arrays back into arr[l..r]*/
//	i = 0; // Initial index of first subarray 
//	j = 0; // Initial index of second subarray 
//	k = l; // Initial index of merged subarray 
//	while (i < n1 && j < n2)
//	{
//		if (L[i] <= R[j])
//		{
//			arr[k] = L[i];
//			i++;
//		}
//		else
//		{
//			arr[k] = R[j];
//			j++;
//		}
//		k++;
//	}
//
//	/* Copy the remaining elements of L[], if there
//	are any */
//	while (i < n1)
//	{
//		arr[k] = L[i];
//		i++;
//		k++;
//	}
//
//	/* Copy the remaining elements of R[], if there
//	are any */
//	while (j < n2)
//	{
//		arr[k] = R[j];
//		j++;
//		k++;
//	}
//	output << arr;
//	std::cout << arr;
//}
//
//template<typename T>
//void mergeSort(Array<T>& arr, int l, int r, std::ofstream& output)
//{
//	output << arr;
//	std::cout << arr;
//
//	if (l < r)
//	{
//		// Same as (l+r)/2, but avoids overflow for 
//		// large l and h 
//		int m = l + (r - l) / 2;
//
//		// Sort first and second halves 
//		mergeSort(arr, l, m, output);
//
//		mergeSort(arr, m + 1, r, output);
//
//		merge(arr, l, m, r, output);
//	}
//}
//
//#endif
