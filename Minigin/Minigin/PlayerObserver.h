#pragma once
#include "MiniginPCH.h"
#include "Observer.h"
#include "TextComponent.h"
#include <iostream>
namespace dae
{
	class PlayerObserver : public Observer
	{
		// Inherited via Observer
		PlayerObserver();
		virtual ~PlayerObserver() = default;
		PlayerObserver(const PlayerObserver& other) = delete;
		PlayerObserver(PlayerObserver&& other) = delete;
		PlayerObserver& operator=(const PlayerObserver& other) = delete;
		PlayerObserver& operator=(PlayerObserver&& other) = delete;

		virtual void Notify(Event event) override;
	private:
		int m_RemainingLives;
		TextComponent* m_pTextLifeComponent;
		
	};

}

