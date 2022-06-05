#include "MiniginPCH.h"
#include "InputManager.h"
#include "backends/imgui_impl_sdl.h"

void dae::InputManager::Initialize()
{
	//keyboard

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (m_EnableKeyboard)
		{
			m_pControllers.emplace_back(new Controller(0, true));
			++i;
		}
		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));

		auto dwResult = XInputGetState(i, &m_CurrentState[i]);

		//determine if the controller is connected
		if (dwResult == ERROR_SUCCESS)
		{
			//Controller is connected
			m_pControllers.emplace_back(new Controller(i));
		}
		else
		{
			ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
			break;
			//Controller is not connected
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

		if (m_EnableKeyboard)
		{
			ProcessKeyboardInput(e);
		}

	}


	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{

		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_CurrentState[i]);
		ProcessGamepadInput();

	}

	return true;
}

void dae::InputManager::ProcessGamepadInput()
{
	for (auto& controller : m_pControllers)
	{
		controller->Update();
		for (auto& command : m_GamepadButtons)
		{
			if (command.second == InputState::down)
			{
				if (controller->IsDown(command.first.first))
				{
					command.first.second.get()->Execute();
					break;
				}
			}
			if (command.second == InputState::pressed)
			{
				if (controller->IsPressed(command.first.first))
				{
					command.first.second.get()->Execute();
					break;
				}
			}
			if (command.second == InputState::released)
			{
				if (controller->IsUp(command.first.first))
				{
					command.first.second.get()->Execute();
					break;
				}
			}
		}
	}
}

void dae::InputManager::ProcessKeyboardInput(SDL_Event& e)
{
	switch (e.type)
	{

	case SDL_KEYDOWN:
		for (auto& command : m_KeyButtons)
		{
			if (command.second == InputState::down)
			{
				if (e.key.keysym.sym == command.first.first)
				{
					command.first.second.get()->Execute();
					break;
				}
			}
		}
		break;

	case SDL_KEYUP:
		m_PreviousKey = false;
		for (auto& command : m_KeyButtons)
		{
			if (command.second == InputState::released)
			{
				if (e.key.keysym.sym == command.first.first)
				{
					command.first.second.get()->Execute();
					break;
				}
			}
		}

	default:
		for (auto& command : m_KeyButtons)
		{
			if (command.second == InputState::pressed)
			{
				if (e.key.keysym.sym == command.first.first && !m_PreviousKey)
				{
					m_PreviousKey = true;
					command.first.second.get()->Execute();
					break;
				}
			}
		}
		break;
	}
}

void dae::InputManager::BindGamepadCommand(GamepadButton button, InputState state, Command* command)
{
	m_GamepadButtons[std::make_pair(button, std::unique_ptr<Command>(command))] = state;
	//m_GamepadButtons.emplace(button, std::unique_ptr<Command>(command));
}

void dae::InputManager::BindKeyboardCommand(SDL_Keycode keyboard, InputState state, Command* command)
{
	m_KeyButtons[std::make_pair(keyboard, std::unique_ptr<Command>(command))] = state;
	//m_KeyButtons.emplace(keyboard, std::unique_ptr<Command>(command));
}


