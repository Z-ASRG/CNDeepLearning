#pragma once
#include "Tensor.h"
#include "NeuralPerception.h"
#include <iostream>
using namespace std;

template<typename T=double>
class Layer
{
public:
	Layer(int row,int column,T learningRate=0.5) :child(NULL), parent(NULL),
		learning_rate(learningRate),
		output_value(row, column), net_value(row, column)
	{}

	Tensor<T> output_value;
	Tensor<T> net_value;
	Tensor<T> bgweight;

	Layer<T>* child;
	Layer<T>* parent;
	T learning_rate;

	virtual void forward() = 0;
	virtual void backward() = 0;

	NeuralPerception<T> interceptor;
};
