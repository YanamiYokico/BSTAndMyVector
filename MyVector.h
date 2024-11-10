#include <iostream>
using namespace std;

template<typename T>
class vector
{
public:

	vector() : vector(nullptr, 0, 0) {}
	vector(T* arr, int size, int capacity) : arr(arr), n(size), capacity(capacity) {}
private:
	T* arr;
	int n;
	int capacity;
public:
	int size() { return n; }
	int Acapacity() { return capacity; }
	void set_size(int size, int grow = 1);
	void show() const;
	int last_index();
	bool is_empty() { return n == 0; }
	void freeExtra();
	void clear();
	T getIndex(int index);
	T& operator[](int index);
	void push_back(T value);
	vector<T>& append(vector& other);
	vector<T>* getData();
	void insert(int value, int index);
	void erase(int index);
	T* begin() const { return arr; }
	T* end() const { return arr + n; }
};

template<typename T>
void vector<T>::set_size(int size, int grow)
{
	if (size > capacity)
	{
		int new_size = size + grow;
		T* newarr = new T[new_size];

		for (int i = 0; i < n; i++)
		{
			newarr[i] = arr[i];
		}

		delete[] arr;

		arr = newarr;
	}
	else if (size < n) {
		n = size;
	}
}


template<typename T>
void vector<T>::show() const
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

template<typename T>
int vector<T>::last_index()
{
	int lindex = -1;
	for (int i = 0; i < n; i++) { lindex++; }
	return lindex;
}

template<typename T>
void vector<T>::freeExtra()
{
	if (n < capacity)
	{
		T* newarr = new T[n];
		for (int i = 0; i < n; i++)
		{
			newarr[i] = arr[i];
		}
		delete[] arr;
		arr = newarr;
		capacity = n;
	}
}

template<typename T>
void vector<T>::clear()
{
	delete[] arr;
	arr = nullptr;
	n = 0;
	capacity = 0;
}

template<typename T>
T vector<T>::getIndex(int index)
{
	for (int i = 0; i < n; i++)
	{
		if (i == index)
		{
			return arr[index];
		}
	}
	return -1;
}

template<typename T>
T& vector<T>::operator[](int index)
{
	if (n >= index)
	{
		return arr[index];
	}

	return arr[-1];
}

template<typename T>
void vector<T>::push_back(T value)
{
	T* newArr = new T[n + 1];

	for (int i = 0; i < n; i++)
	{
		newArr[i] = arr[i];
	}
	delete[] arr;
	newArr[n] = value;

	n += 1;
	arr = newArr;
}

template<typename T>
vector<T>& vector<T>::append(vector& other)
{
	T* newarr = new T[this->n + other.n];

	for (int i = 0; i < this->n; i++)
	{
		newarr[i] = this->arr[i];
	}

	for (int i = 0; i < other.n; i++)
	{
		newarr[this->n + i] = other.arr[i];
	}
	delete[] arr;
	this->arr = newarr;
	this->n = this->n + other.n;
	this->capacity = this->n + other.n;
	return *this;
}

template<typename T>
vector<T>* vector<T>::getData()
{
	vector<T>* ptr = new vector<T>(this->arr, n, capacity);
	return ptr;
}

template<typename T>
void vector<T>::insert(int value, int index)
{
	if (index < 0 || index >= n)
	{
		return;
	}

	T* newarr = new T[n + 1];

	for (int i = 0; i < index; i++)
	{
		newarr[i] = this->arr[i];
	}

	newarr[index] = value;

	for (int i = index; i < n; i++)
	{
		newarr[i + 1] = this->arr[i];
	}
	n++;
	delete[] arr;
	arr = newarr;
}

template<typename T>
void vector<T>::erase(int index)
{
	if (index < 0 || index >= n)
	{
		return;
	}

	T* newarr = new T[n - 1];

	for (int i = 0; i < index; i++)
	{
		newarr[i] = this->arr[i];
	}
	for (int i = index + 1; i < n; i++)
	{
		newarr[i - 1] = this->arr[i];
	}
	n--;
	delete[] arr;
	arr = newarr;
}