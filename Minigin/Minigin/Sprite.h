#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"
#include "Time.h"
namespace dae
{
	class Sprite final
	{
	public:
		Sprite(std::string path, std::string name, int amountOfCol, int amountOfRow, float frameTime, float frameSec);
		virtual ~Sprite() = default;
		Sprite(const Sprite& other) = delete;
		Sprite(Sprite&& other) = delete;
		Sprite& operator=(const Sprite& other) = delete;
		Sprite& operator=(Sprite&& other) = delete;

		void Update();
		void FixedUpdate(float deltaTime);
		void Render(const Transform& spriteTransform);
		std::string GetAnimationClipName() { return m_Name; }
		void SetTexture(std::string& path);

	private:
		std::string m_Path;
		std::string m_Name;
		std::shared_ptr<Texture2D> m_Texture{};

		int m_AmountOfColumns{};
		int m_AmountOfRows{};
		float m_CurrentTime{};
		float m_AccuSec{};
		float m_FrameTime{};
		float m_FrameSec{};

		int m_Width{}, m_Height{};
	};
}


