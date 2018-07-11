////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;


	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void InputClass::Shutdown()
{
	// Release the mouse.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the main interface to direct input.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}


bool InputClass::Frame()
{
	bool result;


	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}


bool InputClass::ReadKeyboard()
{
	HRESULT result;


	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}


bool InputClass::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}


void InputClass::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}


bool InputClass::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	return m_keyboardState[DIK_ESCAPE] & 0x80 ? true : false;
}

bool InputClass::IsUpPressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_UP] & 0x80 ? true : false;
}
bool InputClass::IsDownPressed()
{
	// Do a bitwise and on the keyboard state to check if the A is currently being pressed.
	return m_keyboardState[DIK_DOWN] & 0x80 ? true : false;
}
bool InputClass::IsLeftPressed()
{
	// Do a bitwise and on the keyboard state to check if the S is currently being pressed.
	return m_keyboardState[DIK_LEFT] & 0x80 ? true : false;
}
bool InputClass::IsRightPressed()
{
	// Do a bitwise and on the keyboard state to check if the D is currently being pressed.
	return m_keyboardState[DIK_RIGHT] & 0x80 ? true : false;
}
bool InputClass::Is1Pressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_NUMPAD1] & 0x80 ? true : false;
}
bool InputClass::Is2Pressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_NUMPAD2] & 0x80 ? true : false;
}
bool InputClass::Is4Pressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_NUMPAD4] & 0x80 ? true : false;
}
bool InputClass::Is5Pressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_NUMPAD5] & 0x80 ? true : false;
}
bool InputClass::Is7Pressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_NUMPAD7] & 0x80 ? true : false;
}
bool InputClass::Is8Pressed()
{
	// Do a bitwise and on the keyboard state to check if the W is being pressed.
	return m_keyboardState[DIK_NUMPAD8] & 0x80 ? true : false;
}

bool InputClass::IsPDown()
{
	static int times = 0;
	if (m_keyboardState[DIK_P] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}

bool InputClass::IsZDown() {
	static int times = 0;
	if (m_keyboardState[DIK_Z] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsXDown() {
	static int times = 0;
	if (m_keyboardState[DIK_X] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsCDown() {
	static int times = 0;
	if (m_keyboardState[DIK_C] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsVDown() {
	static int times = 0;
	if (m_keyboardState[DIK_V] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}

		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsBDown() {
	static int times = 0;
	if (m_keyboardState[DIK_B] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsNDown() {
	static int times = 0;
	if (m_keyboardState[DIK_N] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsMDown() {
	static int times = 0;
	if (m_keyboardState[DIK_M] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}

bool InputClass::IsADown() {
	static int times = 0;
	if (m_keyboardState[DIK_A] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsSDown() {
	static int times = 0;
	if (m_keyboardState[DIK_S] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsDDown() {
	static int times = 0;
	if (m_keyboardState[DIK_D] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsFDown() {
	static int times = 0;
	if (m_keyboardState[DIK_F] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}

		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsGDown() {
	static int times = 0;
	if (m_keyboardState[DIK_G] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsHDown() {
	static int times = 0;
	if (m_keyboardState[DIK_H] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsJDown() {
	static int times = 0;
	if (m_keyboardState[DIK_J] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}

bool InputClass::IsQDown() {
	static int times = 0;
	if (m_keyboardState[DIK_Q] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsWDown() {
	static int times = 0;
	if (m_keyboardState[DIK_W] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsEDown() {
	static int times = 0;
	if (m_keyboardState[DIK_E] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsRDown() {
	static int times = 0;
	if (m_keyboardState[DIK_R] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}

		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsTDown() {
	static int times = 0;
	if (m_keyboardState[DIK_T] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsYDown() {
	static int times = 0;
	if (m_keyboardState[DIK_Y] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}
bool InputClass::IsUDown() {
	static int times = 0;
	if (m_keyboardState[DIK_U] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}

bool InputClass::IsMouse1Clicked() 
{
	return m_mouseState.rgbButtons[0] & 0x80 ? true : false;
}

bool InputClass::IsSpaceDown() 
{
	static int times = 0;
	if (m_keyboardState[DIK_SPACE] & 0x80)
	{
		times++;
		if (times == 1) {
			return true;
		}
		return false;
	}
	times = 0;
	return false;
}

void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}