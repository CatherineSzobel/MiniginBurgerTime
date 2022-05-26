#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <chrono>
namespace dae
{
	class Font;
	class Texture2D;
	class FPSComponent final : public BaseComponent
	{
	public:
		virtual void Initialize() override;
		virtual void Render() const override;

		virtual void Update() override;
		virtual void FixedUpdate(float) override;


		void SetPosition(float x, float y);

		void SetTextComp(TextComponent* textcomp);

		explicit FPSComponent() = default;
		virtual ~FPSComponent();
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		TextComponent* m_TextComponent;


		int m_FpsCount = 0;
		int m_CurrentFps = 0;
		float m_FPSTimer;

	};
}

