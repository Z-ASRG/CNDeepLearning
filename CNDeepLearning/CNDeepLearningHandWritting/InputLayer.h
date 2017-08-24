#pragma once
#include <iostream>
#include "Layer.h"
using namespace std;

template<class T>
class InputLayer :public Layer<T>
{
public:
	InputLayer(int row, int column) :Layer(row,column)
	{}
	virtual void forward()
	{};
	virtual void backward()
	{};
	virtual void showInput()
	{
		std::cout << "Input : ";
		for (int i = 0; i < this->output_value._data.size(); i++)
		{
			std::cout << this->output_value._data[i] << "  ";
		}
		std::cout << std::endl;

	}
};
