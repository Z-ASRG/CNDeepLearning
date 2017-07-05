#pragma once

#ifndef __NEURALLAYER_H__
#define __NEURALLAYER_H__

#include "Util.h"
#include "Shape.h"
#include "Tensor.h"

using namespace std;

namespace ASRG
{
	namespace ML
	{
		class NeuralLayer
		{
		protected:
			Tensor<float32> m_Output;
			Tensor<float32> m_Diff;

			Shape m_InputShape;
			Shape m_OutputShape;
		//protected:
			//virtual Shape _CalcOutputShape(const Shape &InShape) const { return InShape; };
		public:
			NeuralLayer() {};
			~NeuralLayer() {};

			virtual void Forward(const Tensor<float32> &InTensor) = 0;
			virtual void Backward(const Tensor<float32> &OutTensor) = 0;

			virtual void InitKernel() = 0;
			virtual void Destory() = 0;
		};
	}
}

#endif