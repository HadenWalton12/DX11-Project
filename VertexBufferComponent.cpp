
#include "VertexBufferComponent.h"

void VertexBufferComponent::SwitchVertexBuffer(ID3D11Buffer* VB, GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
}
