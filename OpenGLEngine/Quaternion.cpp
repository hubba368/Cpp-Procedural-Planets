#include "Quaternion.h"



Quaternion::Quaternion()
{
	_mScalar = 1.0f;
}


Quaternion::~Quaternion()
{
}

Vector3& Quaternion::GetVector()
{
	return _mVector;
}

float Quaternion::GetScalar()
{
	return _mScalar;
}

const float& Quaternion::operator [] (int index)
{
	if (index == 3) 
	{
		return _mScalar;
	}

	return _mVector[index];
}

Quaternion Quaternion::operator + (Quaternion & val)
{
	Quaternion quat;
	Vector3 vec;
	float scalar;

	vec = _mVector + val.GetVector();
	scalar = _mScalar + val.GetScalar();

	quat.SetQuaternion(vec, scalar);
}

Quaternion Quaternion::operator * (Quaternion & val)
{
	Quaternion quat;
	Vector3 vec;
	float scalar;

	scalar = _mScalar * val.GetScalar() - _mVector.DotProduct(val.GetVector());

	vec[0] = _mScalar * val[0] + _mVector[0] * val.GetScalar() + _mVector[1] * val[2] - _mVector[2] * val[1];
	vec[1] = _mScalar * val[1] + _mVector[1] * val.GetScalar() + _mVector[2] * val[0] - _mVector[2] * val[2];
	vec[2] = _mScalar * val[2] + _mVector[2] * val.GetScalar() + _mVector[0] * val[1] - _mVector[2] * val[0];

	quat.SetQuaternion(vec, scalar);

	return quat;
}

Quaternion Quaternion::GetConjugate(Quaternion & val)
{
	//custom method for getting conjugate
	Quaternion quat;
	Vector3 v;
	Vector3 test;
	float scalar;

	test = val.GetVector();
	scalar = val.GetScalar();

	v[0] = -test[0];
	v[1] = -test[1];
	v[2] = -test[2];

	quat.SetQuaternion(v, scalar);


	return quat;
}

float Quaternion::GetSquareRoot()
{
	return _mVector.GetMagnitude() + (_mScalar * _mScalar);
}


void Quaternion::ConvertToRotationMatrix(float * rot)
{
	if (rot == NULL)
	{
		return;
	}

	float norm = GetSquareRoot();
	float s = (norm > 0.0f) ? (2.0f / norm) : 0.0f;

	float xs = _mVector[0] * s;
	float ys = (_mVector)[1] * s;
	float zs = (_mVector)[2] * s;
	float wxs = _mScalar * xs;
	float wys = _mScalar * ys;
	float wzs = _mScalar * zs;
	float xxs = (_mVector)[0] * xs;
	float xys = (_mVector)[0] * ys;
	float xzs = (_mVector)[0] * zs;
	float yys = (_mVector)[1] * ys;
	float yzs = (_mVector)[1] * zs;
	float zzs = (_mVector)[2] * zs;

	rot[0] = 1.0f - (yys + zzs);
	rot[1] = xys + wzs;
	rot[2] = xzs - wys;
	rot[3] = 0.0;

	rot[4] = xys - wzs;
	rot[5] = 1.0f - (xxs + zzs);
	rot[6] = yzs + wxs;
	rot[7] = 0.0;

	rot[8] = xzs + wys;
	rot[9] = yzs - wxs;
	rot[10] = 1.0f - (xxs + yys);
	rot[11] = 0.0f;

	rot[12] = rot[13] = rot[14] = 0.0f;
	rot[15] = 1.0f;
}


void Quaternion::SetQuaternion(float vx, float vy, float vz, float scalar)
{
	_mVector.SetVector(vx, vy, vz);
	_mScalar = scalar;
}


void Quaternion::SetQuaternion(Vector3 & vec, float scalar)
{
	_mVector = vec;
	_mScalar = scalar;
}
