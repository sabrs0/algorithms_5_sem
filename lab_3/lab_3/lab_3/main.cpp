#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "array.hpp"
#include <map>
#include "getCPUTime.h"
#define SIZES_LEN 4
#pragma optimize( "", off )
template <typename T>
void backwards_time()
{
	int sizes[SIZES_LEN] = { 200, 500, 1000, 5000 };
	int times = 10;

	double start, stop;
	FILE* f = fopen("reversed_time.txt", "w");
	for (int i = 0; i < SIZES_LEN; i++)
	{
		fprintf(f, "for len : %d\n", sizes[i]);
		std::cout << "for len " << sizes[i] << " :\n";
		std::map <const char*, double> time_ = {
													{"bubble" , 0.0},
													{"insert" , 0.0},
													{"choice",  0.0}
		};

		for (int j = 0; j < times; j++)
		{
			Array<T> A1(sizes[i]);
			Array<T> A2(sizes[i]);
			Array<T> A3(sizes[i]);
			A1.fill_rand_arr();
			A2.fill_rand_arr();
			A3.fill_rand_arr();
			A1.reverse_arr();
			start = getCPUTime();
			A1.sort_bubble();
			stop = getCPUTime();
			time_["bubble"] += stop - start;

			A2.reverse_arr();
			start = getCPUTime();
			A2.sort_choice();
			stop = getCPUTime();
			time_["choice"] += stop - start;

			A3.reverse_arr();
			start = getCPUTime();
			A3.sort_insert();
			stop = getCPUTime();
			time_["insert"] += stop - start;
		}
		int ind = 0;
		for (auto elem : time_)
		{
			elem.second /= times;
			std::cout << "    " << elem.first << " method time is " << elem.second << std::endl;
			fprintf(f, "    %s method time is %.15lf\n", elem.first, elem.second);
			/*
			fout << "    " << elem.first << " method time is ";
			fout.precision(7);
			fout << elem.second << "\n";*/

		}

	}
	fclose(f);
	//fout.close();
}

#pragma optimize( "", off )
template <typename T>
void random_time()
{
	int sizes[SIZES_LEN] = { 200, 500, 1000, 5000 };
	int times = 20;

	double start, stop;
	FILE* f = fopen("random_time.txt", "w");
	for (int i = 0; i < SIZES_LEN; i++)
	{
		fprintf(f, "for len : %d\n", sizes[i]);
		std::cout << "for len " << sizes[i] << " :\n";
		std::map <const char*, double> time_ = {
													{"bubble" , 0.0},
													{"insert" , 0.0},
													{"choice",  0.0}
		};

		for (int j = 0; j < times; j++)
		{
			Array<T> A1(sizes[i]);
			Array<T> A2(sizes[i]);
			Array<T> A3(sizes[i]);
			A1.fill_rand_arr();
			start = getCPUTime();
			A1.sort_bubble();
			stop = getCPUTime();
			time_["bubble"] += stop - start;

			A2.fill_rand_arr();
			start = getCPUTime();
			A2.sort_choice();
			stop = getCPUTime();
			time_["choice"] += stop - start;

			A3.fill_rand_arr();
			start = getCPUTime();
			A3.sort_insert();
			stop = getCPUTime();
			time_["insert"] += stop - start;
		}
		int ind = 0;
		for (auto elem : time_)
		{
			elem.second /= times;
			std::cout << "    " << elem.first << " method time is " << elem.second << std::endl;
			fprintf(f, "    %s method time is %.15lf\n", elem.first, elem.second);
			/*
			fout << "    " << elem.first << " method time is ";
			fout.precision(7);
			fout << elem.second << "\n";*/

		}

	}
	fclose(f);
	//fout.close();
}
#pragma optimize( "", off )
template <typename T>
void sorted_time()
{
	int sizes[SIZES_LEN] = { 200, 500, 1000, 5000 };
	int times = 20;

	double start, stop;
	FILE* f = fopen("sorted_time.txt", "w");
	for (int i = 0; i < SIZES_LEN; i++)
	{
		fprintf(f, "for len : %d\n", sizes[i]);
		std::cout << "for len " << sizes[i] << " :\n";
		std::map <const char*, double> time_ = {
													{"bubble" , 0.0},
													{"insert" , 0.0},
													{"choice",  0.0}
		};

		for (int j = 0; j < times; j++)
		{
			Array<T> A1(sizes[i]);
			A1.fill_rand_arr();
			A1.sort_bubble();
			Array<T> A2(sizes[i]);
			A2.fill_rand_arr();
			A2.sort_bubble();
			Array<T> A3(sizes[i]);
			A3.fill_rand_arr();
			A3.sort_bubble();

			start = getCPUTime();
			A1.sort_bubble();
			stop = getCPUTime();
			time_["bubble"] += stop - start;

			start = getCPUTime();
			A2.sort_choice();
			stop = getCPUTime();
			time_["choice"] += stop - start;

			start = getCPUTime();
			A3.sort_insert();
			stop = getCPUTime();
			time_["insert"] += stop - start;
		}
		int ind = 0;
		for (auto elem : time_)
		{
			elem.second /= times;
			std::cout << "    " << elem.first << " method time is " << elem.second << std::endl;
			fprintf(f, "    %s method time is %.15lf\n", elem.first, elem.second);
			/*
			fout << "    " << elem.first << " method time is ";
			fout.precision(7);
			fout << elem.second << "\n";*/

		}

	}
	fclose(f);
}


int main()
{
	/*srand(static_cast<unsigned int> (time(0)));
	random_time<int>();
	sorted_time<int>();
	backwards_time<int>();*/
	
	Array<int> Abub({ 3, 2, 1, 5, 7, -2 });
	Abub.output_array();
	Abub.sort_bubble();
	Abub.output_array();

	Array<int> Ains({ 3, 2, 1, 5, 7, -2 });
	Ains.output_array();
	Ains.sort_insert();
	Ains.output_array();

	Array<int> Ach({ 3, 2, 1, 5, 7, -2 });
	Ach.output_array();
	Ach.sort_choice();
	Ach.output_array();

	Array<int>Atest;
	Atest.input_array();
	Atest.sort_bubble();
	Atest.output_array();
	return 0;
}