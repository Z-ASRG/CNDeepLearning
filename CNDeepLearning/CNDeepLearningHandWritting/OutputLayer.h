#pragma once
#include "Tensor.h"
#include "NeuralPerception.h"
#include "Layer.h"

template<typename T = float>
class OutputLayer : public Layer<T>
{
public:
	OutputLayer(int row, int column) :Layer(row,column), error(row, column) {}

	virtual void forward()
	{
		parent->output_value.mat_multi(this->output_value, this->weight);
		this->output_value.mat_add(this->output_value, bias);
		this->interceptor.sigmoid(this->output_value);
	};
	virtual void backward()
	{
		Tensor<T> temp(this->output_value._shape.row, this->output_value._shape.column);
		this->output_value.mat_minus(temp, target);//-(target_o1-out_o1)
		this->output_value.mat_minus_(this->net_value, 1);//1-out_o1
		this->output_value.mat_dot(this->net_value, this->net_value);//out_o1(1-out_o1)
		temp.mat_dot(this->net_value, this->net_value);

		Tensor<T> reout(parent->output_value._shape.column, this->output_value._shape.column);
		GenerateOutMatrix(reout, this->net_value, parent->output_value);
		this->bgweight = this->weight;
		UpdateWeight(this->weight, this->weight, reout, this->learning_rate);//wi - n*e_wi

		//update bias
		for (int i = 0; i < this->bias._data.size(); i++)
		{
			this->bias._data[i] = this->bias._data[i] - this->learning_rate*this->net_value._data[i];
		}

	};
	virtual void caculateError()
	{
		target.mat_minus(error, this->output_value);
		error.mat_dot(error, error);
		error.mat_dot(error, 0.5);
	}
	virtual void showError()
	{
		std::cout << "Target : ";
		for (int i = 0; i < this->target._data.size(); i++)
		{
			std::cout << this->target._data[i] << "  ";
		}
		std::cout << std::endl;
		std::cout << "Output : ";
		for (int i = 0; i < this->output_value._data.size(); i++)
		{
			std::cout<<this->output_value._data[i]<<"  ";
		}
		std::cout << std::endl;
		std::cout << "Output Error: ";
		error.print();
		std::cout << std::endl;
		T sum = 0;
		for (int i = 0; i < error._data.size(); i++)
		{
			sum += error._data[i];
		}
		std::cout << "Total Error: " << sum << std::endl;
	}
	virtual T getError()
	{
		T sum = 0;
		for (int i = 0; i < error._data.size(); i++)
		{
			sum += error._data[i];
		}
		return sum;
	}
	virtual T getError(int i)
	{
		return error._data[i];
	}
public:
	Tensor<T> weight;
	Tensor<T> bias;
	Tensor<T> target;
	Tensor<T> error;
};