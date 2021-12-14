#pragma once
#include "OBJLoader.h"


#include <vector>
#include "DDSTextureLoader.h"
#include "SimpleVertexStructure.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"
#include "TimeStructure.h"
#include "MeshStructure.h"

#include "RenderCommands.h"
#include "EntityTransformation.h"
class GameObjects
{
public:
	GameObjects(ID3D11Device* device, ID3D11DeviceContext* device_context , MeshData mesh , ID3D11VertexShader* VS , ID3D11PixelShader* PS, ID3D11Buffer* CB , XMFLOAT4X4 world ,
		char* file , ID3D11ShaderResourceView* texture);

				


private:




protected:
	ID3D11Device* _pDevice;
	ID3D11DeviceContext* _pDeviceContext;
	MeshData _Mesh;	
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11Buffer* _pConstantBuffer;
	XMFLOAT4X4				_World;
	char* File;
	ID3D11ShaderResourceView* _Texture;


	RenderingCommand* rtx;
	EntityTransformation* Tranforms


};

