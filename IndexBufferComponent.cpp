#include "IndexBufferComponent.h"
void IndexBufferComponent::SwitchIndexBuffer(ID3D11Buffer* IB, GraphicComponent* _gfx)
{
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}
