#include "ObjectComponent.h"

GameObjects::GameObjects(GraphicComponent* _gfx, char* file) : _gfx(_gfx) , _Shader(_Shader) , _Tex(_Tex)
{
	
	_mesh = OBJLoader::Load(file, _gfx->GetDevice());
	Initialise();
}

GameObjects::~GameObjects()
{
}



void GameObjects::Update(GraphicComponent* gfx)
{

}

void GameObjects::Draw()
{
	_Shader->ComposeShader(_gfx);
	SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer , _gfx);
	_Tex->BindTextures(0, _Textures.size(), _Textures , _gfx);
	_gfx->_pImmediateContext->DrawIndexed(_mesh.IndexCount, 0, 0);



}



void GameObjects::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* texture;
	_Tex->CreateTexture(path, &texture , _gfx);
	_Textures.push_back(texture);
}

void GameObjects::Initialise()
{
	_Shader = new ShaderComponent();
	_Shader->CreateVertexShader(_gfx);
	_Shader->CreatePixelShader(_gfx);

}

void GameObjects::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB , GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}