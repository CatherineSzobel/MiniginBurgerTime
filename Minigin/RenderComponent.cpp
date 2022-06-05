#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(const std::string& filename)
	:BaseComponent(), m_Texture{}, m_Transform{}
{
	SetTexture(filename);
}
void dae::RenderComponent::Update(){}
void dae::RenderComponent::FixedUpdate(float /*DeltaTime*/) {}

void dae::RenderComponent::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

}

void dae::RenderComponent::Initialize()
{
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}




