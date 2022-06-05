#pragma once
#include "Singleton.h"
namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:

		explicit Time() = default;
		virtual ~Time() = default;
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

		float GetElapsedTime() const { return m_DeltaTime; }
		float m_DeltaTime;
	private:
		static Time* m_Instance;
	};
}

