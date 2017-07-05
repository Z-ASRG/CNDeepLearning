#include"Tensor.h"

using namespace ASRG;


//x =row(height) y=column(width) z= group a= batch
ASRG::Tensor::Tensor(int x/*=1*/, int y/*=1*/, int z/*=1*/, int a/*=1*/)
	:m_Array(x, y, z, a), m_Shape(x, y, z, a), _x(x), _y(y), _z(z), _a(a)
{

}

ASRG::Tensor::~Tensor()
{

}

void ASRG::Tensor::setZeros()
{
	m_Array = af::constant(0, m_Shape.height, m_Shape.width, m_Shape.depth, m_Shape.batch);
}

void ASRG::Tensor::setRandoms()
{
	m_Array = af::randn(_x, _y, _z, _a);
}

void ASRG::Tensor::setRandomsUniform()
{
	m_Array = af::randu(_x, _y, _z, _a);
}

void ASRG::Tensor::setIdentity()
{
	m_Array = af::identity(_x, _y, _z, _a);
}

void ASRG::Tensor::print()
{
	af::array& element = m_Array;
	af_print(element);
}
