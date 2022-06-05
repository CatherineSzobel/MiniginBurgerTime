#pragma once
#include "Observer.h"
#include "Events.h"

namespace dae
{
	class Subject
	{
		Subject();
		virtual ~Subject() = default;
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(Event event);

	private:
		std::vector<Observer*> m_Observers;
	};
}