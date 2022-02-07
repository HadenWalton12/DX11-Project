#include "ObjectComponent.h"

GameObjects::GameObjects(RenderCommands* render_commands) : _pRenderCommand(render_commands) , _Tex(_Tex)
{
	
	
}

GameObjects::~GameObjects()
{
	Cleanup();
}

void GameObjects::Update()
{

	WorldTransformations();

}

void GameObjects::Draw()
{
	BindShaders();
	_pRenderCommand->UpdateConstantBuffer(_World , GetSurface() );
	SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer , _pRenderCommand);
	_Tex->BindTextures(0, _Textures.size(), _Textures , _pRenderCommand);
	_pRenderCommand->GetDeviceContext()->DrawIndexed(_mesh.IndexCount, 0, 0);
}

void GameObjects::Cleanup()
{
	
	delete(_Tex);
	delete(_pRenderCommand);
	_Textures.clear();
}

void GameObjects::SetWorld(XMFLOAT4X4 world)
{
	_World = world;
}


void GameObjects::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* texture;
	_Tex->CreateTexture(path, &texture , _pRenderCommand);
	_Textures.push_back(texture);
}
void GameObjects::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB , RenderCommands* render_commands)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_pRenderCommand->GetDeviceContext()->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_pRenderCommand->GetDeviceContext()->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}



//Virtual Function
void GameObjects::WorldTransformations()
{
}

//Virtual Function
void GameObjects::BindShaders()
{

}


