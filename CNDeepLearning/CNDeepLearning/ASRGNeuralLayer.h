#pragma once

#ifndef __NEURALLAYER_H__
#define __NEURALLAYER_H__

#include "Util.h"
#include "Shape.h"
#include "Tensor.h"

using namespace std;

namespace ASRG
{

		class ASRGNeuralLayer
		{
		protected:
			Tensor m_Output;
			Tensor m_Diff;

			Shape m_InputShape;
			Shape m_OutputShape;
		//protected:
			//virtual Shape _CalcOutputShape(const Shape &InShape) const { return InShape; };
		public:
			ASRGNeuralLayer() {};
			~ASRGNeuralLayer() {};

			virtual void Forward(const Tensor& InTensor) = 0;
			virtual void Backward(const Tensor& OutTensor) = 0;

			virtual void InitKernel() = 0;
			virtual void Destory() = 0;
		};

}

#endif