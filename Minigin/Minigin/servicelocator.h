#pragma once
#include "SoundSystem.h"
#include "InputManager.h"
#include "sdl_sound_system.h"
#include "Renderer.h"
namespace dae
{
	class servicelocator final
	{
		static SoundSystem* m_pSoundSystem;
		static null_sound_system m_pDefaultSystem;

		static InputManager* m_pInputManager;

		static Renderer* m_pRenderer;
	public:
		static SoundSystem& get_sound_system() { return *m_pSoundSystem; }
		static void register_sound_system(SoundSystem* ss) { m_pSoundSystem = ss == nullptr ? &m_pDefaultSystem : ss; }
		static void destroy_sound_system() { delete m_pSoundSystem; m_pSoundSystem = nullptr; }
		static InputManager& get_input_manager() { return *m_pInputManager; }
		static void register_input_manager(InputManager* im) { m_pInputManager = im; }

		static Renderer& get_renderer() { return *m_pRenderer; }
		static void register_renderer(Renderer* r) { m_pRenderer = r; }
	};

}