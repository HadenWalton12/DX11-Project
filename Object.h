#pragma once
#include "RenderCommands.h"
#include "MeshStructure.h"
#include "Transformation.h"
#include "TextureComponent.h"
#include "OBJLoader.h"
struct Object
{
	char* Name;
	std::vector<ID3D11ShaderResourceView*> _Textures;
	MeshData _Mesh;
	Surface _ObjectMaterial;
	Transformation _ObjectTransformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader _VertexShader;
	PixelShader _PixelShader;
	RenderCommands* _pRenderCommands;
	TextureComponent* _Tex;
	Object() = default;
	
	Object(RenderCommands* render_commands, wchar_t* texture ,TextureComponent* Tex ,  char* object)
	{
		_Tex = Tex;
		_pRenderCommands = render_commands;
		Name = object;
		CreateTexture(texture);
		_Mesh = OBJLoader::Load(object, render_commands->GetDevice());
	}

	void SetTransformation(XMFLOAT3 translation , XMFLOAT3 scale , XMFLOAT3 rotation)
	{
		_ObjectTransformation = Transformation(translation, scale, rotation);
	}

	void SetTransformation(XMFLOAT3 translation, XMFLOAT3 scale, XMFLOAT3 rotation , Timer t)
	{
		_ObjectTransformation = Transformation(translation, scale, rotation);
		t.Update();
	}


	void SetSurface(XMFLOAT4 ambient , XMFLOAT4 diffuse , XMFLOAT4 specular , FLOAT specular_power)
	{
		_ObjectMaterial = Surface(ambient, diffuse, specular, specular_power);
	}

	void SetPixelShader(WCHAR* file_path)
	{
		_PixelShader = PixelShader(file_path, _pRenderCommands->GetDevice());
	}
	void SetVertexShader(WCHAR* file_path)
	{
		_VertexShader = VertexShader(file_path, _pRenderCommands->GetDevice(), _pRenderCommands->GetDeviceContext());
	}


	void Draw()
	{
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;

		_pRenderCommands->BindVertexShader(_VertexShader.GetVertexShader());
		_pRenderCommands->BindPixelShader(_PixelShader.GetPixelShader());
		_pRenderCommands->UpdateConstantBuffer(_ObjectTransformation.GetWorld(), _ObjectMaterial);
		_pRenderCommands->GetDeviceContext()->IASetVertexBuffers(0, 1, &_Mesh.VertexBuffer, &stride, &offset);
		_pRenderCommands->GetDeviceContext()->IASetIndexBuffer(_Mesh.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		_Tex->BindTextures(0, _Textures.size(), _Textures, _pRenderCommands);
		_pRenderCommands->GetDeviceContext()->DrawIndexed(_Mesh.IndexCount, 0, 0);

	}

	void Update()
	{



	}

	void CreateTexture(wchar_t* path)
	{
		ID3D11ShaderResourceView* texture;
		_Tex->CreateTexture(path, &texture, _pRenderCommands);
		_Textures.push_back(texture);
	}





	MeshData GetMesh()
	{
		return _Mesh;
	}
};