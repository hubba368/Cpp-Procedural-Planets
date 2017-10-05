#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include <math.h>
#include <cmath>

/**
*
*/
class MainCamera
{
private:

	Matrix4x4	_mViewMatrix;
	Matrix4x4	_mProjectionMatrix;
	Vector3		_mCameraPosition;
	Vector3		_mUpVector;
	Vector3		_mRightVector;
	Vector3		_mViewVector;
	Vector3		_mCameraDirection;
	float		_mFOV;
	float		_mAspectRatio;

	/// Converts degrees to radians, from input of type float.
	float		DegToRads(float value);

	/// Converts to radians from degrees
	float		RadToDegs(float value);

public:

	MainCamera();
	~MainCamera();

	/// Initialises the camera matrices.
	void		InitialiseCamera();

	/// Sets the camera position to a new position.
	void		SetCameraPosition(Vector3* pos);

	/// Sets the view to face a specific point.
	void		SetLookAtPoint(Vector3* lookPos);

	/// Sets the aspect ratio of the camera view.
	void		SetAspectRatio(float ratio);

	/// Sets the projection matrix.
	void		SetProjectionMatrix(float fovy, float aspect, float zNear, float zFar);

	/// Updates the view matrix, should be called on any matrix calculation.
	void		UpdateViewMatrix();

	/// Gets the view matrix.
	Matrix4x4*		GetViewMatrix();

	/// Gets the projection matrix.
	Matrix4x4*		GetProjectionMatrix();

	/// Moves the camera to the left or right.
	void		StrafeCamera(float amount);

	/// Moves the camera forwards or backwards.
	void		DollyCamera(float amount);

	/// Moves the camera up or down.
	void		PedCamera(float amount);

	/// Rotates the camera in a given direction.
	void		RotateCamera(float yaw, float pitch, float roll);

	/// Zooms the view of the camera in or out.
	void		ZoomCamera(float amount);

	/// Sets the field of view of the camera.
	void		SetCameraFOV(float fov);

	/// Gets the field of view of the camera.
	float		GetCameraFOV();




};

