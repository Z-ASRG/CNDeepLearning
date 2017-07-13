#pragma once
#include <iostream>
#include "NetworkContext.h"
#include "Tensor.h"

namespace ASRG
{
	class NetworkFramework
	{
	public:
		NetworkFramework();
		~NetworkFramework();
		void init();
		void run();
		void clear();

	protected:
		NetworkContext m_Context;

		void forward();
		void backward();
	private:
		double Sigmoid(double x)
		{
			double result = 1.0 / (1.0 + exp(-x));
			return result;
		}
		void test();

		Tensor input, h1_weight, h2_weight, b, b2, Target, E_total;
		Tensor  outh, outo;
		float learning_rate;
		float e_total;
	};

}

