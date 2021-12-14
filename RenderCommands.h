#pragma once
#include "ConstantStructure.h"
#include "LightingValuesStructure.h"
#include "Vertex.h"
#include "CameraComponent.h"
#include "ShaderCompiler.h"
class RenderingCommand
{
public:
	RenderingCommand(ID3D11Device* device , ID3D11DeviceContext* device_context) : _pDevice(device) , _pDeviceContext(device_context)
	{}

	void Swap(IDXGISwapChain* swap_chain)
	{
		swap_chain->Present(0, 0);
	}

	void BindVertexShader(ID3D11VertexShader* VS)
	{
		_pDeviceContext->VSSetShader(VS, nullptr, 0);
	}


	void BindPixelShader(ID3D11PixelShader* PS)
	{
		_pDeviceContext->PSSetShader(PS, nullptr, 0);
	}

	void BindSampler(ID3D11SamplerState* sampler)
	{
		_pDeviceContext->PSSetSamplers(0, 1, &sampler);
	}

	//Bind Index Buffer passed to pipeline 
	void BindVertexBuffer(ID3D11Buffer* vertex_buffer , UINT stride , UINT offset)
	{
		_pDeviceContext->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
	}


	void SwitchCamera(CameraComponent* camera)
	{
		_Camera = camera;
	}

	ID3D11Device* GetDevice()
	{
		return _pDevice;
	}

	void UpdateConstantBuffer(XMFLOAT4X4 world , ID3D11Buffer* CB)
	{
		ConstantBuffer constantbuffer;
		LigthtingValues lightvalue;
		XMMATRIX _world = XMLoadFloat4x4(&world);
		XMMATRIX view = XMLoadFloat4x4(&_Camera->GetView());
		XMMATRIX projection = XMLoadFloat4x4(&_Camera->GetProjection());


		constantbuffer.mWorld = XMMatrixTranspose(_world);
		constantbuffer.mView = XMMatrixTranspose(view);
		constantbuffer.mProjection = XMMatrixTranspose(projection);

		constantbuffer.LightVecW = lightvalue.light_direction;
		constantbuffer.DiffuseLight = lightvalue.diffuse_light;
		constantbuffer.DiffuseMtrl = lightvalue.diffuse_material;
		constantbuffer.AmbientLight = lightvalue.ambient_light;
		constantbuffer.AmbientMtrl = lightvalue.ambient_material;
		constantbuffer.EyePosW = lightvalue.EyePosW;
		constantbuffer.SpecularPower = lightvalue.specular_power;
		constantbuffer.SpecularLight = lightvalue.specular_light;
		constantbuffer.SpecularMtrl = lightvalue.specular_material;

		_pDeviceContext->UpdateSubresource(CB, 0, nullptr, &constantbuffer, 0, 0);

	}


	void CreateTexture(wchar_t* path , std::vector<ID3D11ShaderResourceView*> textures)
	{

		ID3D11ShaderResourceView* texture;
		CreateTexture(path, &texture);
		textures.push_back(texture);


	}

	HRESULT CreateTexture(wchar_t* filepath, ID3D11ShaderResourceView** texture)
	{
		return CreateDDSTextureFromFile(_pDevice, filepath, nullptr, texture);
	}


	void BindTextures(int startSlot, int count, std::vector<ID3D11ShaderResourceView*> textures )
	{
		_pDeviceContext->PSSetShaderResources(startSlot, count, &textures[0]);
	}

	MeshData LoadMesh(MeshData mesh ,char* file)
	{
		mesh = OBJLoader::Load(file, _pDevice);
		return mesh;
	}

	MeshData LoadMesh(ID3D11Buffer* VB , UINT offset, UINT stride , ID3D11Buffer* IB ,UINT index_count ,MeshData mesh)
	{

		mesh.VertexBuffer = VB;
		mesh.VBOffset = offset;
		mesh.VBStride = stride;
		mesh.IndexBuffer = IB;
		mesh.IndexCount = index_count;

		return mesh;
	}


	


	ID3D11Device* _pDevice;
	ID3D11DeviceContext* _pDeviceContext;
	CameraComponent* _Camera;
	ShaderCompiler* _pShaderCompiler;
	
};