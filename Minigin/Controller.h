#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include <memory>
#include "Command.h"
#include "GamepadButton.h"
namespace dae
{
	class Controller final
	{
		class ControllerImpl final
		{
		public:
			ControllerImpl(unsigned int controllerID, bool keyboard = false);
			void Update();

			bool IsDownThisFrame(unsigned int button) const;
			bool IsUpThisFrame(unsigned int button) const;
			bool IsPressed(unsigned int button) const;


		private:

			XINPUT_STATE m_CurrentState{};
			XINPUT_STATE m_PreviousState{};

			bool m_IsKeyboardEnabled{ false };

			XINPUT_KEYSTROKE m_CurrentKeyStroke{};

			int m_ControllerIndex{ 0 };
			WORD buttonPressedThisFrame{ 0 };
			WORD buttonReleasedThisFrame{ 0 };

			SHORT keyPressedThisFrame{ 0 };
			SHORT keyReleasedThisFrame{ 0 };
		};

	public:

		Controller(int controllerID, bool keyboard = false);
		virtual ~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();


		bool IsDown(GamepadButton button) const;
		bool IsUp(GamepadButton button) const;
		bool IsPressed(GamepadButton button) const;

	private:
		//void DeadzoneLeftThumbstick();
		//void DeadzoneRightThumbStick();

		class ControllerImpl;
		ControllerImpl* pImpl;
	};
}
