#pragma once
#include "EntityTransformation.h"
#include "RenderCommands.h"
class Star 
{
public:
	Star::Star(ID3D11Device* device, ID3D11DeviceContext* device_context, XMFLOAT4X4 world, ID3D11VertexShader* VS, ID3D11PixelShader* PS, MeshData _Mesh , ID3D11Buffer* CB)
	{
		
		_pPipelineCommands->UpdateConstantBuffer(world);






	}

	RenderingCommand* _pPipelineCommands;
};