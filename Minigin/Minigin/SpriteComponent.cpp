#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
dae::SpriteComponent::SpriteComponent(std::string path, bool animated)
	:m_IsAnimated{ animated }
{
	SetTexture(path);
}

void dae::SpriteComponent::Initialize()
{
}

void dae::SpriteComponent::Update()
{
	if (m_IsAnimated)
	{
		if (m_CurrentAnimation == nullptr && !m_AnimationClips.empty())
		{
			//default will be the first animation of the vector.
			m_CurrentAnimation = m_AnimationClips[0];
		}
		m_CurrentAnimation->Update();
	}
}

void dae::SpriteComponent::FixedUpdate(float deltaTime)
{
	if (m_IsAnimated)
	{
		if (m_CurrentAnimation == nullptr && !m_AnimationClips.empty())
		{
			//default will be the first animation of the vector.
			m_CurrentAnimation = m_AnimationClips[0];
		}
		m_CurrentAnimation->FixedUpdate(deltaTime);
	}
}

void dae::SpriteComponent::Render() const
{
	if (m_IsAnimated)
	{
		m_CurrentAnimation->Render(m_Transform);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
	}
}

void dae::SpriteComponent::AddAnimationClip(std::string path, std::string name, int amountOfCol, int amountOfRow, float frameTime, float frameSec)
{
	m_AnimationClips.emplace_back(new Sprite(path, name, amountOfCol, amountOfRow, frameTime, frameSec));
}

void dae::SpriteComponent::SetCurrentAnimation(std::string name)
{

	for (auto& clip : m_AnimationClips)
	{

		if (clip->GetAnimationClipName() == name)
		{
			m_CurrentAnimation = clip;
			break;
		}
	}
	std::cout << "No animation clip found with name" << name << ". \n";
}

void dae::SpriteComponent::SetTexture(std::string path)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}

void dae::SpriteComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 1);
}
