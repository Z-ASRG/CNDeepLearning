#pragma once

#include "NeuralLayer.h"

namespace ASRG
{
	class InputLayer :public NeuralLayer
	{
	public:
		virtual void Forward(const Tensor& InTensor) override
		{
			
		}


		virtual void Backward(const Tensor& OutTensor) override
		{
			
		}

	};
}