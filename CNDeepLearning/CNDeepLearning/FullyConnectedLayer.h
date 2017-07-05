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
		FullyConnectedLayer(const Shape &InShape, const Shape &KernelShape)
			:NeuralLayer()
		{

		};
		~FullyConnectedLayer()
		{

		};

		void Forward(const Tensor &InTensor) override
		{

		};
		void Backward(const Tensor &OutTensor) override
		{

		};

		void InitKernel() override;
		void Destory() override;
	};

}

#endif