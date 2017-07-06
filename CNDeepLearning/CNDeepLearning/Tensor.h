#pragma once

#ifndef __TENSORCPU_H__
#define __TENSORCPU_H__

#include "Util.h"
#include "Shape.h"

using namespace std;

namespace ASRG
{
	class Tensor
	{
	private:
		vector<float32> m_Data;
		Shape m_Shape;
	public:
		Tensor(const Shape &TensorShape, float32 Val)
			:m_Data(TensorShape.Size(), Val), m_Shape(TensorShape)
		{
		};
		Tensor(const Tensor &T)
			:m_Data(T.m_Data), m_Shape(T.m_Shape)
		{
		};
		~Tensor() {};

		Tensor& operator=(const Tensor &T)
		{
			m_Data = T.m_Data;
			m_Shape = T.m_Shape;

			return *this;
		};
	public:
		//operator overload
		const float32& operator[](const uint32 ID) const
		{
			return At(ID);
		};
		float32& operator[](const uint32 ID)
		{
			return At(ID);
		};

		//Set tensor value
		void Set(const float32 Val)
		{
			for (auto &D : m_Data) { D = Val; }
		};
		void Set(const vector<float32> &Vec)
		{
			const uint32 Size = min(m_Shape.Size(), Vec.size());

			for (uint32 seek = 0; seek < Size; seek++)
			{
				m_Data[seek] = Vec[seek];
			}
		};

		//Get tensor value
		const float32& At(const uint32 ID) const
		{
			return m_Data[ID];
		};
		const float32& At(const uint32 Row, const uint32 Col, const uint32 Channel, const uint32 Batch) const
		{
			uint32 ID = Batch * m_Shape.Volume() + Channel * m_Shape.Resolution() + Row * m_Shape.width + Col;
			return At(ID);
		};

		float32& At(const uint32 ID)
		{
			return m_Data[ID];
		};
		float32& At(const uint32 Row, const uint32 Col, const uint32 Channel, const uint32 Batch)
		{
			uint32 ID = Batch * m_Shape.Volume() + Channel * m_Shape.Resolution() + Row * m_Shape.width + Col;
			return At(ID);
		};

		void Reshape(const Shape &TensorShape)
		{
			m_Data.resize(TensorShape.Size());
			m_Shape = TensorShape;
		};

		//Math related function
		void Add(const float32 Val)
		{
			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = m_Data[seek] + Val;
				}
			}
		};
		void Add(const Tensor &T)
		{
			if (m_Shape != T.m_Shape) { return; }

			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = m_Data[seek] + T[seek];
				}
			}
		};

		void Sub(const float32 Val)
		{
			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = m_Data[seek] - Val;
				}
			}
		};
		void Sub(const Tensor &T)
		{
			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = m_Data[seek] - T[seek];
				}
			}
		};

		void Mul(const float32 Val)
		{
			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = m_Data[seek] * Val;
				}
			}
		};
		void Mul(const Tensor &T)
		{
			if (m_Shape != T.m_Shape) { return; }

			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = m_Data[seek] * T[seek];
				}
			}
		};

		void Pow(const float32 Val)
		{
			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = pow(m_Data[seek], Val);
				}
			}
		};
		void Exp()
		{
			const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
			for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
			{
				uint32 Index = seek_batch * VolumeSize;

				for (int seek = 0; seek < VolumeSize; seek++)
				{
					m_Data[seek] = exp(m_Data[seek]);
				}
			}
		};
	};
}

#endif