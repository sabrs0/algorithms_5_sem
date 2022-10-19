#include <iostream>
#include <memory>
#include <exception>

template<class T>
class Matrix
{
public:
	int M;
	int N;
	std::shared_ptr<std::shared_ptr<T[]>[]> data;
	Matrix();
	Matrix(const Matrix<T>&M_);

	Matrix(int M_, int N_);
	
	
	Matrix<T> classic_mult(const  Matrix<T> &M2);


	Matrix<T>  Vinograd_mult(const Matrix<T>& M2);

	Matrix<T>  Vinograd_mult_opt(const Matrix<T>& M2);
	
	~Matrix<T>();

	Matrix<T>& input_matrix();

	void output_matrix();

};
template<class T>
Matrix<T> fill_rand_matrix(int M, int N);
