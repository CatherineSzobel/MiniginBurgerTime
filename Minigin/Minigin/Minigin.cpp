#pragma once
#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "TextObject.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

#include "Scene.h"

#include "sdl_sound_system.h"
#include "servicelocator.h"

#include "Time.h"
#include <chrono>

using namespace std;
using namespace std::chrono;
void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	InputManager::GetInstance().SetKeyboardEnabled(true);
	InputManager::GetInstance().Initialize();
	servicelocator::register_sound_system(new sdl_sound_system("../Data/"));
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto go = std::make_shared<GameObject>();
	//	auto backgroundComponent = new RenderComponent();


	go->AddComponent<RenderComponent>()->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>()->SetTexture("logo.png");
	go->GetComponent<RenderComponent>()->SetPosition(216.0f, 180.f);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go->AddComponent<TextComponent>()->SetText("Programming 4 Assignment");
	go->GetComponent<TextComponent>()->SetPosition(80.f, 20.f);
	go->GetComponent<TextComponent>()->SetFont(font);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<TextComponent>()->SetText("FPS: ");
	go->GetComponent<TextComponent>()->SetPosition(0.f, 440.f);
	go->GetComponent<TextComponent>()->SetFont(font);
	scene.Add(go);

}

void dae::Minigin::Cleanup()
{
	servicelocator::destroy_sound_system();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();


	{
		auto fps = std::make_shared<FPSComponent>();

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		input.SetKeyboardEnabled(true);

		servicelocator::register_input_manager(&input);
		servicelocator::register_renderer(&renderer);

		servicelocator::get_input_manager().BindControllerCommand(ControllerButton::ButtonA, new JumpCommand());
		servicelocator::get_input_manager().BindKeyboardCommand('Q', new JumpCommand());
		servicelocator::get_input_manager().BindKeyboardCommand('W', new FireCommand());
		servicelocator::get_input_manager().BindControllerCommand(ControllerButton::ButtonB, new FireCommand());


		// todo: this update loop could use some work.
		high_resolution_clock::time_point previousTime = high_resolution_clock::now();
		float lag = 0.0f;
		bool doContinue = true;
		while (doContinue)
		{
			const high_resolution_clock::time_point currentTime = high_resolution_clock::now();

			float elapsed = duration<float>(currentTime - previousTime).count();
			Time::GetInstance().m_DeltaTime = elapsed;
			fps->FixedUpdate(elapsed);


			previousTime = currentTime;
			lag += elapsed;

			doContinue = input.ProcessInput();

			sceneManager.Update();

			while (lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate(elapsed);
				lag -= MsPerFrame;
			}

			renderer.Render();

		}
	}
	Cleanup();
}
//not using it yet

//maybe later when wanting to change the game loop
float dae::Minigin::GetCurrentTimeInFloat()
{
	high_resolution_clock::time_point currentTimePoint = high_resolution_clock::now();
	float currentTime = duration_cast<duration<float>>(currentTimePoint.time_since_epoch()).count();

	return currentTime;
}
