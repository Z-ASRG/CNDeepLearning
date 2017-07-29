#pragma once
#include "Tensor.h"
#include "NeuralPerception.h"
#include "Layer.h"

template<typename T = float>
class HiddenLayer :public Layer<T>
{
public:
	HiddenLayer(int row, int column)
		:Layer(row,column),bias(row,column)
	{}

	Tensor<T> weight;
	Tensor<T> bias;

public:
	virtual void forward()
	{
		parent->output_value.mat_multi(this->output_value, this->weight);
		this->output_value.mat_add(this->output_value, bias);
		this->interceptor.sigmoid(this->output_value);
	}
	virtual void backward()
	{
		vector<T> e;
		
		for (int r = 0; r < this->child->bgweight._shape.row; r++)//Êä³öµãÊý
		{
			T net_wi = 0;
			for (int c = 0; c < this->child->bgweight._shape.column; c++)
			{
				net_wi += this->child->net_value._data[c] *
					this->child->bgweight._data[r*this->child->bgweight._shape.column + c];
			}
			e.push_back(net_wi);
		}
		this->bgweight = this->weight;
		for (int r = 0; r < this->weight._shape.row; r++)
		{
			for (int c = 0; c < this->weight._shape.column; c++)
			{
				
				this->weight._data[r*this->weight._shape.column+c]
					=(this->parent->output_value._data[r]                             
					* this->output_value._data[c]*(1- this->output_value._data[c])    //out_h1(1-out_h1)
					*e[c])
					*this->learning_rate*(-1)+ this->weight._data[r*this->weight._shape.column + c]
					;
				//-0.3*this->weight._data[r*this->weight._shape.column + c]
			}
		}
		////update bias
		for (int i = 0; i < this->bias._data.size(); i++)
		{
			this->bias._data[i] = (this->bias._data[i]
				* this->output_value._data[i] * (1 - this->output_value._data[i])
				*e[i])
				*this->learning_rate*(-1) + this->bias._data[i];
		}


		//Tensor<double> Eo1_out(2, 2), E_total(1, 2);
		//GenerateEoutMatrix(Eo1_out, this->child->net_value,
		//	this->child->bgweight);//(out-target)*out*(1-out)  * wi
		//TensorReduce(E_total, Eo1_out);

		//Tensor<double> pout_h(1, 2);

		//this->output_value.mat_minus_(pout_h, 1);
		//pout_h.mat_dot(pout_h, this->output_value);

		//pout_h.mat_dot(pout_h, E_total);
		//Tensor<double> ooo(this->parent->output_value._shape.column ,
		//	this->output_value._shape.column);
		//GenerateOutMatrix(ooo, pout_h, this->parent->output_value);
		//this->bgweight = this->weight;
		//UpdateWeight(this->weight, this->weight, ooo);

	}
};