#pragma once

#ifndef __TENSOR_H__
#define __TENSOR_H__

#include "Shape.h"

#include <arrayfire.h>
#include<iostream>
#include <array>


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
		Tensor(int x = 1, int y = 1, int z = 1, int a = 1);

		template<typename T = float>
		Tensor(const T* data, int x = 1, int y = 1, int z = 1, int a = 1)
			:m_Array(x, y, z, a,data), m_Shape(x, y, z, a)
		{}
		~Tensor();

		af::array Array() const { return m_Array; }
		void Array(af::array val) { m_Array = val; }
		ASRG::Shape Shape() const { return m_Shape; }
		void Shape(ASRG::Shape val) { m_Shape = val; }
	public:
		//Matrix operation function sets
		//Initializing all element to 0
		//************************************
		// Method:    setZeros
		// FullName:  ASRG::Tensor::setZeros
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void setZeros();
		//Generate and tranform array into [-1,1]
		//************************************
		// Method:    setRandoms
		// FullName:  ASRG::Tensor::setRandoms
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void setRandoms();
		//Generate and tranform array into [0,1]
		//************************************
		// Method:    setRandomsUniform
		// FullName:  ASRG::Tensor::setRandomsUniform
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void setRandomsUniform();
		//Generate and traform array into identity
		//************************************
		// Method:    setIdentity
		// FullName:  ASRG::Tensor::setIdentity
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void setIdentity();

	public:

		//************************************
		// Method:    getDimensions
		// FullName:  ASRG::Tensor::getDimensions
		// Access:    virtual public 
		// Returns:   int
		// Qualifier:
		// Parameter: int pos   position of dimensions array
		// Using getDimensionSize to get all size of dimensions array
		//************************************
		virtual int getDimensions(int pos);
		//************************************
		// Method:    getDimensionsSize
		// FullName:  ASRG::Tensor::getDimensionsSize
		// Access:    virtual public 
		// Returns:   int
		// Qualifier:
		//************************************
		virtual int getDimensionsSize();

		//print all array elements
		//************************************
		// Method:    print
		// FullName:  ASRG::Tensor::print
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void print();

	public:
		//Row * Column
		//************************************
		// Method:    operator*
		// FullName:  ASRG::Tensor::operator*
		// Access:    public 
		// Returns:   ASRG::Tensor
		// Qualifier: const
		// Parameter: const Tensor & i
		//************************************
		Tensor operator*(const Tensor& i)const;
	};






}

#endif