#pragma once

#ifndef __NEURALLAYER_H__
#define __NEURALLAYER_H__

#include "Util.h"
#include "Shape.h"

using namespace std;

namespace ASRG
{
	namespace ML
	{
		class Tensor;
		
		class NeuralLayer
		{
		private:
			vector<float32> m_Weight;
			vector<float32> m_Bias;

			Shape m_InputShape;
			Shape m_OutputShape;
		public:
			NeuralLayer();
			~NeuralLayer();

			virtual void Forward() = 0;
			virtual void Backward() = 0;

			virtual void Resize();
		};
	}
}

#endif