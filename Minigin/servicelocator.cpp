#include "MiniginPCH.h"
#include "servicelocator.h"

dae::null_sound_system dae::servicelocator::m_pDefaultSystem{};
dae::SoundSystem* dae::servicelocator::m_pSoundSystem = &m_pDefaultSystem;
dae::InputManager* dae::servicelocator::m_pInputManager{};
dae::Renderer* dae::servicelocator::m_pRenderer{};