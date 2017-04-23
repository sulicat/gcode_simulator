#pragma once
#include <vector>
template<typename T>
class ArrayList final
{
private:
	T *data;
	unsigned int size, maxSize;
public:
	ArrayList(int maxSize) { data = new T[maxSize]; this->maxSize = maxSize; size = 0; }
	ArrayList() { data = new T[100]; this->maxSize = 100; size = 0; }
	~ArrayList() { /*delete data; */}
	void operator+(T item) { data[size++] = item; }
	void add(T item){ data[size++] = item; }
	T* Data() { T *ret = new T[size]; for (int i = 0; i < size; i++)ret[i] = data[i]; return ret; }
	T& operator[](int index) { return data[index]; }
	T RemoveIndex(int index)
	{
		T ret = data[index];
		for (unsigned int i = index; i < size; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
		return ret;
	}
	int find(T value)
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == value)
			{
				return i;
			}
		}
	}
	T operator-(T val) { return RemoveIndex(find(val)); }
	unsigned int Size() { return size; }
	unsigned int MaxSize() { return maxSize; }
	void Clear() { size = 0; }

	ArrayList<T> operator=(ArrayList<T> o)
	{
		size = o.size;
		maxSize = o.maxSize;
		data = o.data;
	}

	operator std::vector<T>()
	{
		std::vector<T> ret(data, data+size);
		return ret;
	}
};

template<>
char* ArrayList<char>::Data()
{
	char *ret = new char[size + 1]; for (size_t i = 0; i < size; i++)ret[i] = data[i]; ret[size] = '\0'; return ret;
}