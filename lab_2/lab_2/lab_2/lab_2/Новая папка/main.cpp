#include <iostream>
#include "Matrix.hpp"
#include <map>
#include <Windows.h>
#include <string>
#include "getCPUTime.h"
#include <fstream>
template <typename T>
void  get_time_0()
{
	std::ofstream fout("time.txt");
	int times = 15;
	for (int i = 100; i < 700; i+= 100)
	{
		std::cout << "for len = " << i << ":" << std::endl;
		Matrix<T> matr1 = fill_rand_matrix<T>(i,i);
		Matrix<T> matr2 = fill_rand_matrix<T>(i, i);
		std::map <std::string, double> time_ = {
													{"classic" , 0.0},
													{"vgd" , 0.0},
													{"vgd_opt",  0.0}
												};
		for (int j = 0; j < times; j++)
		{
			//std::cout << "\tj is " << j << std::endl;
			double start = getCPUTime();
			matr1.classic_mult(matr2);
			double stop = getCPUTime();
			time_["classic"] += (stop - start);


			start = getCPUTime();
			matr1.Vinograd_mult(matr2);
			stop = getCPUTime();
			time_["vgd"] += (stop - start);
			
			start = getCPUTime();
			matr1.Vinograd_mult_opt(matr2);
			stop = getCPUTime();
			time_["vgd_opt"] += (stop - start);
		}
		std::map<std::string, double> ::iterator it = time_.begin();
		for (int i = 0; it != time_.end(); it++, i++)
		{
			time_[it->first] /= times;
			std::cout << "    " << it->first << " method time is " << time_[it->first] << std::endl;
			fout << "    " << it->first << " method time is " << time_[it->first] << "\n";
		}
	}

	fout << "\n\n\n";

	for (int i = 101; i < 700; i += 100)
	{
		std::cout << "for len = " << i << ":" << std::endl;
		Matrix<T> matr1 = fill_rand_matrix<T>(i, i);
		Matrix<T> matr2 = fill_rand_matrix<T>(i, i);
		std::map <std::string, double> time_ = {
													{"classic" , 0.0},
													{"vgd" , 0.0},
													{"vgd_opt",  0.0}
		};
		for (int j = 0; j < times; j++)
		{
			//std::cout << "\tj is " << j << std::endl;
			double start = getCPUTime();
			matr1.classic_mult(matr2);
			double stop = getCPUTime();
			time_["classic"] += (stop - start);


			start = getCPUTime();
			matr1.Vinograd_mult(matr2);
			stop = getCPUTime();
			time_["vgd"] += (stop - start);

			start = getCPUTime();
			matr1.Vinograd_mult_opt(matr2);
			stop = getCPUTime();
			time_["vgd_opt"] += (stop - start);
		}
		std::map<std::string, double> ::iterator it = time_.begin();
		for (int i = 0; it != time_.end(); it++, i++)
		{
			time_[it->first] /= times;
			std::cout << "    " << it->first << " method time is " << time_[it->first] << std::endl;
			fout << "    " << it->first << " method time is " << time_[it->first] << "\n";
		}
	}
	fout.close();
}










int main()
{
	
	srand(static_cast<unsigned int>(time(0)));
	get_time_0<int>();
	/*Matrix<int> M1(3, 3);
	std::cout << "\nInput M1 :" << std::endl;
	M1.input_matrix();
	Matrix<int> M2(3, 3);
	std::cout << "\nInput M2 :" << std::endl;
	M2.input_matrix();
	
	std::cout << "\nM1 is :" << std::endl;
	M1.output_matrix();
	std::cout << "\nM2 is :" << std::endl;
	M2.output_matrix();

	Matrix<int> res_classic(M1.classic_mult(M2));
	std::cout << "\nRes is :" << std::endl;
	res_classic.output_matrix();

	Matrix<int> res_Vin(M1.Vinograd_mult(M2));
	std::cout << "\nVinograd Res is :" << std::endl;
	res_Vin.output_matrix();

	Matrix<int> res_Vin_opt(M1.Vinograd_mult_opt(M2));
	std::cout << "\nVinograd Opt Res is :" << std::endl;
	res_Vin_opt.output_matrix();
	*/
	return 0;
}