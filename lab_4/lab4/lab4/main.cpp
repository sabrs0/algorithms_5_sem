#include <iostream>
#include <vector>
#include <thread>
#include <stdio.h>
#include <chrono>
#include <cstdlib>
#include <cmath>
using namespace std;
#define ITERATIONS 20
template<class T>
class Matrix
{
public:
	int M;
	int N;
	vector<vector<T>> data;
	Matrix();
	Matrix(const Matrix<T>& M_);

	Matrix(int M_, int N_);


	Matrix<T> classic_sum(  Matrix<T>& M2);

	~Matrix<T>();

	Matrix<T>& input_matrix();

	void output_matrix();

};
template<class T>
void parallel_add(Matrix<T> matrix1, Matrix<T> matrix2, Matrix<T> &result, int thread, int threads_amount)
{

	for (int i = thread; i < result.M; i += threads_amount)
	{
		for (int j = 0; j < result.N; j++)
		{
			result.data[i] [j] = (matrix1.data[i][j] + matrix2.data[i][j]);
		}

	}
}
template<class T>
Matrix<T>  parallel_sum( Matrix<T> M1,  Matrix<T> M2, int threads_amount)
{
	Matrix<T> res(M1.M, M2.N);

	vector<thread> threads(threads_amount);

	for (int thread_ = 0; thread_ < threads_amount; thread_++)
	{
		threads[thread_] = thread(parallel_add<T>, M1, M2, std::ref(res), thread_, threads_amount);
	}

	for (int i = 0; i < threads_amount; i++)
	{
		threads[i].join();
	}

	return res;
}
template<typename T>
Matrix<T>::Matrix()
{
	this->M = 0;
	this->N = 0;

	//std::cout << "\nMatrix contructor usual for " << this << std::endl;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& M_)
{
	this->M = M_.M;
	this->N = M_.N;
	this->data.resize(this->M);
	for (int i = 0; i < this->M; i++)
	{
		this->data[i].resize(this->N);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			this->data[i][j] = M_.data[i][j];
		}
	}
	//cout << "\n Copy constructor for " << this << std::endl;
}
template<typename T>
Matrix<T>::~Matrix()
{
	//std::cout << "\nMatrix destructor  for " << this << std::endl;
}

template<typename T>
Matrix<T>::Matrix(int M_, int N_)
{
	this->M = M_;
	this->N = N_;
	this->data.resize(this->M);
	for (int i = 0; i < this->M; i++)
	{
		this->data[i].resize(this->N);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			this->data[i][j] = 0;
		}
	}
	//std::cout << "\nMatrix contructor param for " << this << std::endl;
}

template<typename T>
Matrix<T>& Matrix<T> ::input_matrix()
{
	std::cout << "M:" << std::endl;
	std::cin >> this->M;

	std::cout << "N:" << std::endl;
	std::cin >> this->N;
	this->data.resize(this->M);
	for (int i = 0; i < this->M; i++)
	{
		this->data[i].resize(this->N);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> this->data[i][j];
		}
	}
	return *this;
}

template<typename T>
void Matrix<T> ::output_matrix()
{
	std::cout << "Matrix" << "[" << this->M << "] [" << this->N << "]\n";

	for (int i = 0; i < this->M; i++)
	{
		for (int j = 0; j < this->N; j++)
		{
			std::cout << this->data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
template <typename T>
Matrix<T> fill_rand_matrix(int M, int N)
{
	Matrix<T> M_(M, N);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			M_.data[i][j] = static_cast<int> (rand() % 1000);
		}
	}
	return M_;
}
template <typename T>
Matrix<T> Matrix<T>::classic_sum( Matrix<T>& M2)
{
	Matrix<T> res(this->M, M2.N);
	for (int i = 0; i < res.M; i++)
	{
		for (int j = 0; j < res.N; j++)
		{
			res.data[i][j] = this->data[i][j] + M2.data[i][j];
		}
	}
	return res;

}
template <typename T>
void time_analysis()
{
	int M, N;
	cout << "Input M:\n";
	cin >> M;
	cout << "\nInput N:\n";
	cin >> N;

	Matrix<T> m1 = fill_rand_matrix<T>(M, N);
	Matrix<T> m2 = fill_rand_matrix<T>(M, N);
	//Matrix<T> result;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	double result_time;

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  m1.classic_sum(m2);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time sequential on random array: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  parallel_sum(m1, m2, 1);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 1 thread on random matr: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */parallel_sum(m1, m2, 2);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 2 threads on random mat: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  parallel_sum(m1, m2, 4);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 4 threads on random matr: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  parallel_sum(m1, m2, 8);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 8 threads on random matr: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  parallel_sum(m1, m2, 16);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 16 threads on random matr: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  parallel_sum(m1, m2, 32);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 32 threads on random matr: %lf seconds\n\n", result_time / 1e9);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < ITERATIONS; i++)
	{
		/*result = */  parallel_sum(m1, m2, 64);
	}

	end = std::chrono::system_clock::now();

	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	result_time /= ITERATIONS;

	printf("Time parallel 64 threads on random matr: %lf seconds\n\n", result_time / 1e9);
}
void show_info()
{
	cout << endl << "1. Run Sequential algorithm" << endl;
	cout << "2. Run Parallel algorithm" << endl;
	cout << "3. Run Time analysis" << endl;
	cout << "0. Exit" << endl;
}
int main()
{
	int command = -1, threads = 1;

	while (command != 0)
	{
		show_info();
		cin >> command;
		cout << endl;

		if (command == 3)
		{
			//break;
			time_analysis<int>();
		}

		else if (command == 1 || command == 2)
		{
			Matrix<int> M1;
			Matrix<int> M2;
			M1.input_matrix();
			M1.output_matrix();
			M2.input_matrix();
			M1.output_matrix();
			if (command == 1)
			{
				Matrix<int> result(M1.classic_sum(M2));
				cout << "\n RES:\n";
				result.output_matrix();
			}

			else if (command == 2)
			{
				cout << "Input number of threads: ";
				cin >> threads;
				cout << endl;

				Matrix<int> result(parallel_sum(M1, M2, threads));
				cout << "\n RES:\n";
				result.output_matrix();
			}
		}
	}

	return 0;
}