#pragma once

#ifndef __LOGISTICLAYER_H__
#define __LOGISTICLAYER_H__

#include "NeuralLayer.h"

namespace ASRG
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

		void Forward(const Tensor& InTensor) override
		{

		};
		void Backward(const Tensor& OutTensor) override
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