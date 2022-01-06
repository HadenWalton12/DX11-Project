#pragma once
#include "DynamicMovementCamera.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code
#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library

using namespace DirectX; 

class InputComponent
{
public:
    InputComponent(HINSTANCE hInstance)
    {
        if (!InitDirectInput(hInstance))
        {
            MessageBox(0, L"Direct Input Initialization - Failed", L"Error", MB_OK);
        }
    }


	~InputComponent();
    void Cleanup();
    bool InitDirectInput(HINSTANCE hInstance);

    void DetectWASDMovement(DynamicMovementCamera* camera_instance);

    IDirectInputDevice8* DIKeyBoard;
    IDirectInputDevice8* DIMouse;

    DIMOUSESTATE MouseLastState;
    LPDIRECTINPUT8 DirectInput;
};

