#pragma once

#ifndef __LOGISTICLAYER_H__
#define __LOGISTICLAYER_H__

#include "ASRGNeuralLayer.h"

namespace ASRG
{

		class CNLogisticLayer : public CNNeuralLayer
		{
		protected:
		public:
			CNLogisticLayer(const Shape &InShape)
				:CNNeuralLayer()
			{
			};
			~CNLogisticLayer()
			{

			};

			void Forward(const Tensor &InTensor) override
			{

			};
			void Backward(const Tensor &OutTensor) override
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

#endif