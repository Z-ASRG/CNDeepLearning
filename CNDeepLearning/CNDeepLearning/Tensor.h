#pragma once

#ifndef __TENSOR_H__
#define __TENSOR_H__

#include "Shape.h"
using namespace std;

namespace ASRG
{
	namespace ML
	{
		template<class _Data>
		class Tensor
		{
		private:
			vector<_Data> m_HostBuffer;
			Shape m_Shape;
		public:
			Tensor();
			~Tensor();

			//...
		};
	}
}

#endif