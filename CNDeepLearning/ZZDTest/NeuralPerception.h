#pragma once
#include "Tensor.h"

template<typename T = double>
class NeuralPerception
{
public:
	virtual void sigmoid(Tensor<T>& mat)
	{
		for (int i = 0; i < mat._shape.row; i++)
		{
			for (int j = 0; j < mat._shape.column; j++)
			{
				mat._data[i*mat._shape.row + j] = this->_sigmoid(mat._data[i*mat._shape.row + j]);
			}
		}
	}
private:
	T _sigmoid(T num)
	{
		T result = 1.0 / (1.0 + exp(-num));
		return result;
	}
};

