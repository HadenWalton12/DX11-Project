#include "Plane.h"
void Plane::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}

void Plane::CalculateTransformation()
{
	Timer t;
	XMMATRIX scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
	XMMATRIX translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x * t.time, ObjectRotation.y, ObjectRotation.z);


	XMStoreFloat4x4(&world, scale * translation * rotation);
}
