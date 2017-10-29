#include "MainCamera.h"



float MainCamera::DegToRads(float value)
{
	float radians = value * (3.14159265 / 180.0);
	return radians;
}


float MainCamera::RadToDegs(float value)
{
	float degrees = value * (180.0 / 3.14159265);
	return degrees;
}


MainCamera::MainCamera()
{
	InitialiseCamera();
}


MainCamera::~MainCamera()
{
	
}


void MainCamera::InitialiseCamera()
{
	_mCameraPosition.SetVector(0.0f, 0.0f, 0.0f);
	_mCameraDirection.SetVector(0.0f, 0.0f, -1.0f);
	_mUpVector.SetVector(0.0f, 1.0f, 0.0f);
	_mRightVector = _mCameraDirection.CrossProduct(_mUpVector);
	_mUpVector = _mRightVector.CrossProduct(_mCameraDirection);
	UpdateViewMatrix();
}


void MainCamera::SetCameraPosition(Vector3 * pos)
{
	_mCameraPosition = (*pos);
	UpdateViewMatrix();
}


void MainCamera::SetLookAtPoint(Vector3 * lookPos)
{
	_mCameraDirection = (*lookPos) - _mCameraPosition;
	_mCameraDirection.Normalise();

	_mRightVector = _mCameraDirection.CrossProduct(_mUpVector);

	_mUpVector = _mRightVector.CrossProduct(_mCameraDirection);

	_mUpVector.Normalise();
	_mRightVector.Normalise();

	UpdateViewMatrix();
}


void MainCamera::SetAspectRatio(float ratio)
{
	_mAspectRatio = ratio;
}


void MainCamera::SetProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
	_mProjectionMatrix.SetPerspective(fovy, aspect, zNear, zFar);
	UpdateViewMatrix();
}


void MainCamera::UpdateViewMatrix()
{
	_mViewMatrix.SetViewMatrix(_mCameraPosition, _mCameraPosition + _mCameraDirection, _mUpVector);
}


Matrix4x4* MainCamera::GetViewMatrix()
{
	return &_mViewMatrix;
}


Matrix4x4* MainCamera::GetProjectionMatrix()
{
	return &_mProjectionMatrix;
}


void MainCamera::StrafeCamera(float amount)
{
	_mCameraPosition = _mCameraPosition + _mRightVector * amount;
}


void MainCamera::DollyCamera(float amount)
{
	_mCameraPosition = _mCameraPosition + _mCameraDirection * amount;
}


void MainCamera::PedCamera(float amount)
{
	_mCameraPosition = _mCameraDirection + _mUpVector * amount;
}


void MainCamera::RotateCamera(float yaw, float pitch, float roll)
{
	//convert to radians
	yaw = DegToRads(yaw);
	pitch = DegToRads(pitch);
	roll = DegToRads(roll);

	//Get new rotations
	Quaternion newPitch;
	Quaternion newYaw;
	Quaternion newRoll;

	newPitch.SetQuaternion(_mRightVector * sin(pitch / 2.0f), cos(pitch / 2.0f));
	newYaw.SetQuaternion(Vector3(0.0f, 1.0f, 0.0f) * sin(yaw / 2.0f), cos(yaw / 2.0f));
	newRoll.SetQuaternion(_mCameraDirection * sin(roll / 2.0f), cos(roll / 2.0f));

	Quaternion newRotation = newRoll * newPitch * newYaw;

	Quaternion conj;
	Quaternion directionQuat;
	Quaternion upQuat;

	//get conjugate of rotation quaternion 
	conj.GetConjugate(newRotation);
	//not the best way to calc rotation, but it works
	directionQuat.SetQuaternion(_mCameraDirection, 0);
	Quaternion result = directionQuat * newRotation * conj;

	upQuat.SetQuaternion(_mUpVector, 0);
	Quaternion result2 = upQuat * newRotation * conj;

	_mCameraDirection = result.GetVector();
	_mUpVector = result2.GetVector();
	_mRightVector = _mCameraDirection.CrossProduct(_mUpVector);

	UpdateViewMatrix();
}


void MainCamera::ZoomCamera(float amount)
{
	//TODO
}


void MainCamera::SetCameraFOV(float fov)
{
	_mFOV = fov;
}


float MainCamera::GetCameraFOV()
{
	return _mFOV;
}
