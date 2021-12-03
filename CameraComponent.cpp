#include "CameraComponent.h"

CameraComponent::CameraComponent(XMVECTOR position, XMVECTOR at, XMVECTOR up, float windowWidth, float windowHeight, float nearDepth, float farDepth)
{
	this->eye = position;
	this->at =  at;
	this->up = up;

	 _WindowWidth = windowWidth;
	_WindowHeight = windowHeight;
	_NearDepth = nearDepth;
	_FarDepth = farDepth;

	Reshape(windowWidth, windowHeight, nearDepth, farDepth);
}

void CameraComponent::SetEye(XMFLOAT3 eye)
{
	this->eye = eye;
}

void CameraComponent::SetAt(XMFLOAT3 at)
{
	this->at = at;
}

void CameraComponent::SetUp(XMFLOAT3 up)
{
	this->up = up;
}

XMFLOAT3 CameraComponent::GetEye()
{
	return eye;
}

XMFLOAT3 CameraComponent::GetAt()
{
	return at;
}

XMFLOAT3 CameraComponent::GetUp()
{
	return up;
}

XMFLOAT4X4 CameraComponent::GetView()
{
	return _View;
}

XMFLOAT4X4 CameraComponent::GetProjection()
{
	return _Projection;
}

void CameraComponent::Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth)
{
	_WindowWidth = windowWidth;
	_WindowHeight = windowHeight;
	_NearDepth = nearDepth;
	_FarDepth = farDepth;


	// Initialize the projection matrix
	XMStoreFloat4x4(&_Projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));

}

void CameraComponent::Update()
{
	LigthtingValues lightvalue;
		// Initialize values of view matrix - Defines values of 4x4 View matrix 

	XMStoreFloat4(&lightvalue.EyePosW, camPosition);


	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	camPosition += moveLeftRight * camRight;
	camPosition += moveBackForward * camForward;
	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;

	XMStoreFloat4x4(&_View, XMMatrixLookAtLH(camPosition, camTarget, camUp));


}
