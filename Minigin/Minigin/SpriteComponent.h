#pragma once
#include "BaseComponent.h"
#include "Sprite.h"
#include <map>
namespace dae
{
	class Texture2D;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(std::string path, bool animated = false);
		SpriteComponent() = default;
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		virtual void Initialize() override;

		virtual void Update() override;
		virtual void FixedUpdate(float deltaTime) override;

		virtual void Render() const override;
		void AddAnimationClip(std::string path, std::string name, int amountOfCol, int amountOfRow, float frameTime, float frameSec);
		void SetCurrentAnimation(std::string name);

		void SetTexture(std::string path);
		void SetPosition(float x, float y);
	private:

		std::shared_ptr<Texture2D> m_Texture{};

		bool m_IsAnimated{};
		Sprite* m_CurrentAnimation;
		std::vector<Sprite*> m_AnimationClips;

		dae::Transform m_Transform;
	};

}