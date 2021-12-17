#pragma once
#include "OBJLoader.h"
#include "RenderCommands.h"
#include "TextureComponent.h"

#include <vector>
#include "DDSTextureLoader.h"
#include "SimpleVertexStructure.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"
#include "TimeStructure.h"
#include "MeshStructure.h"

class GameObjects
{
public:
	GameObjects(RenderCommands* render_command, char* file);   //Constructor , when child class is called , we will need to initialise a gfx component and file , this is how we create our objects.Within we call OBJ load method , passing in our "_pd3dDevice" function , and "file" , so when we create child class
	//we can call the device pointer and the file name as a string to initialise the object loading , to which we call the draw the loaded mesh object
	~GameObjects();

	void Update();										//Used to reference instances where the object is to be updated
	void Draw();
	
	void SetWorld(XMFLOAT4X4 world);
	//Draw method , to how we draw objects
	void CreateTexture(wchar_t* path);					//Creates Texture

private:

	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, RenderCommands* render_command);

protected:
	MeshData _mesh;										//Store object data within a mesh
	std::vector<ID3D11ShaderResourceView*> _Textures;	//Texture Vector to store multiple textures
	virtual void WorldTransformations();
	virtual void BindShaders();
	RenderCommands* _pRenderCommand;							//Graphic Component Class pointer, needed to reference graphiccomponents for creation of object
	
	TextureComponent* _Tex;								//Texture Component Class pointer, needed to assign objects with textures
	XMFLOAT4X4 _World;


};

