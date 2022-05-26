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
		void BindCommand(ControllerButton button, Command* command);
	private:

		XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT];
		//XINPUT_STATE m_PreviousState{};

		//XINPUT_KEYSTROKE m_CurrentKeyStroke[XUSER_MAX_COUNT];

		using ControllerCommandsMap = std::map<ControllerButton, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ConsoleButtons{};

		std::vector<std::unique_ptr<Controller>> m_pControllers{};
	};

}
