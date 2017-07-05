#pragma once

#ifndef __TENSOR_H__
#define __TENSOR_H__

#include "Shape.h"

#include <arrayfire.h>
#include<iostream>


using namespace std;

namespace ASRG
{

	class Tensor
	{
	private:
		af::array m_Array;
		Shape m_Shape;
	public:
		//Constructor

		//x =row y=column z= group a= batch
		Tensor(int x=1, int y=1, int z=1, int a=1);
		Tensor(int x=1, int y=1, int z=1, int a=1);
		~Tensor();

	public:
		virtual void setZeros();
		//Generate and tranform array into [-1,1]
		virtual void setRandoms();
		//Generate and tranform array into [0,1]
		virtual void setRandomsUniform();
		//Generate and traform array into identity
		virtual void setIdentity();
		//print all array elements
		virtual void print();
	private:
		int _x, _y, _z, _a;
	};





}

#endif