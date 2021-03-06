#include "stdafx.h"
#include <stdio.h>

template<unsigned columns, unsigned rows, class matrix_t>
class Matrix;

template<class matrix_t>
struct Matrix<0, 0, matrix_t>;

template<unsigned columns, class matrix_t>
struct Matrix<columns, 0, matrix_t>;

template<class matrix_t>
struct Matrix<0, 1, matrix_t>;

template<unsigned rows, class matrix_t>
using RowMatrix = Matrix<rows, 1, matrix_t>;

template<unsigned columns, class matrix_t>
using ColumnMatrix = Matrix<1, columns, matrix_t>;

template<unsigned rows, unsigned columns, class matrix_t>
using SquareMatrix = Matrix<rows, columns, matrix_t>;

template<unsigned rows>
struct Matrix<rows, 1, float> {
public:
	Matrix() {};

	Matrix(float args[rows]) {
		for (unsigned i = 0; i < rows; ++i) {
			values_[i] = args[rows];
		}
	}

	Matrix operator+(Matrix j) {
		Matrix r;

		for (unsigned i = 0; i < this->Rows; ++i) {
			r[i] = this->values_[i] + j[i];
		}

		return r;
	}

	inline float& operator[](unsigned i) {
		return this->values_[i];
	}

	static constexpr size_t Rows = rows;
	static constexpr size_t Cols = 1;
	static constexpr size_t elements = rows * Cols;

private:
	float values_[rows];
};

template<unsigned rows, unsigned columns, typename matrix_t>
struct Matrix {
public:
	Matrix() {};

	 

	Matrix(matrix_t initial_value) {
		for_each_cell([&](matrix_t& r) { r = initial_value; });
	}

	Matrix operator+(Matrix j) {
		Matrix result;
		for (unsigned c = 0; c < this->Cols; ++c){
			for (unsigned r = 0; r < this->Rows; ++r) {
				result[c][r] = this->values_[c][r] + j[c][r];
			}
		}
		return result;
	}

	inline RowMatrix<rows, matrix_t>& operator[](unsigned i) {
		return this->values_[i];
	}

	static constexpr size_t Rows = rows;
	static constexpr size_t Cols = columns;
	static constexpr size_t elements = rows * columns;

private:
	template<typename fn_t>
	inline void for_each_cell(fn_t fn) {
		for (unsigned r = 0; r < this->Cols; ++r) {
			for (unsigned c = 0; c < this->Rows; ++c) {
				fn(values_[r][c]);
			}
		}
	}

	ColumnMatrix<columns, matrix_t> values_[rows];
};



template<unsigned r, typename matrix_t>
void print_row(RowMatrix<r, matrix_t> m) {
		for (int ri = 0; ri < m.Rows; ++ri) {
			if(ri+1 != m.Rows) { printf("[1][%u]: %f ", ri+1,m[ri]); }
			else { printf("[1][%u]: %f\n", ri+1, m[ri]); }
		}
}

template<unsigned c, unsigned r, typename matrix_t>
void print_matrix(Matrix<c, r, matrix_t> m) {
	for (int ci = 0; ci < m.Cols; ++ci) {
		for (int ri = 0; ri < m.Rows; ++ri) {
			if (ri + 1 != m.Rows) { printf("[%u][%u]: %f ", ci+1, ri+1, m[ci][ri]); }
			else { printf("[%u][%u]: %f\n", ci+1, ri+1, m[ci][ri]); }
		}
	}
}

inline void ln() {
	printf("\n");
}

int main() {

	Matrix<2, 3, float> s, y;

	s[0][0] = 1, s[1][0] = 3, s[2][0] = 1;
	s[0][1] = 1, s[1][1] = 0, s[2][1] = 1;

	y[0][0] = 0, y[1][0] = 0, y[2][0] = 5;
	y[0][1] = 7, y[1][1] = 5, y[2][1] = 0;

	auto r_x = s + y;
	print_matrix(r_x);
	ln();
	getchar();
	//just here to coerce machine code
}