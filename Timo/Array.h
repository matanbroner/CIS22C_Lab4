#ifndef Array_h
#define Array_h

#include <iostream>

template<typename T>
class Array
{
private:
	int size;
	T* arr;

public:
	Array() : size(0), arr(NULL) {}
	Array(int size) {
		this->size = size;
		this->arr = new T[size];
		for (int i = 0; i < size; i++) {
			arr[i] = T();
		}
	}
	~Array() { this->deleteArray();	}

	int getSize() { return this->size; }

	int getSizeOf() { return sizeof(&arr); }

	// setSize can only be called if size has not been defined or if deleteArray was called;
	void setSize(int size) {
		if (this->size != 0 || this->arr != NULL)  // check both to ensure no shenaniganry
			throw std::exception("Array<T>:setSize(int size): cannot change size of existing array");
		else {
			this->size = size;
			this->arr = new T[size];

			for (int i = 0; i < size; i++) {
				arr[i] = T();
			}
		}
	}

	void deleteArray() {
		delete[] this->arr;
		this->arr = NULL;
		this->size = 0;
	}

	T& operator[](int index) {
		if (index < size && index > -1)
			return arr[index];
		else
			throw std::out_of_range("Array<T>::operator[]: index is out of range");
	}
	friend std::ostream& operator<< (std::ostream& output, const Array<T>& a) {
		int i;
		if (SORT_MAX_SIZE < 40) {
			for (i = 0; i < a.size; i++)
				output << a.arr[i] << ' ';
			output << std::endl;
		}
		else {  // if size >=40 only display 40 per line
			for (i = 0; i < a.size; i++) {
				output << a.arr[i] << ' ';
				if ((i + 1) % 40 == 0)
					output << std::endl;
			}

			if (i % 40 != 0)
				output << std::endl;
		}

		return output;
	}
};

#endif
