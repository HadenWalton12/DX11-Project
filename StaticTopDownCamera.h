#pragma once
#include "Camera.h"

class StaticTopDownCamera : public Camera
{
public:
	StaticTopDownCamera(XMFLOAT3 camera_position, XMFLOAT3 camera_direction) : _Camera_Position(camera_position), _Camera_Direction(camera_direction)
	{
		InitialiseView();
		InitialiseProjection();
	}

	void InitialiseView() override
	{
		XMVECTOR Direction, Position, UP;

		
		Position  = XMVectorSet(_Camera_Position.x, _Camera_Position.y, _Camera_Position.z, 0.0f);
		Direction = XMVectorSet(_Camera_Direction.x, _Camera_Direction.y, _Camera_Direction.z, 0.0f);
		UP  = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		XMStoreFloat4(&light.EyePosW, Direction);

		//Initalize view matrix
		XMStoreFloat4x4(&_View, XMMatrixLookToLH(Position, Direction, UP));

	}
	void InitialiseProjection() override
	{
		XMStoreFloat4x4(&_Projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, _NearDepth, _FarDepth));
	}

	void UpdateCamera()override
	{


		XMVECTOR Direction, Position, UP;
		Position = XMVectorSet(_Camera_Position.x, _Camera_Position.y, _Camera_Position.z, 0.0f);
		Direction = XMVectorSet(_Camera_Direction.x, _Camera_Direction.y, _Camera_Direction.z, 0.0f);
		UP = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		XMStoreFloat4(&light.EyePosW, Direction);

		//Initalize view matrix
		XMStoreFloat4x4(&_View, XMMatrixLookToLH(Position, Direction, UP));

	}

	// Setters
	virtual void SetPosition(XMFLOAT3 camera_position)
	{
		_Camera_Position = camera_position;
	}

	// Set Camera Direction
	void SetPitch(FLOAT pitch)
	{
		_Pitch = pitch;
	}
	void SetYaw(FLOAT yaw)
	{

		_Yaw = yaw;
	}
	void SetRoll(FLOAT roll)
	{
		_Roll = roll;

	}
	//Getters
	XMFLOAT4X4 GetView() override
	{

		return _View;
	}
	XMFLOAT4X4 GetProjection() override
	{

		return _Projection;
	}
	XMFLOAT3 GetPosition()
	{
		return _Camera_Position;
	}

	//Get Camera Direction
	FLOAT GetPitch()
	{
		return _Pitch;
	}
	FLOAT GetYaw()
	{

		return _Yaw;
	}
	FLOAT GetRoll()
	{
		return _Roll;

	}
private:
	XMFLOAT3 _Camera_Position;
	XMFLOAT3 _Camera_Direction;
	//Rotation on the Z-Axis
	FLOAT _Pitch;
	//Rotation on the Y-Axis
	FLOAT _Yaw;
	//Rotation of the X-Axis - Unique for the object 
	FLOAT _Roll;

	XMVECTOR DefaultForward = XMVectorSet(0.0f, -0.00000001f, 0.0f, 0.0f);

	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection;

	//Used For Camera rotational Matrix Calculations
	XMMATRIX CameraRotationMatrix;

	LigthtingValues light;
};
