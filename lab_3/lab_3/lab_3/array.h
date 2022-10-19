#include <iostream>
#include <vector>
template <typename T>
class Array
{
private:
	std::vector<T> array;
	int N;
public:
	Array() = default;
	Array(int N);
	Array(std::initializer_list<T> list_);
	Array(std::vector<T> list_);
	Array(const Array& Arr);
	~Array() = default;

	void sort_insert();
	void sort_bubble();
	void sort_choice();
	void output_array();
	void input_array();
	void fill_rand_arr();
	void reverse_arr();
};
