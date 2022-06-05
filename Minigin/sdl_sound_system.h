#pragma once
#include "TrackType.h"
#include "SoundSystem.h"
#include <thread>
#include <mutex>
#include <queue>
namespace dae
{
	class sdl_sound_system final : public SoundSystem
	{
	public:

		sdl_sound_system(const std::string& path);

		explicit sdl_sound_system() = default;
		virtual ~sdl_sound_system() = default;
		sdl_sound_system(const sdl_sound_system& other) = delete;
		sdl_sound_system(sdl_sound_system&& other) = delete;
		sdl_sound_system& operator=(const sdl_sound_system& other) = delete;
		sdl_sound_system& operator=(sdl_sound_system&& other) noexcept = delete;

		virtual void Cleanup() override;
		virtual void PlaySound(const sound_id m_Id, int volume) override;
		virtual void PlayMusic(const sound_id m_Id, int volume) override;
		virtual void AddAudioClip(std::string path) override;
		virtual void AddMusicClip(std::string path, bool loop) override;

		void Update();

		virtual void SetVolume(int volume) override;
		int GetVolume();

	private:
		std::string m_path;
		int m_Volume;
		bool m_IsStopping;

		std::vector<Sound_Nr> m_pSoundList;
		std::vector<Song_Nr> m_pSongList;

		std::deque<Sound_Nr> m_SoundQueue;
		std::deque<Song_Nr> m_MusicQueue;

		//std::mutex m_SoundMutex;
		//std::mutex m_SongMutex;

		//std::condition_variable m_SoundConditionalVariable;
		//std::condition_variable m_SongConditionalVariable;
		//std::thread m_Thread;

	};

	class null_sound_system final : public SoundSystem
	{
	public:
		explicit null_sound_system() = default;
		virtual ~null_sound_system() = default;
		null_sound_system(const null_sound_system& other) = delete;
		null_sound_system(null_sound_system&& other) = delete;
		null_sound_system& operator=(const null_sound_system& other) = delete;
		null_sound_system& operator=(null_sound_system&& other) noexcept = delete;

		// Inherited via SoundSystem
		virtual void Cleanup() override {};
		virtual void PlaySound(const sound_id, int) override {};
		virtual void PlayMusic(const sound_id, int) override {};
		virtual void AddAudioClip(std::string) override {};
		virtual void AddMusicClip(std::string, bool) override {};
		virtual void SetVolume(int) override {};
	};
}
