#pragma once

#ifndef __LOGISTICLAYER_H__
#define __LOGISTICLAYER_H__

#include "NeuralLayer.h"

namespace ASRG
{
	namespace ML
	{
		class LogisticLayer : public NeuralLayer
		{
		protected:
		public:
			LogisticLayer(const Shape &InShape)
				:NeuralLayer()
			{
			};
			~LogisticLayer()
			{

			};

			void Forward(const Tensor<float32> &InTensor) override
			{

			};
			void Backward(const Tensor<float32> &OutTensor) override
			{

			};

			void InitKernel() override
			{
			};
			void Destory() override
			{
			};
		};
	}
}

#endif