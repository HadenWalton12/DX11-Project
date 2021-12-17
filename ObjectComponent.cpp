#include "ObjectComponent.h"

GameObjects::GameObjects(GraphicComponent* _gfx, char* file) : _gfx(_gfx) , _Tex(_Tex) , world(world)
{
	_mesh = OBJLoader::Load(file, _gfx->GetDevice());

}

GameObjects::~GameObjects()
{
}



void GameObjects::Update(GraphicComponent* gfx)
{

	CalculateTransformation(); 
}

void GameObjects::Draw()
{
	_gfx->UpdateConstantBuffer(world);

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
void GameObjects::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB , GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}

void GameObjects::CalculateTransformation()
{
}






void GameObjects::SetRotation(float x, float y, float z)
{
	ObjectRotation = XMFLOAT3(x, y, z);
}

void GameObjects::SetTranslation(float x, float y, float z)
{
	ObjectTranslation = XMFLOAT3(x, y, z);
}
void GameObjects::BindShaders()
{
}
void GameObjects::SetScale(float x, float y, float z)
{

	ObjectScale = XMFLOAT3( x,  y,  z);
}
