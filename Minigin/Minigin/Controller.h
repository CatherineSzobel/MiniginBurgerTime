#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include <memory>
#include "Command.h"
#include "ControllerButton.h"
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

			bool IsKeyDown(unsigned int key) const;
			bool IsKeyUp(unsigned int key) const;
			bool isKeyPressed(unsigned int key) const;

		private:

			XINPUT_STATE m_CurrentState{};
			XINPUT_STATE m_PreviousState{};

			bool m_IsKeyboardEnabled{ false };
			BYTE m_CurrentStateKey[256]{};
			BYTE m_PreviousStateKey[256]{};

			XINPUT_KEYSTROKE m_CurrentKeyStroke{};
			XINPUT_KEYSTROKE m_PrevKeyStroke{};

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


		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		bool IsKeyDown(SDL_Keycode key) const;
		bool IsKeyUp(SDL_Keycode key) const;
		bool isKeyPressed(SDL_Keycode key) const;

	private:
		//void DeadzoneLeftThumbstick();
		//void DeadzoneRightThumbStick();

		class ControllerImpl;
		ControllerImpl* pImpl;
	};
}
