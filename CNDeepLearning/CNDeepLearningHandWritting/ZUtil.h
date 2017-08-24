#pragma once


#include <iostream>
#include<cmath>
#include <vector>
#include "Tensor.h"


template<typename T = float>
void UpdateWeight(Tensor<T>& newweight, const Tensor<T>& weight, const Tensor<T>& a, const T learningrate = 0.5)
{
	for (int i = 0; i < weight._shape.row; i++)
	{
		for (int j = 0; j < weight._shape.column; j++)
		{

			newweight._data[i*weight._shape.column + j] =
				weight._data[i*weight._shape.column + j] -
				learningrate*a._data[i*weight._shape.column + j];
		}
	}
}
template<typename T = float>
void GenerateOutMatrix( Tensor<T>& newweight, const Tensor<T>& out_o, 
	                   const Tensor<T>& out_h)
{
	for (int i = 0; i < newweight._shape.row; i++)
	{
		for (int j = 0; j < newweight._shape.column; j++)
		{

			newweight._data[i*newweight._shape.column + j] =
				out_o._data[j % newweight._shape.column] * out_h._data[i % newweight._shape.column];
		}
	}
}
template<typename T = float>
void GenerateEoutMatrix(Tensor<T>& newweight, const Tensor<T>& out_o,
	const Tensor<T>& weight)
{
	for (int i = 0; i < newweight._shape.row; i++)
	{
		for (int j = 0; j < newweight._shape.column; j++)
		{

			newweight._data[i*newweight._shape.column + j] =
				out_o._data[j % newweight._shape.column] * weight._data[i*newweight._shape.column + j];
		}
	}
}
template<typename T = float>
void TensorReduce(Tensor<T>& result,const Tensor<T>& mat)
{
	for (int i = 0; i < mat._shape.row; i++)
	{
		for (int j = 0; j < mat._shape.column; j++)
		{

			result._data[i] +=
				mat._data[i*mat._shape.column + j];
		}
	}
}

inline double random(double start, double end)
{
	return  ((double)rand() / RAND_MAX)*(end - start) + start;
}
inline int random(int start, int end)
{
	return  (rand() % (end - start + 1)) + start;
}
