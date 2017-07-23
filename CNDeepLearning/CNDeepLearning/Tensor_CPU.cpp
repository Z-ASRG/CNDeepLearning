#include "Tensor_CPU.h"

using namespace ASRG;

const float32& Tensor_CPU::operator[](const uint32 ID) const
{
	return At(ID);
}
float32& Tensor_CPU::operator[](const uint32 ID)
{
	return At(ID);
}
void Tensor_CPU::Set(const float32 Val)
{
	for (auto &D : m_Data) { D = Val; }
}
void Tensor_CPU::Set(const vector<float32> &Vec)
{
	const uint32 Size = min(m_Shape.Size(), Vec.size());

	for (uint32 seek = 0; seek < Size; seek++)
	{
		m_Data[seek] = Vec[seek];
	}
}
const float32& Tensor_CPU::At(const uint32 ID) const
{
	return m_Data[ID];
}
const float32& Tensor_CPU::At(const uint32 Row, const uint32 Col, const uint32 Channel, const uint32 Batch) const
{
	uint32 ID = Batch * m_Shape.Volume() + Channel * m_Shape.Resolution() + Row * m_Shape.width + Col;
	return At(ID);
}
float32& Tensor_CPU::At(const uint32 ID)
{
	return m_Data[ID];
}
float32& Tensor_CPU::At(const uint32 Row, const uint32 Col, const uint32 Channel, const uint32 Batch)
{
	uint32 ID = Batch * m_Shape.Volume() + Channel * m_Shape.Resolution() + Row * m_Shape.width + Col;
	return At(ID);
}
void Tensor_CPU::Reshape(const Shape &TensorShape)
{
	m_Data.resize(TensorShape.Size());
	m_Shape = TensorShape;
}
void Tensor_CPU::Add(const float32 Val)
{
	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 Index = seek_batch * VolumeSize;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[Index + seek] += Val;
		}
	}
}
void Tensor_CPU::Add(const Tensor_CPU &T, const bool bPerBatch = false)
{
	if (m_Shape.Volume() != T.m_Shape.Volume()) { return; }

	if (!bPerBatch)
	{
		if (m_Shape != T.m_Shape) { return; }
	}

	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 SrcIndex = seek_batch * VolumeSize;
		uint32 DestIndex = bPerBatch ? 0 : SrcIndex;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[SrcIndex + seek] += T[DestIndex + seek];
		}
	}
}
void Tensor_CPU::Sub(const float32 Val)
{
	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 Index = seek_batch * VolumeSize;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[Index + seek] -= Val;
		}
	}
}
void Tensor_CPU::Sub(const Tensor_CPU &T, const bool bPerBatch = false)
{
	if (m_Shape.Volume() != T.m_Shape.Volume()) { return; }

	if (!bPerBatch)
	{
		if (m_Shape != T.m_Shape) { return; }
	}

	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 SrcIndex = seek_batch * VolumeSize;
		uint32 DestIndex = bPerBatch ? 0 : SrcIndex;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[SrcIndex + seek] -= T[DestIndex + seek];
		}
	}
}
void Tensor_CPU::Mul(const float32 Val)
{
	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 Index = seek_batch * VolumeSize;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[Index + seek] *= Val;
		}
	}
}
void Tensor_CPU::Mul(const Tensor_CPU &T, const bool bPerBatch = false)
{
	if (m_Shape.Volume() != T.m_Shape.Volume()) { return; }

	if (!bPerBatch)
	{
		if (m_Shape != T.m_Shape) { return; }
	}

	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 SrcIndex = seek_batch * VolumeSize;
		uint32 DestIndex = bPerBatch ? 0 : SrcIndex;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[SrcIndex + seek] *= T[DestIndex + seek];
		}
	}
}
void Tensor_CPU::Pow(const float32 Val)
{
	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 Index = seek_batch * VolumeSize;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[Index + seek] = pow(m_Data[Index + seek], Val);
		}
	}
}
void Tensor_CPU::Exp()
{
	const uint32 VolumeSize = m_Shape.Size();

#pragma omp parallel for
	for (int32 seek_batch = 0; seek_batch < m_Shape.batch; seek_batch++)
	{
		uint32 Index = seek_batch * VolumeSize;

		for (int seek = 0; seek < VolumeSize; seek++)
		{
			m_Data[Index + seek] = exp(m_Data[Index + seek]);
		}
	}
}
const Shape Tensor_CPU::GetShape() const
{
	return m_Shape;
};