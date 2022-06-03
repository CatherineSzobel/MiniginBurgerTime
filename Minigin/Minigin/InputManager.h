#pragma once
#define WIN32_LEAN_AND_MEAN
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <vector>
#include <memory>
#include <map>
#include "Controller.h"
#include "ControllerButton.h"
namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		virtual ~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		void Initialize();
		bool ProcessInput();
		void ProcessControllerInput();
		void ProcessKeyboardInput();
		void BindControllerCommand(ControllerButton button, Command* command);
		void BindKeyboardCommand(int keyboard, Command* command);
		void SetKeyboardEnabled(bool enable) { m_EnableKeyboard = enable; }
	private:

		XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT];
		//XINPUT_STATE m_PreviousState{};

		//XINPUT_KEYSTROKE m_CurrentKeyStroke[XUSER_MAX_COUNT];

		using ControllerCommandsMap = std::map<ControllerButton, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ConsoleButtons{};

		using KeyboardCommandsMap = std::map<int, std::unique_ptr<Command>>;
		KeyboardCommandsMap m_KeyButtons{};

		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		bool m_EnableKeyboard{ false };
		int	m_CurrentAmountOfPlayers{ 0 };
	};

}
