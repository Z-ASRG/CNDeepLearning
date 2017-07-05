#pragma once

#ifndef __FULLYCONNECTEDLAYER_H__
#define __FULLYCONNECTEDLAYER_H__

#include "NeuralLayer.h"

namespace ASRG
{
	namespace ML
	{
		class FullyConnectedLayer : public NeuralLayer
		{
		protected:
			Tensor<float32> m_Weight;
			Tensor<float32> m_Bias;

			Shape m_KernelShape;
		public:
			FullyConnectedLayer(const Shape &InShape, const Shape &KernelShape)
				:NeuralLayer()
			{

			};
			~FullyConnectedLayer()
			{

			};

			void Forward(const Tensor<float32> &InTensor) override
			{

			};
			void Backward(const Tensor<float32> &OutTensor) override
			{

			};

			void InitKernel() override;
			void Destory() override;
		};
	}
}

#endif