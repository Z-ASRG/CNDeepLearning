#pragma once

#ifndef __NEURALLAYER_H__
#define __NEURALLAYER_H__

#include "Util.h"
#include "Shape.h"
#include "Tensor.h"

using namespace std;

namespace ASRG
{
	class NeuralLayer
	{
	protected:
		//Layer output
		Tensor m_Output;
		Shape m_OutputShape;

		//Layer backward error
		Tensor m_Diff;
		Shape m_InputShape;

		//protected:
		//virtual Shape _CalcOutputShape(const Shape &InShape) const { return InShape; };
	public:
		NeuralLayer()
		{
		};
		~NeuralLayer() {};

		virtual void Create() = 0;
		virtual void Destory() = 0;

		virtual void Forward(const Tensor& InTensor) = 0;
		virtual void Backward(const Tensor& OutTensor) = 0;

		virtual void UpdateWeight(const Tensor& OutTensor) = 0;

		virtual void Reshape(const Shape &InputShape) = 0;

		void Reshape()
		{
			//Reshape output, diff tensor
			m_Output.Reshape(m_OutputShape);
			m_Diff.Reshape(m_InputShape);
		};
	};

}

#endif