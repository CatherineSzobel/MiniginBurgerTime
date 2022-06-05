#pragma once
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		virtual void Initialize() override;
		virtual void Render() const override;

		virtual void Update() override;
		virtual void FixedUpdate(float dt) override;
	
		void SetPosition(float x, float y);
		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font> font);

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		explicit TextComponent(const std::shared_ptr<Font>& font) : m_Font{ font } {}
		explicit TextComponent() : m_Font{}, m_Transform{}, m_NeedsUpdate{ false }, m_TextTexture{}
		{}
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}

