#include "CameraComponent.h"

CameraComponent::CameraComponent(XMFLOAT3 camera_position, XMFLOAT3 camera_target, XMFLOAT3 camera_up, float windowWidth, float windowHeight, float nearDepth, float farDepth)
{

	SetView(camera_position , camera_target , camera_up);
	 _WindowWidth = windowWidth;
	_WindowHeight = windowHeight;
	_NearDepth = nearDepth;
	_FarDepth = farDepth;
	
	SetProjection();
	Camera_Position = camera_position;
	Camera_Target = camera_target;
	Camera_Up = camera_up;
}

void CameraComponent::SetEye(XMFLOAT3 eye)
{
	Camera_Position = XMFLOAT3(eye.x, eye.y, eye.z);
}

void CameraComponent::SetAt(XMFLOAT3 at)
{
	Camera_Target = XMFLOAT3(at.x , at.y , at.z);
}





XMFLOAT3 CameraComponent::GetEye()
{
	return Camera_Position;
}

XMFLOAT3 CameraComponent::GetAt()
{
	return XMFLOAT3();
}

XMFLOAT4X4 CameraComponent::GetView()
{
	return _View;
}

XMFLOAT4X4 CameraComponent::GetProjection()
{
	return _Projection;
}

void CameraComponent::SetView(XMFLOAT3 camera_position, XMFLOAT3 camera_target, XMFLOAT3 camera_up)
{

	LigthtingValues lightvalue;
	XMVECTOR Eye = XMVectorSet(camera_position.x , camera_position.y , camera_position.z  , 0.0f);
	XMVECTOR Target = XMVectorSet(camera_target.x, camera_target.y, camera_target.z, 0.0f);
	XMVECTOR Up = XMVectorSet(camera_up.x, camera_up.y, camera_up.z, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	up = XMVector3Transform(up, Rotation);
	XMStoreFloat4(&lightvalue.EyePosW, Eye);
	//Initalize view matrix
	XMStoreFloat4x4(&_View, XMMatrixLookAtLH(Eye, Target, Up));
}

void CameraComponent::SetProjection()
{

	// Initialize the projection matrix
	XMStoreFloat4x4(&_Projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));
}

void CameraComponent::CameraMovement(float d)
{

}

void CameraComponent::Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth)
{
	_WindowWidth = windowWidth;
	_WindowHeight = windowHeight;
	_NearDepth = nearDepth;
	_FarDepth = farDepth;




}

void CameraComponent::Update()
{

	XMVECTOR Eye = XMVectorSet(Camera_Position.x, Camera_Position.y, Camera_Position.z, 0.0f);
	XMVECTOR Target = XMVectorSet(Camera_Target.x, Camera_Target.y, Camera_Target.z, 0.0f);
	XMVECTOR Up = XMVectorSet(Camera_Up.x, Camera_Up.y, Camera_Up.z, 0.0f);


	XMStoreFloat4x4(&_View, XMMatrixLookAtLH(Eye, Target, Up));

}
