#pragma once
#include <amp.h>  
#include <amp_math.h>
#include <iostream>  
using namespace std;
using namespace concurrency;

inline void mat_multiplyNN(index<2> idx,
	concurrency::array<int, 2>& product,
	concurrency::array<int, 2>& a,
	concurrency::array<int, 2>& b) restrict(amp)
{
	int row = idx[0];
	int col = idx[1];
	for (int inner = 0; inner < 2; inner++) {
		product[idx] += a(row, inner)* b(inner, col);

	}
}

inline void mat_multiplyFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a,
	concurrency::array<float, 2>& b) restrict(amp)
{
	int row = idx[0];//[0]
	int col = idx[1];//[0,1]
	product[idx] = 0;
	for (int cj = 0; cj < product.extent[1]; cj++)
	{
		product[idx] += a(row, cj)*b(cj, col);        //tested correct!

	}

}
inline void addFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a,
	concurrency::array<float, 2>& b) restrict(amp)
{
	product[idx] = a[idx] + b[idx];
}
inline void minusFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a,
	concurrency::array<float, 2>& b) restrict(amp)
{
	product[idx] = a[idx] - b[idx];
}
inline void minusFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a,
	float b) restrict(amp)
{
	product[idx] = a[idx] - b;
}
inline void minusFF(index<2> idx,
	concurrency::array<float, 2>& product,
	float a,
	concurrency::array<float, 2>& b) restrict(amp)
{
	product[idx] = a - b[idx];
}
inline void dotFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a,
	float b) restrict(amp)
{
	product[idx] = a[idx] * b;
}
inline void dotFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a,
	concurrency::array<float, 2>& b) restrict(amp)
{
	product[idx] = a[idx] * b[idx];
}
inline void sigmoidFF(index<2> idx,
	concurrency::array<float, 2>& product,
	concurrency::array<float, 2>& a) restrict(amp)
{
	product[idx] = 1.0f / (1.0f + fast_math::exp(-1 * a(idx)));
}
inline float map_reduce(concurrency::array_view<float, 2>& mvector)
{
	float sum = 0.0;
	for (int row = 0; row < mvector.extent[0]; row++) {
		for (int col = 0; col < mvector.extent[1]; col++) {
			sum += mvector(row, col);
		}
	}
	return sum;
}

inline void expandTensor(concurrency::array<float, 2>& source,concurrency::array<float,2>& dest)
{
	std::vector<float> temp;
	for (int row = 0; row < source.extent[0]; row++) {
		for (int col = 0; col < source.extent[1]; col++) {
			temp.push_back(source(row,col));
		}
	}

	dest = concurrency::array<float, 2>(2,2,temp.data());

}


inline void print(concurrency::array<float, 2>& z)
{
	for (int row = 0; row < z.extent[0]; row++) {
		for (int col = 0; col < z.extent[1]; col++) {
			//std::cout <<productMatrix[row*3 + col] <<"  ";  
			std::cout << z(row, col) << "  ";
		}
		std::cout << "\n";
	}
}