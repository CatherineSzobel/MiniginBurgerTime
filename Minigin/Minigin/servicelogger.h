#pragma once
#include "SoundSystem.h"
namespace dae
{
	class servicelogger final : public SoundSystem
	{
		using sound_id = unsigned short;
	public:
		explicit servicelogger() = default;
		virtual ~servicelogger() = default;
		servicelogger(const servicelogger& other) = delete;
		servicelogger(servicelogger&& other) = delete;
		servicelogger& operator=(const servicelogger& other) = delete;
		servicelogger& operator=(servicelogger&& other) noexcept = delete;

		virtual void Cleanup() override;
		virtual void PlaySound(const sound_id m_Id, int volume) override;
		virtual void AddAudioClip(std::string path) override;
		virtual void AddMusicClip(std::string path, bool loop) override;

		virtual void SetVolume(int volume) override;

	private:

		// Inherited via SoundSystem
		virtual void PlayMusic(const sound_id m_Id, int volume) override;
	};
}