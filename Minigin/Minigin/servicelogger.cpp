#include "MiniginPCH.h"
#include "servicelogger.h"


void dae::servicelogger::Cleanup()
{

}

void dae::servicelogger::PlaySound(const sound_id m_Id, int volume)
{

	std::cout << "playing sound id " << m_Id << " at volume" << volume << " \n";
}

void dae::servicelogger::AddAudioClip(std::string path)
{
	std::string::size_type format = path.find('.');
	std::cout << "Audio name: " << path.substr(0, format) << " added.\n";
}

void dae::servicelogger::AddMusicClip(std::string path, bool /*loop*/)
{
	std::string::size_type format = path.find('.');
	std::cout << "Music name: " << path.substr(0, format) << " added.\n";
}

void dae::servicelogger::SetVolume(int volume)
{
	std::cout << "Set volume to " << volume << " \n";
}

void dae::servicelogger::PlayMusic(const sound_id m_Id, int volume)
{

	std::cout << "playing song id " << m_Id << " at volume" << volume << " \n";
}
