#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <chrono>
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Time.h"
using namespace std::chrono;
void dae::FPSComponent::Update()
{
	m_TextComponent->SetText(std::to_string(int(1 / Time::GetInstance().GetElapsedTime())));
}

void dae::FPSComponent::FixedUpdate(float/*deltaTime*/ )
{
		//m_TextComponent->SetText(std::to_string(int(1/deltaTime)));
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::FPSComponent::Initialize()
{
	m_Font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_TextComponent = new TextComponent(m_Font);
	m_TextComponent->SetPosition(30, 440);
}

void dae::FPSComponent::SetTextComp(TextComponent* textcomp)
{
	m_TextComponent = textcomp;
}

dae::FPSComponent::~FPSComponent()
{
	delete m_TextComponent;
	m_TextComponent = nullptr;
}
