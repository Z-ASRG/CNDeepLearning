#include"Tensor.h"

using namespace ASRG;


//x =row(height) y=column(width) z= group a= batch
ASRG::Tensor::Tensor(int x/*=1*/, int y/*=1*/, int z/*=1*/, int a/*=1*/)
	:m_Array(x, y, z, a), m_Shape(x, y, z, a)
{

}
ASRG::Tensor::~Tensor()
{

}

void ASRG::Tensor::setZeros()
{
	m_Array = af::constant(0, m_Shape.x, m_Shape.y, m_Shape.z, m_Shape.a);
}

void ASRG::Tensor::setRandoms()
{
	m_Array = af::randn(m_Shape.x, m_Shape.y, m_Shape.z, m_Shape.a);
}

void ASRG::Tensor::setRandomsUniform()
{
	m_Array = af::randu(m_Shape.x, m_Shape.y, m_Shape.z, m_Shape.a);
}

void ASRG::Tensor::setIdentity()
{
	m_Array = af::identity(m_Shape.x, m_Shape.y, m_Shape.z, m_Shape.a);
}

void ASRG::Tensor::print()
{
	af::array& element = m_Array;
	af_print(element,8);
}

Tensor ASRG::Tensor::tranverse()
{
	Tensor m;
	m.m_Array = m_Array.T();
	return m;
}

ASRG::Tensor ASRG::Tensor::multiply(const Tensor& i)
{
	Tensor m;
	m.m_Array = m_Array*i.m_Array;
	return m;
}

ASRG::Tensor ASRG::Tensor::operator*(const Tensor& i)const
{
	Tensor m;
	m.m_Array = af::matmul(m_Array, i.m_Array);
	return m;
}
ASRG::Tensor ASRG::operator*(const float f, const Tensor& i)
{
	Tensor m;
	m.m_Array = f*i.m_Array;
	return m;
}
ASRG::Tensor ASRG::Tensor::operator+(const Tensor& i) const
{
	Tensor m;
	m.m_Array = this->m_Array + i.m_Array;
	return m;
}

ASRG::Tensor ASRG::Tensor::operator-(const Tensor& i) const
{
	Tensor m;
	m.m_Array = this->m_Array - i.m_Array;
	return m;
}

ASRG::Tensor ASRG::Tensor::expandTensor()
{
	float* m = m_Array.host<float>();
	float a[] = {m[0],m[0],m[1],m[1]};
	Tensor Epn(a, 2, 2);
	delete[] m;
	return Epn;
}

ASRG::Tensor ASRG::operator-(const float f, const Tensor& i)
{
	Tensor m;
	m.m_Array = f - i.m_Array;
	return m;
}
int ASRG::Tensor::getDimensions(int pos)
{
	return m_Array.dims(pos);
}

int ASRG::Tensor::getDimensionsSize()
{
	return m_Array.numdims();
}