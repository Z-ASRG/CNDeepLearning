#pragma once

#ifndef __LOGISTICLAYER_H__
#define __LOGISTICLAYER_H__

#include "NeuralLayer.h"

namespace ASRG
{
	class LogisticLayer : public NeuralLayer
	{
	public:
		LogisticLayer(const Shape &InShape)
			:NeuralLayer()
		{
		};
		~LogisticLayer()
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
			//sigmoid val = 1.0 / (1.0 + e^(-x))
			m_Output = InTensor;

			m_Output.Mul(-1);
			m_Output.Exp();
			m_Output.Add(1.0);
			m_Output.Pow(-1);
		};
		void Backward(const Tensor& OutTensor)
		{

		};

		void UpdateWeight(const Tensor& OutTensor)
		{
		};

		void Reshape(const Shape &InputShape)
		{
			m_OutputShape = InputShape;
		};
	};
}

#endif