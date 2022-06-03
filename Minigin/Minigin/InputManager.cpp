#include "MiniginPCH.h"
#include "InputManager.h"
#include "backends/imgui_impl_sdl.h"

void dae::InputManager::Initialize()
{
	//keyboard
	if (m_EnableKeyboard)
	{
		m_pControllers.emplace_back(new Controller(0, true));
	}
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (m_pControllers[i] != nullptr)
		{
			ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));

			auto dwResult = XInputGetState(i, &m_CurrentState[i]);

			//determine if the controller is connected
			if (dwResult == ERROR_SUCCESS)
			{
				//Controller is connected
				m_pControllers.emplace_back(new Controller(i));
				++m_CurrentAmountOfPlayers;
			}
			else
			{
				ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
				break;
				//Controller is not connected
			}
		}

	}

}

bool dae::InputManager::ProcessInput()
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{

		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_CurrentState[i]);
		ProcessControllerInput();

	}
	ProcessKeyboardInput();
	return true;
}

void dae::InputManager::ProcessControllerInput()
{
	for (auto& controller : m_pControllers)
	{
		controller->Update();
		for (auto& command : m_ConsoleButtons)
		{
			if (controller->IsDown(command.first))
			{
				command.second.get()->Execute();
				break;
			}
		}
	}
}

void dae::InputManager::ProcessKeyboardInput()
{
	for (auto& controller : m_pControllers)
	{
		controller->Update();
		for (auto& command : m_KeyButtons)
		{
			if (controller->IsKeyDown(command.first))
			{
				command.second.get()->Execute();
				break;
			}
		}
	}
}

void dae::InputManager::BindControllerCommand(ControllerButton button, Command* command)
{
	m_ConsoleButtons.emplace(button, std::unique_ptr<Command>(command));
}

void dae::InputManager::BindKeyboardCommand(int keyboard, Command* command)
{
	m_KeyButtons.emplace(keyboard, std::unique_ptr<Command>(command));
}


