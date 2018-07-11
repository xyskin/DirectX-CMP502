////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


//////////////
// INCLUDES //
//////////////
#include <dinput.h>
#include <unordered_map>


////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	bool IsUpPressed();
	bool IsDownPressed();
	bool IsLeftPressed();
	bool IsRightPressed();
	bool Is1Pressed();
	bool Is2Pressed();
	bool Is4Pressed();
	bool Is5Pressed();
	bool Is8Pressed();
	bool Is7Pressed();
	bool IsMouse1Clicked();

	bool IsPDown();

	bool IsZDown();
	bool IsXDown();
	bool IsCDown();
	bool IsVDown();
	bool IsBDown();
	bool IsNDown();
	bool IsMDown();
	
	bool IsADown();
	bool IsSDown();
	bool IsDDown();
	bool IsFDown();
	bool IsGDown();
	bool IsHDown();
	bool IsJDown();
	
	bool IsQDown();
	bool IsWDown();
	bool IsEDown();
	bool IsRDown();
	bool IsTDown();
	bool IsYDown();
	bool IsUDown();

	bool IsSpaceDown();
	void GetMouseLocation(int&, int&);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif