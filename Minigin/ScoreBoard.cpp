#include "MiniginPCH.h"
#include "ScoreBoard.h"

void dae::ScoreBoard::Notify(Event event)
{
	std::string text = "Points: ";
	switch (event)
	{

	case Event::BurgerDrops:
		m_Score += 50;
		break;
	case Event::MrHotDog:
		m_Score += 100;
		break;
	case Event::MrPickle:
		m_Score += 200;
		break;
	case Event::MrEgg:
		m_Score += 300;
		break;
	case Event::DropBurgerWithOneEnemy:
		m_Score += 500;
		break;
	case Event::DropBurgerWithTwoEnemy:
		m_Score += 1000;
		break;
	case Event::DropBurgerWithThreeEnemy:
		m_Score += 2000;
		break;
	case Event::DropBurgerWithFourEnemy:
		m_Score += 4000;
		break;
	case Event::DropBurgerWithFiveEnemy:
		m_Score += 8000;
		break;
	case Event::DropBurgerWithSixEnemy:
		m_Score += 16000;
		break;

	}
	text.append(std::to_string(m_Score));
	m_pTextScoreComponent->SetText(text);
	
}
