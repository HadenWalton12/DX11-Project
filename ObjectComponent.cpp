#include "ObjectComponent.h"

GameObjects::GameObjects(RenderingPipeline* pipeline) : _pPipeline(pipeline), world(world)
{

	Initialise();

}

GameObjects::~GameObjects()
{


}


void GameObjects::Update()
{
	CalculateTransformation();
}

void GameObjects::Render()
{


	/*
	_gfx->UpdateConstantBuffer(world);
	_Shader->ComposeShader(_gfx);
	SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer , _gfx);
	_Tex->BindTextures(0, _Textures.size(), _Textures , _gfx);
	_gfx->_pImmediateContext->DrawIndexed(_mesh.IndexCount, 0, 0);
	*/


}




void GameObjects::Initialise()
{
	

}


void GameObjects::CalculateTransformation()
{


}

