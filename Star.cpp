#include "Star.h"

void Star::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}
