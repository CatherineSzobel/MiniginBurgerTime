#include "MiniginPCH.h"
#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);

}

void dae::Subject::RemoveObserver(Observer* observer)
{
	const auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	m_Observers.erase(it);
}

void dae::Subject::Notify(Event event)
{
	for (const auto& singleEvent : m_Observers)
	{
		singleEvent->Notify(event);
	}
}
