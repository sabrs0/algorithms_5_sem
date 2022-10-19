#include "Matrix.h"
template<typename T>
Matrix<T>::Matrix()
{
	this->M = 0;
	this->N = 0;
	this->data = nullptr;

	//std::cout << "\nMatrix contructor usual for " << this << std::endl;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>&M_)
{
	this->M = M_.M;
	this->N = M_.N;
	this->data.reset(new std::shared_ptr<T[]>[this->M]);
	for (int i = 0; i < M; i++)
	{
		this->data[i].reset(new T[N]);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			this->data[i][j] = M_.data[i][j];
		}
	}
	//std::cout << "\nMatrix COPY contructor for " << this << std::endl;
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
	this->data.reset(new std::shared_ptr<T[]>[M]);
	for (int i = 0; i < M; i++)
	{
		this->data[i].reset(new T[N]);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			data[i][j] = 0;
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
	this->data.reset(new std::shared_ptr<T[]>[M]);
	for (int i = 0; i < M; i++)
	{
		this->data[i].reset(new T[N]);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> data[i][j];
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
Matrix<T> Matrix<T>::classic_mult( const Matrix<T>& M2)
{
	Matrix<T> res(this->M, M2.N);
	int K = this->N;
	for (int i = 0; i < res.M; i++)
	{
		for (int j = 0; j < res.N; j++)
		{
			for (int k = 0; k < K; k++)
			{
				res.data[i][j] = res.data[i][j] + (this->data[i][k] * M2.data[k][j]);
			}
		}
	}
	return res;

}
template <typename T>
Matrix<T> rows_sum_matr(Matrix<T> matr, int M_, int C_)
{
	C_ = C_ / 2;
	Matrix<T> c_matr(M_, C_);
	for (int i = 0; i < M_; i++)
	{
		for (int j = 0; j < C_; j++)
		{
			c_matr.data[i][j] = c_matr.data[i][j] + matr.data[i][j * 2] * matr.data[i][j * 2 + 1];
		}
	}
	return c_matr;
}template <typename T>
Matrix<T> cols_sum_matr(Matrix<T> matr, int C_, int N_)
{
	C_ = C_ / 2;
	Matrix<T> c_matr(C_, N_);
	for (int i = 0; i < C_; i++)
	{
		for (int j = 0; j < N_; j++)
		{
			c_matr.data[i][j] += matr.data[i * 2][j] * matr.data[i * 2 + 1][j];
		}
	}
	return c_matr;
}
template <typename T>
Matrix<T>  Matrix<T>::Vinograd_mult(const Matrix<T>& M2)
{
	int C = this->N;
	Matrix<T> c_matr(this->M, M2.N);
	Matrix<T> matr_r = rows_sum_matr(*this, this->M, C);
	Matrix<T> matr_c = cols_sum_matr(M2, C, M2.N);
	for (int i = 0; i < c_matr.M; i++)
	{
		for (int j = 0; j < c_matr.N; j++)
		{
			for (int k = 0; k < (C / 2); k++)
			{
				c_matr.data[i][j] += ((this->data[i][k * 2] + M2.data[k * 2 + 1][j]) * (this->data[i][k * 2 + 1] + M2.data[k * 2][j]) - matr_r.data[i][k] - matr_c.data[k][j]);
			}
		}
	}
	if (C % 2 != 0)
	{
		for (int i = 0; i < c_matr.M; i++)
		{
			for (int j = 0; j < c_matr.N; j++)
			{
				c_matr.data[i][j] += this->data[i][C - 1] * M2.data[C - 1][j];
			}
		}
	}
	return c_matr;
}
template <typename T>
std::shared_ptr<T[]> rows_sum_matr_opt(Matrix<T> matr, int M_, int C_)
{
	std::shared_ptr<T[]> row_(new T[M_]());
	for (int i = 0; i < M_; i++)
	{
		for (int j = 0; j < C_ - 1; j += 2)
		{
			row_[i] +=  matr.data[i][j] * matr.data[i][j + 1];
		}
	}
	return row_;
}template <typename T>
std::shared_ptr<T[]> cols_sum_matr_opt(Matrix<T> matr, int C_, int N_)
{
	std::shared_ptr<T[]> col_(new T[N_]());
	for (int i = 0; i < C_ - 1; i += 2)
	{
		for (int j = 0; j < N_; j++)
		{
			col_[j] += matr.data[i][j] * matr.data[i + 1][j];
		}
	}
	return col_;
}
template <typename T>
Matrix<T>  Matrix<T>::Vinograd_mult_opt(const Matrix<T>& M2)
{
	int C = this->N;
	Matrix<T> c_matr(this->M, M2.N);
	std::shared_ptr<T[]> arr_r = rows_sum_matr_opt(*this, this->M, C);
	std::shared_ptr<T[]> arr_c = cols_sum_matr_opt(M2, C, M2.N);
	for (int i = 0; i < c_matr.M; i++)
	{
		for (int j = 0; j < c_matr.N; j++)
		{
			c_matr.data[i][j] = -arr_r[i] - arr_c[j];
			for (int k = 0; k < C - 1; k += 2)
			{
				c_matr.data[i][j] += (this->data[i][k] + M2.data[k+ 1][j]) * (this->data[i][k + 1] + M2.data[k][j]);
			}
		}
	}
	if (C % 2 != 0)
	{
		for (int i = 0; i < c_matr.M; i++)
		{
			for (int j = 0; j < c_matr.N; j++)
			{
				c_matr.data[i][j] += this->data[i][C - 1] * M2.data[C - 1][j];
			}
		}
	}
	return c_matr;
}

