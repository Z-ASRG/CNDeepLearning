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

		Tensor m_WeightGrad;
		Tensor m_BiasGrad;

		Shape m_KernelShape;
	public:
		FullyConnectedLayer(const Shape &KernelShape)
			:NeuralLayer(), m_KernelShape(KernelShape)
		{
		};
		~FullyConnectedLayer()
		{
		};

		void Create()
		{
			//Set weight and bias
			m_Weight.Reshape(Shape(m_KernelShape.width, m_KernelShape.height, m_KernelShape.depth, 1));
			m_Bias.Reshape(Shape(1, 1, m_KernelShape.depth, 1));


			//Set grad
			m_WeightGrad.Reshape(m_Weight.GetShape());
			m_BiasGrad.Reshape(m_Bias.GetShape());

			//Set random number

			//Set zero
			m_WeightGrad.Set(0.0);
			m_BiasGrad.Set(0.0);
		};
		void Destory()
		{
		};

		//Calc output
		void Forward(const Tensor& InTensor)
		{
			m_Output.Set(0.0);
			//m_Output
		};

		//Calc grad
		void Backward(const Tensor& OutTensor)
		{
		};

		//Update weight
		void UpdateWeight(const Tensor& OutTensor)
		{
			m_Weight.Add(m_WeightGrad);
			m_Bias.Add(m_BiasGrad);
		};

		void Reshape(const Shape &InputShape)
		{
			m_OutputShape = Shape(1, 1, InputShape.Volume(), InputShape.batch);
			static_cast<NeuralLayer*>(this)->Reshape();
		};
	};

}

#endif