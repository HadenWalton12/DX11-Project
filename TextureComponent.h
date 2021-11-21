#pragma once

#include "Structure.h"
#include "OBJLoader.h"
//Libraries used to create application 
//Makes it possible to create our window
#include <windows.h>
//Access to core DX functions 
#include <d3d11_1.h>
//Allows us to compile DX11 Code
#include <d3dcompiler.h>
//Math Library
#include <directxmath.h>
#include <directxcolors.h>
//Libraries used to create application 
//Makes it possible to create our window
#include <windows.h>
//Access to core DX functions 
#include <d3d11_1.h>
//Allows us to compile DX11 Code
#include <d3dcompiler.h>
//Math Library
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"



#include "DDSTextureLoader.h"
#include "GraphicComponent.h"
//Allows us to easily call reference upon our DX naming conventions
using namespace DirectX;

class TextureComponent
{
public:
	TextureComponent();
	~TextureComponent();
	HRESULT CreateTexture(wchar_t* filepath, ID3D11ShaderResourceView** texture , GraphicComponent* gfx);
	void BindTextures(int startSlot, int count, std::vector<ID3D11ShaderResourceView*> textures , GraphicComponent* gfx);
	void ClearTexture(GraphicComponent* gfx);

private:
		GraphicComponent* _gfx;
	ID3D11Device* _device;

};

