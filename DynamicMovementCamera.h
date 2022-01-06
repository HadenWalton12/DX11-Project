#pragma once
#include "Camera.h"
#include "PlaneCamera.h"


class DynamicMovementCamera : public Camera
{
public:
	DynamicMovementCamera(XMFLOAT3 camera_position, FLOAT yaw, FLOAT pitch, FLOAT roll) : _Camera_Position(camera_position), _Yaw(yaw), _Pitch(pitch), _Roll(roll)
	{
		InitialiseView();
		InitialiseProjection();
	}

	void InitialiseView() override
	{
		CameraRotationMatrix = XMMatrixRotationRollPitchYaw(_Pitch, _Yaw, _Roll);
		XMVECTOR Direction;
		Direction = XMVector3TransformCoord(DefaultForward, CameraRotationMatrix);
		Direction = XMVector3Normalize(Direction);

		XMVECTOR Eye = XMVectorSet(_Camera_Position.x, _Camera_Position.y, _Camera_Position.z, 0.0f);
		XMVECTOR UP = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		XMStoreFloat4(&light.EyePosW, Eye);

		//Initalize view matrix
		XMStoreFloat4x4(&_View, XMMatrixLookToLH(Eye, Direction, UP));

	}
	void InitialiseProjection() override
	{
		XMStoreFloat4x4(&_Projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, _NearDepth, _FarDepth));
	}

	void UpdateCamera()override
	{
		XMVECTOR Direction, Position, UP;
		CameraRotationMatrix = XMMatrixRotationRollPitchYaw(_Pitch, _Yaw, _Roll);
		Direction = XMVector3TransformCoord(DefaultForward, CameraRotationMatrix);
		Direction = XMVector3Normalize(Direction);

		Position = XMVectorSet(_Camera_Position.x, _Camera_Position.y, _Camera_Position.z, 0.0f);
		UP = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		//Initalize view matrix
		XMStoreFloat4x4(&_View, XMMatrixLookToLH(Position, Direction, UP));
	}

	// Setters
	virtual void SetPosition(XMFLOAT3 camera_position)
	{_Camera_Position = camera_position;}
	// Set Camera Direction
	void SetPitch(FLOAT pitch)
	{_Pitch = pitch;}
	void SetYaw(FLOAT yaw)
	{_Yaw = yaw;}
	void SetRoll(FLOAT roll)
	{_Roll = roll;}

	//Getters
	XMFLOAT4X4 GetView() override
	{return _View;}
	XMFLOAT4X4 GetProjection() override
	{return _Projection;}
	XMFLOAT3 GetPosition()
	{return _Camera_Position;}

	//Get Camera Direction
	FLOAT GetPitch()
	{return _Pitch;}
	FLOAT GetYaw()
	{return _Yaw;}
	FLOAT GetRoll()
	{return _Roll;}

private:

	XMFLOAT3 _Camera_Position;

	//Rotation on the Z-Axis
	FLOAT _Pitch;
	//Rotation on the Y-Axis
	FLOAT _Yaw;
	//Rotation of the X-Axis - Unique for the object 
	FLOAT _Roll;

	XMMATRIX CameraRotationMatrix;
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);

	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection;


	LigthtingValues light;
};
