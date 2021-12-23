#include "InputComponent.h"
#define TO_RADIANS 3.14/180 //Converts degrees to radians upon multiplication
InputComponent::~InputComponent()
{
}

bool InputComponent::InitDirectInput(HINSTANCE hInstance )
{

    DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL);

    //Create Keyboard Device
    DirectInput->CreateDevice(GUID_SysKeyboard, &DIKeyBoard, NULL);

    //Create Mouse Device
    DirectInput->CreateDevice(GUID_SysMouse, &DIMouse, NULL);

    //Input format of device
    DIKeyBoard->SetDataFormat(&c_dfDIKeyboard);
    DIKeyBoard->SetCooperativeLevel(NULL, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    //Input format of mouse device
    DIMouse->SetDataFormat(&c_dfDIMouse);
    DIMouse->SetCooperativeLevel(NULL, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
    return true;
}

/*
void InputComponent::DetectWASDMovement()
{

    XMFLOAT3 CameraPosition = _DynamicCamera->GetPosition();

    DIMOUSESTATE mouseCurrState;

    BYTE keyboardState[256];

    DIKeyBoard->Acquire();
    DIMouse->Acquire();

    DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
    DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

    float yaw = _DynamicCamera->GetYaw();
    float pitch = _DynamicCamera->GetPitch();
    //Yaw & Pitch Calculations, We divide our pitch and yaw to control to sensitive of our mouse input
    
    //Forward
    if (keyboardState[DIK_W] & 0x80)
    {

        CameraPosition.x += cos((90 + 180) * TO_RADIANS) / 5.0;
        CameraPosition.z -= sin((90 + 180) * TO_RADIANS) / 5.0;

    }

    //Backwards
    if (keyboardState[DIK_S] & 0x80)
    {
        CameraPosition.x += cos((90) * TO_RADIANS) / 5.0;
        CameraPosition.z -= sin((90) * TO_RADIANS) / 5.0f;
    }

    //Right
    if (keyboardState[DIK_D] & 0x80)
    {
        CameraPosition.x += cos((90 - 90) * TO_RADIANS) / 5.0;
        CameraPosition.z -= sin((90 - 90) * TO_RADIANS) / 5.0;
    }

    //Left
    if (keyboardState[DIK_A] & 0x80)
    {
        CameraPosition.x += cos((90 + 90) * TO_RADIANS) / 5.0;
        CameraPosition.z -= sin((90 + 90) * TO_RADIANS) / 5.0;
    }

    //Up
    if (keyboardState[DIK_SPACE] & 0x80)
    {
        CameraPosition.y += cos((90 - 90) * TO_RADIANS) / 5.0;
    }

    //Down
    if (keyboardState[DIK_LSHIFT] & 0x80)
    {
        CameraPosition.y -= cos((90 - 90) * TO_RADIANS) / 5.0;
    }

    if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
    {
        yaw += mouseLastState.lX * 0.001f;

        pitch += mouseCurrState.lY * 0.001f;

        mouseLastState = mouseCurrState;
    }

    

    //Update 
    _DynamicCamera->SetPitch(pitch);
    _DynamicCamera->SetYaw(yaw);

    _DynamicCamera->SetPosition(CameraPosition);



}
*/