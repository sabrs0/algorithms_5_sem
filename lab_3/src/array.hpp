#include "array.h"

template <typename T>
Array<T>::Array(int N)
{
	this->array.resize(N);
}
template <typename T>
Array<T>::Array(std::initializer_list<T> list_)
{
	this->array.resize(list_.size());
	int i = 0;
	for (T elem : list_)
	{
		this->array[i] = elem;
		i++;
	}
}
template <typename T>
void Array<T>::input_array()
{
	std::cout << "Input N: ";
	std::cin >> this->N;
	std::cout << "Input Array: \n";
	this->array.resize(this->N);
	for (int i = 0; i < this->N; i++)
	{
		std::cin >> this->array[i];
	}
}
template <typename T>
Array<T>::Array(std::vector<T> list_)
{
	this->array.resize(list_.size());
	for (int i = 0; i < this->array.size(); i++)
	{
		this->array[i] = list_[i];
	}
}
template <typename T>
Array<T>::Array(const Array& Arr)
{
	this->array.resize(Arr.array.size());
	for (int i = 0; i < this->array.size(); i++)
	{
		this->array[i] = Arr.array[i];
	}
}
template <typename T>
void Array<T>:: sort_insert()
{
	for (int i = 0; i < this->array.size() - 1; i++)
	{
		int key = i + 1;
		T temp = this->array[key];
		for (int j = i + 1; j > 0; j--)
		{
			if (temp < this->array[j - 1])
			{
				this->array[j] = this->array[j - 1];
				key = j - 1;
			}
		}
		this->array[key] = temp;
	}
}
template <typename T>
void Array<T>::sort_bubble()
{
	
	int l = this->array.size();
	for (int i = 0; i < l - 1; i ++)
	{
		for (int j = i; j < l; j ++)
		{
			if (this->array[i] > this->array[j])
			{
				std::swap(this->array[i], this->array[j]);
			 }
		}
	}
}
template <typename T>
void Array<T>::sort_choice()
{
	for (int startIndex = 0; startIndex < this->array.size() - 1; ++startIndex)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < this->array.size(); ++currentIndex)
		{
			if (this->array[currentIndex] < this->array[smallestIndex])
				smallestIndex = currentIndex;
		}
		std::swap(this->array[startIndex], this->array[smallestIndex]);
	}
}
template <typename T>
void Array<T>::fill_rand_arr()
{
	srand(static_cast<unsigned int> (time(0)));
	for (int i = 0; i < this->array.size(); i++)
	{
		this->array[i] = rand();
	}
}
template <typename T>
void Array<T>::reverse_arr()
{
	this->sort_bubble();
	for (int i = 0; i < this->array.size() / 2; i++)
	{
		std::swap(this->array[i],this->array[this->array.size() - 1 - i]);
	}
}
template <typename T>
void Array<T>::output_array()
{
	for (int i = 0; i < this->array.size(); i++)
	{
		std::cout << this->array[i] << " ";
	}
	std::cout << std::endl;
}