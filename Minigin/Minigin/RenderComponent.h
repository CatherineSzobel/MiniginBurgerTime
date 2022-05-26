#pragma once
#include "BaseComponent.h"
#include "Transform.h"
namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		void Update() override;
		virtual void FixedUpdate(float deltaTime) override;
		void Render() const override;
		virtual void Initialize() override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		RenderComponent() = default;
		RenderComponent(const std::string& filename);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_Texture{};
		dae::Transform m_Transform;

	};
}

