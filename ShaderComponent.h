#pragma once

//ShaderComponent Depenencies
#include "GraphicComponent.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"
#include "OBJLoader.h"

//Libraries used to create application  

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming conventions

class ShaderComponent
{
public:
	//Constructor
	ShaderComponent();
	//Destructor
	~ShaderComponent();

	//Creates Vertex Shader , further compiles shader from file , this is done by compiling shader from fx file , then passing such data via local pPSBlob "Used to return data" to then pass into our VS Pointer , We also define the VertexShader Layout to which how we pass data into the shader (Tex , Normals , Vertexes) , this data will be later processed in PixelShader.
	HRESULT CreateVertexShader(GraphicComponent* gfx);

	//Creates Pixel Shader , further compiles shader from file , this is done by compiling shader from fx file , then passing such data via local pPSBlob "Used to return data" to then pass into our PS Pointer
	HRESULT CreatePixelShader(GraphicComponent* gfx);

	//We compose our VS and PS  , Calling initshader function ,and setting the initialised input layout for our vertex shader.
	void ComposeShader(GraphicComponent* gfx);
	
	//Reference DeviceContext to set shaders used in application to the ones initialised in this component , we call the function , passing in our created shaders from the CreateVPixel/VertexShader functions
	//We then reference the Constant buffers  , Constant Buffers are needed since this is where we store all scene related data , lighting , world/project/view matrix , eyepos . We pass in this data so we can process Vertex Transformations (Per-Vertex Lighting , Vertex Manipulation )and Pixel Transformations (Per-Pixel Lighting , Texturing)
	//We further set the sampler,  used for texturing.
	void InitialiseShaders(ID3D11VertexShader* VS, ID3D11PixelShader* PS , GraphicComponent* gfx);

	//Set the devicecontext to set the input Assemblers input layout
	void SetInputLayout(ID3D11InputLayout* layout , GraphicComponent* gfx);


//Private Objects
private:

	//Input Layout holds definition of how to feed vertex data laid out in memory (Buffers)into input-assembler stage
	ID3D11InputLayout* _pVertexLayout;
	
	// Interfaces/manages vertex shader  that controls vertex-shader stage (stage on pipeline)
	ID3D11VertexShader* _pVertexShader;	

	//Interfaces/manages the pixel shader that controls pixel-shader stage (Stage on PipeLine) 
	ID3D11PixelShader* _pPixelShader;

//Private Functions
private:

	//Compiles Shader Code From HLSL Files - Referenced within our "CreateShader" functions , pass Shader File , to process into PS & VS Shaders to utilise shader code , applying shader effects to data within both shaders
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

};

