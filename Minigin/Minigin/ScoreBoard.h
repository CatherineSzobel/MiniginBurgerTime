#pragma once
#include "Observer.h"
#include "TextComponent.h"
#include <iostream>
namespace dae
{
	class ScoreBoard final : public Observer
	{
		// Inherited via Observer
		virtual void Notify(Event event) override;
		int GetScore() { return m_Score; };
	private:
		TextComponent* m_pTextScoreComponent;
		int m_Score;
	};
}

