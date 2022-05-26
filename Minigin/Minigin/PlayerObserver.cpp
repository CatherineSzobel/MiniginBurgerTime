#include "MiniginPCH.h"
#include "PlayerObserver.h"

dae::PlayerObserver::PlayerObserver()
	:m_RemainingLives{ 3 }, m_pTextLifeComponent{ nullptr }
{
}

void dae::PlayerObserver::Notify(Event event)
{
	std::string text = "Remaining lives: ";
	switch (event)
	{
	case Event::ActorDied:
		m_RemainingLives -= 1;
		break;
	}
	text.append(std::to_string(m_RemainingLives));
	m_pTextLifeComponent->SetText(text);
}
