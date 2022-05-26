#pragma once
#include "Singleton.h"
#include "SDL_mixer.h"
#include "TrackType.h"
namespace dae
{
	using sound_id = unsigned short;
	
	class SoundSystem
	{
	public:
		explicit SoundSystem();
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem & other) = delete;
		SoundSystem(SoundSystem && other) = delete;
		SoundSystem& operator=(const SoundSystem & other) = delete;
		SoundSystem& operator=(SoundSystem && other) noexcept = delete;


		virtual void Cleanup() = 0;
		virtual void PlaySound(const sound_id m_Id, int volume) = 0;
		virtual void PlayMusic(const sound_id m_Id, int volume) = 0;
		virtual void AddAudioClip(std::string path) = 0;
		virtual void AddMusicClip(std::string path, bool loop) = 0;

		virtual void SetVolume(int volume) = 0;

	};
}

