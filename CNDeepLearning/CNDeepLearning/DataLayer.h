#pragma once

#ifndef __DATALAYER_H__
#define __DATALAYER_H__

#include "NeuralLayer.h"

namespace ASRG
{
	class DataLayer : public NeuralLayer
	{
	public:
		DataLayer(const Shape &KernelShape)
			:NeuralLayer()
		{
		};
		~DataLayer()
		{
		};

		void Create()
		{
		};
		void Destory()
		{
		};

		//Calc output
		void Forward(const Tensor& InTensor)
		{
			m_Output = InTensor;
		};

		//Calc grad
		void Backward(const Tensor& OutTensor)
		{
		};

		//Update weight
		void UpdateWeight(const Tensor& OutTensor)
		{
		};

		void Reshape(const Shape &InputShape)
		{
			m_OutputShape = InputShape;
			static_cast<NeuralLayer*>(this)->Reshape();
		};
	};

}

#endif