#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")


#include "DynamicMovementCamera.h"
#include "PlaneCamera.h"
#include "Plane.h"
#include <dinput.h>

//Alter
class InputComponent
{
public:
    InputComponent(HINSTANCE hInstance)
    {
        if (!InitDirectInput(hInstance))
        {
            MessageBox(0, L"Direct Input Initialization - Failed",
                L"Error", MB_OK);
        }

    }
	~InputComponent();

    bool InitDirectInput(HINSTANCE hInstance);

    void DetectWASDMovement();
    void DetectPlaneMovement(Plane* plane, XMFLOAT3 translate, XMFLOAT3 scale, XMFLOAT3 rotation);
 IDirectInputDevice8* DIKeyBoard;
    IDirectInputDevice8* DIMouse;

    DIMOUSESTATE mouseLastState;
    LPDIRECTINPUT8 DirectInput;

private:

    DynamicMovementCamera* _DynamicCamera;
    PlaneCamera* _PlaneCamera;
    
};

