#include "MiniginPCH.h"
#include "Controller.h"


//Controller
dae::Controller::Controller(int controllerID, bool keyboard)
{
	pImpl = new ControllerImpl(controllerID, keyboard);
}
dae::Controller::~Controller()
{
	delete pImpl;
}
void dae::Controller::Update()
{
	pImpl->Update();

}

bool dae::Controller::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

bool dae::Controller::IsKeyDown(SDL_Keycode key) const
{
	return pImpl->IsKeyDown(key);
}

bool dae::Controller::IsKeyUp(SDL_Keycode key) const
{
	return pImpl->IsKeyUp(key);
}

bool dae::Controller::isKeyPressed(SDL_Keycode key) const
{
	
	return pImpl->isKeyPressed(key);
}

//void dae::Controller::DeadzoneLeftThumbstick()
//{
//	float RX = m_CurrentState.Gamepad.sThumbRX;
//	float RY = m_CurrentState.Gamepad.sThumbRY;
//
//	//determine how far the controller is pushed
//	float magnitudeR = sqrtf(RX * RX + RY * RY);
//
//	////Determine the idrection the controller is pushed
//	//float normalizedLX = RX / magnitudeR;
//	//float normalizedLY = RY / magnitudeR;
//
//	float normalizedMagnitude = 0;
//
//	//check if the controller is outside a circular dead zone
//	if (magnitudeR > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
//	{
//		//clip the magnitude at its expected maximum value
//		if (magnitudeR > 32767) magnitudeR = 32767;
//
//		//adjust magnitude relative to the end of the dead zone
//		magnitudeR -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
//
//		//optionally normalize the magnitude with respect to its expected range
//		//giving a magnitude value of 0.0 to 1.0
//		normalizedMagnitude = magnitudeR / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
//	}
//	else //if the controller is in the deadzone zero out the magnitude
//	{
//		magnitudeR = 0.0;
//		normalizedMagnitude = 0.0;
//	}
//}
//void dae::Controller::DeadzoneRightThumbStick()
//{
//	float RX = m_CurrentState.Gamepad.sThumbRX;
//	float RY = m_CurrentState.Gamepad.sThumbRY;
//
//	//determine how far the controller is pushed
//	float magnitudeR = sqrtf(RX * RX + RY * RY);
//
//	////Determine the idrection the controller is pushed
//	//float normalizedLX = RX / magnitudeR;
//	//float normalizedLY = RY / magnitudeR;
//
//	float normalizedMagnitude = 0;
//
//	//check if the controller is outside a circular dead zone
//	if (magnitudeR > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
//	{
//		//clip the magnitude at its expected maximum value
//		if (magnitudeR > 32767) magnitudeR = 32767;
//
//		//adjust magnitude relative to the end of the dead zone
//		magnitudeR -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
//
//		//optionally normalize the magnitude with respect to its expected range
//		//giving a magnitude value of 0.0 to 1.0
//		normalizedMagnitude = magnitudeR / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
//	}
//	else //if the controller is in the deadzone zero out the magnitude
//	{
//		magnitudeR = 0.0;
//		normalizedMagnitude = 0.0;
//	}
//}


//Implementation
dae::Controller::ControllerImpl::ControllerImpl(unsigned int controllerID, bool keyboard)
	:m_IsKeyboardEnabled{ keyboard }
{
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	m_ControllerIndex = controllerID;
}

void dae::Controller::ControllerImpl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	buttonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	buttonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	if (m_IsKeyboardEnabled)
	{
	
	}

}

bool dae::Controller::ControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return  buttonPressedThisFrame & static_cast<int>(button);
}

bool dae::Controller::ControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return  buttonReleasedThisFrame & static_cast<int>(button);;
}

bool dae::Controller::ControllerImpl::IsPressed(unsigned int button) const
{
	return  ((m_CurrentState.Gamepad.wButtons & static_cast<int>(button)) != 0);
}

bool dae::Controller::ControllerImpl::IsKeyDown(unsigned int key) const
{

	return GetKeyState(key) & 0x8000;;
}

bool dae::Controller::ControllerImpl::IsKeyUp(unsigned int key) const
{
	return 	~GetKeyState(key) & 0x8000;
}

bool dae::Controller::ControllerImpl::isKeyPressed(unsigned int key) const
{
	return GetKeyState(key) & 0x8000;
}
