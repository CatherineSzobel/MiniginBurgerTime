#include "MiniginPCH.h"
#include "SoundSystem.h"
#include "SDL_mixer.h"
using std::cout, std::endl;

dae::SoundSystem::SoundSystem()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}
