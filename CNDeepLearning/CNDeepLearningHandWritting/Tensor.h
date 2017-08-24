#pragma once

#include <iostream>
#include<cmath>
#include <vector>


#include <boost/thread.hpp>
#include <boost/thread/thread_pool.hpp>   
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

template<typename T = double>
class Tensor
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & _shape;
		ar & _data;
	}
public:
	Tensor(T* data, int row, int column) :_shape(row, column)
	{
		for (int i = 0; i < row*column; i++)
		{
			this->_data.push_back(data[i]);
		}
	}
	Tensor(int row, int column) :_shape(row, column), _data(row*column)
	{

	}
	Tensor(const Tensor& t) :_shape(t._shape.row, t._shape.column), _data(t._shape.row*t._shape.column)
	{
		for (int i = 0; i < t._shape.row*t._shape.column; i++)
		{
			this->_data[i] = t._data[i];
		}
	}
	Tensor() :_shape(0, 0)
	{

	}
	std::vector<T> Data() { return _data; }
	void Data(std::vector<T> val) { _data = val; }

	void mat_multi(Tensor& newmat, const Tensor& mat)
	{
		for (int r = 0; r < this->_shape.row; r++) {
			multi_thread_mat_multiply(r, newmat, mat);
			//boost::thread t(&Tensor::multi_thread_mat_multiply, this, r, std::ref(newmat), std::ref(mat));
			//t.join();
		}

	}
	void mat_add(Tensor& newmat, const Tensor& mat)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*this->_shape.column + j] = this->_data[i*this->_shape.column + j]
					+ mat._data[i*this->_shape.column + j];
			}
		}
	}
	void mat_add(Tensor& newmat, const float num)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*_shape.row + j] = this->_data[i*_shape.row + j]
					+ num;
			}
		}
	}
	void mat_minus(Tensor& newmat, const Tensor& mat)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*_shape.row + j] = this->_data[i*_shape.row + j]
					- mat._data[i*_shape.row + j];
			}
		}
	}
	void mat_minus(Tensor& newmat, const float num)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*_shape.row + j] = this->_data[i*_shape.row + j]
					- num;
			}
		}
	}
	void mat_minus_(Tensor& newmat, const float num)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*_shape.row + j] =
					num - this->_data[i*_shape.row + j];
			}
		}
	}
	void mat_dot(Tensor& newmat, const Tensor& mat)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*_shape.row + j] = this->_data[i*_shape.row + j]
					* mat._data[i*_shape.row + j];
			}
		}
	}
	void mat_dot(Tensor& newmat, const float f)
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				newmat._data[i*_shape.row + j] = this->_data[i*_shape.row + j]
					* f;
			}
		}
	}
	void test(int& i, int j)
	{
		i = -100;
		printf("%d, %d", i, j);
	}
public:
	struct Shape
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & row;
			ar & column;
		}
	public:
		int row, column;
		Shape(int _row, int _column) :row(_row), column(_column) {}
	};

	Shape _shape;
	std::vector<T> _data;
	void reShape(int row,int column)
	{
		this->_shape.row = row;
		this->_shape.column = column;
	}

	void multi_thread_mat_multiply(int rowId, Tensor<T>& _new, const Tensor<T>& _right)
	{
		for (int k = 0; k < _right._shape.column; k++)
		{
			_new._data[rowId*_new._shape.column + k] = 0;
			for (int c = 0; c < _right._shape.row; c++)
			{
				_new._data[rowId*_new._shape.column + k] += _data[rowId*_shape.column + c]
					* _right._data[c*_right._shape.column + k];
			}
		}
	}

	void print()
	{
		for (int i = 0; i < this->_shape.row; i++)
		{
			for (int j = 0; j < this->_shape.column; j++)
			{
				std::cout << " " << this->_data[i*_shape.row + j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void generateRandomTensor(int row, int column)
	{
		this->_shape.row = row;
		this->_shape.column = column;
		this->_data.clear();
		for (int i = 0; i < row; i++)
		{
			for (int c = 0; c < column; c++)
			{
				this->_data.push_back(random(-1.0, 1.0));
			}
		}
	}
	virtual void operator=(const Tensor& t)
	{
		this->_shape.row = t._shape.row;
		this->_shape.column = t._shape.column;
		this->_data.clear();
		for (int i = 0; i < _shape.row*_shape.column; i++)
		{
			this->_data.push_back(t._data[i]);
		}
	}
};