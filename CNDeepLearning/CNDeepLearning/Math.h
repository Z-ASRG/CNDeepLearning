#ifndef _ZMATH_H_
#define _ZMATH_H_
#include<iostream>
#include<cmath>
using namespace std;
namespace ASRG
{

	/////////////////////////向量、点/////////////////////////////
	//不包含W分量2D向量和点
	class Vector2D
	{
	public:
		float x,y;

		Vector2D():x(0),y(0)
		{
		}
		Vector2D(float _x,float _y):x(_x),y(_y)
		{
		};
		void setXYZero()
		{
			this->x = this->y = 0.0;
		};
		void setXY(float x,float y)
		{
			this->x = x;
			this->y = y;
		};
		float getDistanceValue()
		{
			return sqrt(x*x+y*y);
		}

		Vector2D operator+(Vector2D& i)
		{
			Vector2D t;
			t.x = x + i.x;
			t.y = y + i.y;
			return t;
		};
		Vector2D operator-(Vector2D& i)
		{
			Vector2D t;
			t.x = x - i.x;
			t.y = y - i.y;
			return t;
		};
		Vector2D operator*(float scale)
		{
			Vector2D t;
			t.x = x * scale;
			t.y = y * scale;
			return t;
		};
		float operator*(Vector2D i)
		{
			return this->x*i.x+this->y*i.y;
		};
		void Normalize()
		{
			float length = this->getDistanceValue();
			x = x/length;
			y = y/length;
		};
		void NormalizeToVector(Vector2D& v)
		{
			float length = this->getDistanceValue();
			v.x = x/length;
			v.y = y/length;
		};
		float CosTh(Vector2D& v)
		{
			return (*this*v)/(this->getDistanceValue()*v.getDistanceValue());
		};

	};
	typedef Vector2D Point2D;

	//不包含w分量的3D向量和点
	class Vector3D
	{
	public:
		float _x,_y,_z;

		Vector3D():_x(0),_y(0),_z(0)
		{
		}
		Vector3D(float x,float y,float z):_x(x),_y(y),_z(z)
		{
		};

		void setXYZero()
		{
			_x = _y =_z = 0.0;
		};
		void setXYZ(float x,float y,float z)
		{
			_x = x;
			_y = y;
			_z = z;
		};
		float getDistanceValue()
		{
			return sqrt(_x*_x+_y*_y+_z*_z);
		}

		Vector3D operator+(const Vector3D& i)
		{
			Vector3D t;
			t._x = _x + i._x;
			t._y = _y + i._y;
			t._z = _z + i._z;
			return t;
		};
		Vector3D operator-(const Vector3D& i)
		{
			Vector3D t;
			t._x = _x - i._x;
			t._y = _y - i._y;
			t._z = _z - i._z;
			return t;
		};
		Vector3D operator*(float scale)
		{
			Vector3D t;
			t._x = _x * scale;
			t._y = _y * scale;
			t._z = _z * scale;
			return t;
		};
		float operator*(Vector3D& i)
		{
			return _x*i._x+_y*i._y+_z*i._z;
		};


		Vector3D CrossMultiplication(Vector3D in)
		{
			//this X in
			/*
			i     j    k
			x     y    z
			in.x in.y in.z

			i*((y*in.z)-(z*in.y))-j((x*in.z)-(z*in.x))+k((x*in.y)-(in.x*z))
			*/
			Vector3D t(((_y*in._z)-(_z*in._y)),-1*((_x*in._z)-(_z*in._x)),((_x*in._y)-(in._x*_y)));
			return t;
		};
		void Normalize()
		{
			float length = this->getDistanceValue();
			_x = _x/length;
			_y = _y/length;
			_z = _z/length;
		};
		void NormalizeToVector(Vector3D& v)
		{
			float length = this->getDistanceValue();
			v._x = _x/length;
			v._y = _y/length;
			v._z = _y/length;
		};
		void BuildByVector(Vector3D& first,Vector3D& end)
		{
			*this = end - first;
		};
		float CosTh(Vector3D& v)
		{
			return (*this*v)/(this->getDistanceValue()*v.getDistanceValue());
		};

	};
	typedef Vector3D Point3D;

	//包含W分量的4D齐次向量和点
	class Vector4D
	{
	public:
		float _x,_y,_z,_w;

		Vector4D():_x(0),_y(0),_z(0)
		{
		}
		Vector4D(float x,float y,float z,float w = 1):_x(x),_y(y),_z(z),_w(w)
		{
		};

		void setXYZero()
		{
			_x = _y =_z=_w = 0.0;
		};
		void setXYZW(float x,float y,float z,float w=1)
		{
			_x = x;
			_y = y;
			_z = z;
			_w = w;
		};
		float getDistanceValue()
		{
			return sqrt(_x*_x+_y*_y+_z*_z);
		}

		Vector4D operator+(const Vector4D& i)
		{
			Vector4D t;
			t._x = _x + i._x;
			t._y = _y + i._y;
			t._z = _z + i._z;
			t._w = 1;
			return t;
		};
		Vector4D operator-(const Vector4D& i)
		{
			Vector4D t;
			t._x = _x - i._x;
			t._y = _y - i._y;
			t._z = _z - i._z;
			t._w = 1;
			return t;
		};
		Vector4D operator*(float scale)
		{
			Vector4D t;
			t._x = _x * scale;
			t._y = _y * scale;
			t._z = _z * scale;
			t._w = 1;
			return t;
		};
		float operator*(Vector4D& i)
		{
			return _x*i._x+_y*i._y+_z*i._z;
		};
		Vector4D CrossMultiplication(Vector4D in)
		{
			//this X in
			/*
			i     j    k
			x     y    z
			in.x in.y in.z

			i*((y*in.z)-(z*in.y))-j((x*in.z)-(z*in.x))+k((x*in.y)-(in.x*z))
			*/
			Vector4D t(((_y*in._z)-(_z*in._y)),-1*((_x*in._z)-(_z*in._x)),((_x*in._y)-(in._x*_y)));
			return t;
		};
		void Normalize()
		{
			float length = this->getDistanceValue();
			_x = _x/length;
			_y = _y/length;
			_z = _z/length;
		};
		void NormalizeToVector(Vector4D& v)
		{
			float length = this->getDistanceValue();
			v._x = _x/length;
			v._y = _y/length;
			v._z = _y/length;
		};
		Vector3D To3DVector()
		{
			Vector3D t;
			t._x = _x/_w;
		    t._y = _y/_w;
		    t._z = _z/_w;
			return t;
		}
		void BuildByVector(Vector4D& first,Vector4D& end)
		{
			*this = end - first;
		};
		float CosTh(Vector4D& v)
		{
			return (*this*v)/(this->getDistanceValue()*v.getDistanceValue());
		};
	};
	typedef Vector4D Point4D;

	//2D顶点(int)
	class Vertex2D_INT
	{
	public:
		int x,y;
	};
	typedef Vertex2D_INT Vertex2DI;

	//2D顶点(float)
	class Vertex2D_FLOAT
	{
	public:
		float x,y;
	};
	typedef Vertex2D_FLOAT Vertex2DF;


	/////////////////////////向量、点 end/////////////////////////////

	////////////////////////参数化直线///////////////////////////
	//2D参数化直线
	class Parmline2D
	{
	public:
		Point2D p0;//起点
		Vector2D p1;//终点
		Vector2D v;//线段的方向向量
	};

	typedef Parmline2D PARMLINE2D;

	//3D参数化直线
	class Parmline3D
	{
	public:
		Point3D p0;//起点
		Point3D p1;//终点
		Vector3D v;//线段的方向向量
	};
	///////////////////////参数化直线 end////////////////////////////
	/////////////////////3D平面///////////////////////////////////
	class Plane3D
	{
	public:
		Point3D p0;
		Vector3D n;
		Plane3D()
		{};
		Plane3D(Point3D& p0,Vector3D& normal, int normalize=0)
		{
			// if normalize is 1 then the normal is made into a unit vector
			if (!normalize)
				this->n = normal;
			else
			{
				// make normal into unit vector
				normal.NormalizeToVector(this->n);
			} // end else
		};
		void Init(Point3D* p0,Vector3D* normal, int normalize=0)
		{
			// if normalize is 1 then the normal is made into a unit vector
			if (!normalize)
				this->n = *normal;
			else
			{
				// make normal into unit vector
				normal->NormalizeToVector(this->n);
			} // end else
		};
	};
	/////////////////////3D平面 end/////////////////////////////
	////////////////////矩阵///////////////////////////////////



	//////////////2x2矩阵
	class Matrix2X2
	{
	public:
		float M[2][2];

		/*
		float M00,M01;
		float M10,M11;
		*/

		Matrix2X2(){};
		Matrix2X2(float m00,float m01,float m10,float m11)
		{
			M[0][0] = m00;
			M[0][1] = m01;
			M[1][0] = m10;
			M[1][1] = m11;
		};
		//只有两个同型矩阵才可加
		Matrix2X2 operator+(Matrix2X2& m)
		{
			Matrix2X2 t;
			for(int i = 0;i<2;i++)
			{
				for(int j = 0;j < 2;j++)
					t.M[i][j] = m.M[i][j] + this->M[i][j];
			}
			return t;
		};
		Matrix2X2 operator*(float num)
		{
			Matrix2X2 t;
			for(int i = 0;i<2;i++)
			{
				for(int j = 0;j < 2;j++)
					t.M[i][j] = M[i][j] * num;
			}
			return t;
		};
		/*
		行列积
		可乘条件：左矩阵a的列数与右矩阵的行数要相等
		2 -> 2x1 2x2 2x3 2x4
		*/
		Matrix2X2 operator*(Matrix2X2 m)
		{
			Matrix2X2 t;
			t.M[0][0] = M[0][0]*m.M[0][0] +M[0][1]*m.M[1][0];
			t.M[0][1] = M[0][0]*m.M[0][1] +M[0][1]*m.M[1][1];
			t.M[1][0] = M[1][0]*m.M[0][0] +M[1][1]*m.M[1][0];
			t.M[1][1] = M[1][0]*m.M[0][1] +M[1][1]*m.M[1][1];

			return t;
		};
		/*
		矩阵行列式值
		*/
		float Det()
		{
			return (M[0][0]*M[1][1]-M[0][1]*M[1][0]);
		};
		/*
		矩阵的逆
		*/
		int TransToInverse(Matrix2X2& v)
		{
			float condi = Det();
			if(condi==0)
				return 0;
			v.M[0][0] = M[0][0];
			v.M[0][1] = M[1][0];
			v.M[1][0] = M[0][1];
			v.M[1][1] = M[1][1];
			v = v*(1/condi);
			return 1;
		}

		void show()
		{
			for(int i = 0;i<2;i++)
			{
				for(int j = 0;j < 2;j++)
					cout<< M[i][j]<<endl;
			}
		};
	};
	class Matrix1X3;
	////////////////3x3矩阵
	class Matrix3X3
	{
	public:
		//friend class Tool;
		float M[3][3];
		/*
		float M00,M01,M02;
		float M10,M11,M12;
		float M20,M21,M22;
		*/

		Matrix3X3(){};
		Matrix3X3(float m00,float m01,float m02,
			float m10,float m11,float m12,
			float m20,float m21,float m22)
		{
			M[0][0] = m00;
			M[0][1] = m01;
			M[0][2] = m02;
			M[1][0] = m10;
			M[1][1] = m11;
			M[1][2] = m12;
			M[2][0] = m20;
			M[2][1] = m21;
			M[2][2] = m22;
		};
		//只有两个同型矩阵才可加
		Matrix3X3 operator+(Matrix3X3& m)
		{
			Matrix3X3 t;
			for(int i = 0;i<3;i++)
			{
				for(int j = 0;j < 3;j++)
					t.M[i][j] = m.M[i][j] + this->M[i][j];
			}
			return t;
		};
		Matrix3X3 operator*(float num)
		{
			Matrix3X3 t;
			for(int i = 0;i<3;i++)
			{
				for(int j = 0;j < 3;j++)
					t.M[i][j] = M[i][j] * num;
			}
			return t;
		};
		/*
		行列积
		可乘条件：左矩阵a的列数与右矩阵的行数要相等
		2 -> 2x1 2x2 2x3 2x4
		*/
		Matrix3X3 operator*(Matrix3X3 m)
		{
			Matrix3X3 t;
			float sum=0;
			for(int k = 0;k<3;k++)
			{
				for(int i = 0;i<3;i++)
				{
					for(int j = 0;j<3;j++)
					{
						sum += M[k][j]*m.M[j][i];
					}
					t.M[k][i] = sum;
					sum = 0;
				}

			}
			return t;
		};


		/*
		矩阵行列式值
		*/
		float Det()
		{
			return (M[0][0]*(M[1][1]*M[2][2] - M[2][1]*M[1][2])+
				(-1)*M[1][0]*(M[0][1]*M[2][2]-M[2][1]*M[0][2])+M[2][0]*(M[0][1]*M[1][2]-M[1][1]*M[0][2]));
		};
		/*
		矩阵的逆
		*/
		int TransToInverse(Matrix3X3& v)
		{
			float condi = Det();
			if(condi==0)
				return 0;
			v.M[0][0] =   M[1][1]* M[2][2] -  M[2][1]* M[1][2];
			v.M[1][0] =  M[1][0]* M[2][2] -  M[2][0]* M[1][2];
			v.M[2][0] =   M[1][0]* M[2][1] -  M[2][0]* M[1][1];

			v.M[0][1] =  M[0][1]* M[2][2] -  M[2][1]* M[0][2];
			v.M[1][1] =   M[0][0]* M[2][2] -  M[2][0]* M[0][2];
			v.M[2][1] =  M[0][0]* M[2][1] -  M[2][0]* M[0][1];

			v.M[0][2] =   M[0][1]* M[1][2] -  M[1][1]* M[0][2];
			v.M[1][2] =  M[0][0]* M[1][2] -  M[1][0]* M[0][2];
			v.M[2][2] =  M[0][0]* M[1][1] -  M[1][0]* M[0][1];

			v = v*(1/condi);
			return 1;
		}

		void VectorMulMatrix3X3(Vector3D* v,Matrix3X3* m,Matrix1X3* t);
		void VectorMulMatrix3X32(Vector3D& v,Matrix3X3& m,Matrix1X3& t);
		void show()
		{
			for(int i = 0;i<3;i++)
			{
				for(int j = 0;j < 3;j++)
					cout<< M[i][j]<<" ";
				cout<<endl;
			}
		};
	};

	/////////////3X2矩阵
	class Matrix3X2
	{
	public:
		float M[3][2];
		/*
		float M00,M01;
		float M10,M11;
		float M20,M21;
		*/

		Matrix3X2(){};
		Matrix3X2(float m00,float m01,float m10,float m11,float m20,float m21)
		{
			M[0][0] = m00;
			M[0][1] = m01;
			M[1][0] = m10;
			M[1][1] = m11;
			M[2][0] = m20;
			M[2][1] = m21;
		};
		//只有两个同型矩阵才可加
		Matrix3X2 operator+(Matrix3X2& m)
		{
			Matrix3X2 t;
			for(int i = 0;i<3;i++)
			{
				for(int j = 0;j < 2;j++)
					t.M[i][j] = m.M[i][j] + this->M[i][j];
			}

			return t;
		};
		Matrix3X2 operator*(float num)
		{
			Matrix3X2 t;
			for(int i = 0;i<3;i++)
			{
				for(int j = 0;j < 2;j++)
					t.M[i][j] = M[i][j] * num;
			}
			return t;
		};

	};


	//////////////////4X3
	class Matrix4X3
	{
	public:

		float M[4][3];
		/*
		float M00,M01,M02;
		float M10,M11,M12;
		float M20,M21,M22;
		float M30,M31,M32;
		*/


	};
	///////////////////4X4
	class Matrix4X4
	{
	public:

		float M[4][4];
		/*
		float M00,M01,M02,M03;
		float M10,M11,M12,M13;
		float M20,M21,M22,M23;
		float M30,M31,M32,M33;
		*/
		Matrix4X4(){};
		Matrix4X4(float m00,float m01,float m02,float m03,
			      float m10,float m11,float m12,float m13,
			      float m20,float m21,float m22,float m23,
			      float m30,float m31,float m32,float m33)
		{
			M[0][0] = m00;
			M[0][1] = m01;
			M[0][2] = m02;
			M[0][3] = m03;
			M[1][0] = m10;
			M[1][1] = m11;
			M[1][2] = m12;
			M[1][3] = m13;
			M[2][0] = m20;
			M[2][1] = m21;
			M[2][2] = m22;
			M[2][3] = m23;
			M[3][0] = m30;
			M[3][1] = m31;
			M[3][2] = m32;
			M[3][3] = m33;

		};
		//只有两个同型矩阵才可加
		Matrix4X4 operator+(Matrix4X4& m)
		{
			Matrix4X4 t;
			for(int i = 0;i<4;i++)
			{
				for(int j = 0;j < 4;j++)
					t.M[i][j] = m.M[i][j] + this->M[i][j];
			}
			return t;
		};
		Matrix4X4 operator*(float num)
		{
			Matrix4X4 t;
			for(int i = 0;i<4;i++)
			{
				for(int j = 0;j < 4;j++)
					t.M[i][j] = M[i][j] * num;
			}
			return t;
		};
		/*
		行列积
		可乘条件：左矩阵a的列数与右矩阵的行数要相等
		*/
		Matrix4X4 operator*(Matrix4X4& m)
		{
			Matrix4X4 t;
			for (int row=0; row<4; row++)
			{
				for (int col=0; col<4; col++)
				{
					float sum = 0;

					for (int index=0; index<4; index++)
					{
						sum+=(M[row][index]*m.M[index][col]);
					} 
					t.M[row][col] = sum;

				}

			}

			return t;
		};
		void Mat_Mul_VECTOR3D_4X4(Vector3D*  va, 
			Matrix4X4* mb,
			Vector3D*  vprod)
		{


			for (int col=0,row=0; col < 3; col++)
			{
				// compute dot product from row of ma 
				// and column of mb
				float sum = 0,num=0; // used to hold result

				for (row = 0; row<3; row++)
				{
					if(row == 0)
						num= va->_x;
					if(row == 1)
						num= va->_y;
					if(row == 2)
						num= va->_z;
					// add in next product pair
					sum+=(num*mb->M[row][col]);
				} // end for index

				// add in last element in column or w*mb[3][col]
				    sum+=mb->M[row][col];

					if(col == 0)
						vprod->_x=sum;
					if(col == 1)
						vprod->_y=sum;
					if(col == 2)
						vprod->_z=sum;
				// insert resulting col element
	

			} // end for col

		} 
		void Mat_Mul_VECTOR4D_4X4(Vector4D*  va, 
			Matrix4X4* mb,
			Vector4D* vprod)
		{
			// this function multiplies a VECTOR4D against a 
			// 4x4 matrix - ma*mb and stores the result in mprod
			// the function makes no assumptions

			for (int col=0; col < 4; col++)
			{
				// compute dot product from row of ma 
				// and column of mb
				float sum = 0,num=0; // used to hold result

				for (int row=0; row<4; row++)
				{
					if(row == 0)
						num= va->_x;
					if(row == 1)
						num= va->_y;
					if(row == 2)
						num= va->_z;
					if(row == 3)
						num= va->_w;
					// add in next product pair
					sum+=(num*mb->M[row][col]);
				} // end for index

				if(col == 0)
					vprod->_x=sum;
				if(col == 1)
						vprod->_y=sum;
					if(col == 2)
						vprod->_z=sum;
			if(col == 3)
						vprod->_w=sum;
		// insert resulting col element

			} // end for col

		} 
		void Mat_Mul_VECTOR4D_4X4(Vector4D*  va,
			Vector4D* vprod)
		{
			// this function multiplies a VECTOR4D against a 
			// 4x4 matrix - ma*mb and stores the result in mprod
			// the function makes no assumptions

			for (int col=0; col < 4; col++)
			{
				// compute dot product from row of ma 
				// and column of mb
				float sum = 0,num=0; // used to hold result

				for (int row=0; row<4; row++)
				{
					if(row == 0)
						num= va->_x;
					if(row == 1)
						num= va->_y;
					if(row == 2)
						num= va->_z;
					if(row == 3)
						num= va->_w;
					// add in next product pair
					sum+=(num*this->M[row][col]);
				} // end for index

				if(col == 0)
					vprod->_x=sum;
				if(col == 1)
						vprod->_y=sum;
					if(col == 2)
						vprod->_z=sum;
			if(col == 3)
						vprod->_w=sum;
		// insert resulting col element

			} // end for col

		} 
		Vector4D Mat_Mul_VECTOR4D_4X4(Vector4D*  va)
		{
			// this function multiplies a VECTOR4D against a 
			// 4x4 matrix - ma*mb and stores the result in mprod
			// the function makes no assumptions
			Vector4D vprod;
			for (int col=0; col < 4; col++)
			{
				// compute dot product from row of ma 
				// and column of mb
				float sum = 0,num=0; // used to hold result

				for (int row=0; row<4; row++)
				{
					if(row == 0)
						num= va->_x;
					if(row == 1)
						num= va->_y;
					if(row == 2)
						num= va->_z;
					if(row == 3)
						num= va->_w;
					// add in next product pair
					sum+=(num*this->M[row][col]);
				} // end for index

				if(col == 0)
					vprod._x=sum;
				if(col == 1)
						vprod._y=sum;
					if(col == 2)
						vprod._z=sum;
			if(col == 3)
						vprod._w=sum;
			
		// insert resulting col element

			} // end for col
			return vprod;
		} 
		/*
		矩阵行列式值
		*/
		float Det()
		{
			return (  M[0][0] * (  M[1][1] *  M[2][2] -  M[1][2] *  M[2][1] ) -
                M[0][1] * (  M[1][0] *  M[2][2] -  M[1][2] *  M[2][0] ) +
                M[0][2] * (  M[1][0] *  M[2][1] -  M[1][1] *  M[2][0] ) );
		};
		/*
		矩阵的逆
		*/
		int TransToInverse(Matrix4X4& v)
		{
			float condi = Det();
			if(condi==0)
				return 0;

			float det_inv  = 1.0f / condi;

			v.M[0][0] =  det_inv * (  M[1][1] *  M[2][2] -  M[1][2] *  M[2][1] );
			v.M[0][1] = -det_inv * (  M[0][1] *  M[2][2] -  M[0][2] *  M[2][1] );
			v.M[0][2] =  det_inv * (  M[0][1] *  M[1][2] -  M[0][2] *  M[1][1] );
			v.M[0][3] = 0.0f; // always [0][

			v.M[1][0] = -det_inv * (  M[1][0] *  M[2][2] -  M[1][2] *  M[2][0] );
			v.M[1][1] =  det_inv * (  M[0][0]*  M[2][2] -  M[0][2] *  M[2][0] );
			v.M[1][2] = -det_inv * (  M[0][0] *  M[1][2] -  M[0][2] *  M[1][0]);
			v.M[1][3] = 0.0f; // always [0][

			v.M[2][0] =  det_inv * (  M[1][0] *  M[2][1] -  M[1][1] *  M[2][0] );
			v.M[2][1] = -det_inv * (  M[0][0] *  M[2][1] -  M[0][1] *  M[2][0] );
			v.M[2][2] =  det_inv * (  M[0][0] *  M[1][1] -  M[0][1] *  M[1][0]);
			v.M[2][3] = 0.0f; // always [0][

			v.M[3][0] = -(  M[3][0] * v.M[0][0]+  M[3][1] * v.M[1][0]+  M[3][2] * v.M[2][0] );
			v.M[3][1] = -(  M[3][0] * v.M[0][1] +  M[3][1] * v.M[1][1] +  M[3][2] * v.M[2][1] );
			v.M[3][2] = -(  M[3][0] * v.M[0][2] +  M[3][1] * v.M[1][2] +  M[3][2] * v.M[2][2] );
			v.M[3][3] = 1.0f; // always [0][

			// return success 

			return 1;
		}


		void show()
		{
			for(int i = 0;i<4;i++)
			{
				for(int j = 0;j < 4;j++)
					cout<< M[i][j]<<" ";
				cout<<endl;
			}
		};
	};
	////////////////1X3矩阵
	class Matrix1X3
	{
	public:
		float M[3];
		/*
		float M00,M01,M02;
		*/
		Matrix1X3(){};
		Matrix1X3(float m00,float m01,float m11)
		{
			M[0] = m00;
			M[1] = m01;
			M[2] = m11;
		}
		Matrix1X3 operator*(Matrix3X3& m)
		{
			Matrix1X3 t;
			float sum = 0;
			for(int i = 0;i<3;i++,sum = 0)
			{
				for(int j = 0;j<3;j++)
				{
					sum +=M[j]*m.M[j][i];
				}
				t.M[i] = sum;
			}
			return t;
		};


	};
	//////////////1x2矩阵
	class Matrix1X2
	{
	public:

		float M[2];
		/*
		float M00,M01;
		*/


		Matrix1X2(){};
		Matrix1X2(float m00,float m01)
		{
			M[0]= m00;
			M[1]= m01;
		};
		//只有两个同型矩阵才可加
		Matrix1X2 operator+(Matrix1X2& m)
		{
			Matrix1X2 t;
			t.M[0] = m.M[0] + this->M[0];
			t.M[1] = m.M[1] + this->M[1];

			return t;
		};
		Matrix1X2 operator*(float num)
		{
			Matrix1X2 t;

			t.M[0] = this->M[0]*num;
			t.M[1] = this->M[1]*num;

			return t;
		};
		/*
		行列积
		可乘条件：左矩阵a的列数与右矩阵的行数要相等
		*/
		Matrix1X2 operator*(Matrix3X2& m)
		{
			//数学上无定义这里把1x2矩阵加一列w
			Matrix1X2 t;
			t.M[0] = M[0]*m.M[0][0]+M[1]*m.M[1][0]+m.M[2][0];
			t.M[1] = M[0]*m.M[0][1]+M[1]*m.M[1][1]+m.M[2][1];
			return t;
		};
		void show()
		{
			cout<< M[0]<<endl;
			cout<< M[1]<<endl;
		};
	};
	//////////////////1X4矩阵
	class Matrix1X4
	{
	public:
		union
		{
			float M[4];
			struct
			{
				float M00,M01,M02,M03;
			};
		};
		/*	void Mat_Mul_1X4_4X4(MATRIX1X4_PTR ma, 
		MATRIX4X4_PTR mb,
		MATRIX1X4_PTR mprod)
		{
		// this function multiplies a 1x4 matrix against a 
		// 4x4 matrix - ma*mb and stores the result
		// no tricks or assumptions here, just a straight multiply

		for (int col=0; col<4; col++)
		{
		// compute dot product from row of ma 
		// and column of mb
		float sum = 0; // used to hold result

		for (int row=0; row<4; row++)
		{
		// add in next product pair
		sum+=(ma->M[row] * mb->M[row][col]);
		} // end for index

		// insert resulting col element
		mprod->M[col] = sum;

		} // end for col

		}*/
	};

	class Tool
	{
	public:
		/*	void VectorMulMatrix3X3(Vector3D* v,Matrix3X3* m,Matrix1X3* t)
		{
		t->M[0] = v->_x*m->M[0][0]+v->_x*m->M[1][0]+v->_x*m->M[2][0];
		t->M[1] = v->_x*m->M[0][1]+v->_x*m->M[1][1]+v->_x*m->M[2][1];
		t->M[2] = v->_x*m->M[0][2]+v->_x*m->M[1][2]+v->_x*m->M[2][2];

		};*/
	};

	////////////////////矩阵end/////////////////////////////
};

#endif