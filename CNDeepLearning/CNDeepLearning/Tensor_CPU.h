#pragma once

#ifndef __TENSORCPU_H__
#define __TENSORCPU_H__

#include "Util.h"
#include "Shape.h"

using namespace std;

namespace ASRG
{
	class Tensor_CPU
	{
	private:
		vector<float32> m_Data;
		Shape m_Shape;
	public:
		Tensor_CPU(const Shape &TensorShape = Shape(), float32 Val = 0.0);
		Tensor_CPU(const Tensor_CPU &T);
		~Tensor_CPU() {};

		Tensor_CPU& operator=(const Tensor_CPU &T);

		//operator overload
		const float32& operator[](const uint32 ID) const;
		float32& operator[](const uint32 ID);

		//Set tensor value
		void Set(const float32 Val);
		void Set(const vector<float32> &Vec);

		//Get tensor value
		const float32& At(const uint32 ID) const;
		const float32& At(const uint32 Row, const uint32 Col, const uint32 Channel, const uint32 Batch) const;

		float32& At(const uint32 ID);
		float32& At(const uint32 Row, const uint32 Col, const uint32 Channel, const uint32 Batch);

		void Reshape(const Shape &TensorShape);

		//Math related function
		void Add(const float32 Val);
		void Add(const Tensor_CPU &T, const bool bPerBatch = false);

		void Sub(const float32 Val);
		void Sub(const Tensor_CPU &T, const bool bPerBatch = false);

		void Mul(const float32 Val);
		void Mul(const Tensor_CPU &T, const bool bPerBatch = false);

		void Pow(const float32 Val);
		void Exp();

		//Get shape
		const Shape GetShape() const;
	};

	typedef Tensor_CPU Tensor;
}

#endif