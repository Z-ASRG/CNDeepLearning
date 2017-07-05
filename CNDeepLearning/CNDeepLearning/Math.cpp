#include"Math.h"
using namespace ASRG;

void Matrix3X3::VectorMulMatrix3X3(Vector3D* v,Matrix3X3* m,Matrix1X3* t)
{
	t->M[0] = v->_x*m->M[0][0]+v->_x*m->M[1][0]+v->_x*m->M[2][0];
	t->M[1] = v->_x*m->M[0][1]+v->_x*m->M[1][1]+v->_x*m->M[2][1];
	t->M[2] = v->_x*m->M[0][2]+v->_x*m->M[1][2]+v->_x*m->M[2][2];

};
void Matrix3X3::VectorMulMatrix3X32(Vector3D& v,Matrix3X3& m,Matrix1X3& t)
{
	t.M[0] = v._x*m.M[0][0]+v._x*m.M[1][0]+v._x*m.M[2][0];
	t.M[1] = v._x*m.M[0][1]+v._x*m.M[1][1]+v._x*m.M[2][1];
	t.M[2] = v._x*m.M[0][2]+v._x*m.M[1][2]+v._x*m.M[2][2];

};