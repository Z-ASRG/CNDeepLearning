#pragma once

#ifndef __FULLYCONNECTEDLAYER_H__
#define __FULLYCONNECTEDLAYER_H__

#include "NeuralLayer.h"

namespace ASRG
{
	class FullyConnectedLayer : public NeuralLayer
	{
	protected:
		Tensor m_Weight;
		Tensor m_Bias;

		Shape m_KernelShape;
	public:
		FullyConnectedLayer(const Shape &KernelShape)
			:NeuralLayer(), m_KernelShape(KernelShape)
		{
		};
		~FullyConnectedLayer()
		{
		};

		void Create()
		{
		};
		void Destory()
		{
		};

		void Forward(const Tensor& InTensor)
		{
		};
		void Backward(const Tensor& OutTensor)
		{
		};

		void UpdateWeight(const Tensor& OutTensor)
		{
		};

		void Reshape(const Shape &InputShape)
		{
			m_OutputShape = Shape(1, 1, InputShape.Volume(), InputShape.batch);
			Reshape();
		};
	};

}

#endif