#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")


#include "CameraComponent.h"
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
    void DetectWASDMovement(CameraComponent* Camera);
    
 IDirectInputDevice8* DIKeyBoard;
    IDirectInputDevice8* DIMouse;

    DIMOUSESTATE mouseLastState;
    LPDIRECTINPUT8 DirectInput;

private:


   

};

