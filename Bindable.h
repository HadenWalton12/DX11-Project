#pragma once
#include "GraphicComponent.h"


class Bindable
{
public:
	//Initializer List - Allow us to initalizer data members
	Bindable(ID3D11Device* device , ID3D11DeviceContext* device_context , ID3D11Buffer* CB) : _pd3dDevice(device) , _pDeviceContext(device_context) {}

	virtual void SetShaders(ID3D11InputLayout* VL, ID3D11VertexShader* VS, ID3D11Buffer* CB, ID3D11PixelShader* PS, ID3D11SamplerState* sampler) {}
	virtual void SetVertexBuffer() {}
	virtual void SetIndexBuffer() {} 

protected:
	ID3D11Device * _pd3dDevice;									//Virtual Representation of Video Card , used to create resources for application , resources exuted using device context
	ID3D11DeviceContext* _pDeviceContext;
};

