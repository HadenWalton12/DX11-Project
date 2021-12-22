#include "InputComponent.h"

InputComponent::~InputComponent()
{
}

bool InputComponent::InitDirectInput(HINSTANCE hInstance)
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

void InputComponent::DetectWASDMovement(CameraComponent* camera_instance)
{

    XMFLOAT3 CameraPosition = camera_instance->GetPosition();
    XMFLOAT3 CameraDirection = camera_instance->GetDirection();
    DIMOUSESTATE mouseCurrState;

    BYTE keyboardState[256];

    DIKeyBoard->Acquire();
    DIMouse->Acquire();

    DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
    DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);


  
    //Forward
    if (keyboardState[DIK_W] & 0x80)
    {
        CameraPosition.z -= 0.001;
    }

    //Backwards
    if (keyboardState[DIK_S] & 0x80)
    {
        CameraPosition.z += 0.001;
    }

    //Right
    if (keyboardState[DIK_D] & 0x80)
    {
        CameraPosition.x -= 0.001;
    }

    //Left
    if (keyboardState[DIK_A] & 0x80)
    {
        CameraPosition.x += 0.001;
    }

    //Up
    if (keyboardState[DIK_SPACE] & 0x80)
    {
        CameraPosition.y += 0.1;
    }

    //Down
    if (keyboardState[DIK_LSHIFT] & 0x80)
    {
        CameraPosition.y -= 0.1;
    }

    //Look Vertical
    if (mouseCurrState.lY != mouseLastState.lY)
    {
        CameraDirection.y -= (mouseCurrState.lY * 0.05f);
    }

    //Look Horizontal
    if ( mouseLastState.lX)
    {
        CameraDirection.x -= (mouseCurrState.lX * 0.05f);
    }

    //Update 
    camera_instance->SetDirection(CameraDirection);
    camera_instance->SetPosition(CameraPosition);



}

