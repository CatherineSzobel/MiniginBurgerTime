#include "MiniginPCH.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Renderer.h"
dae::Sprite::Sprite(std::string path, std::string name, int amountOfCol, int amountOfRow, float frameTime, float frameSec)
	:m_AmountOfColumns{ amountOfCol }, m_Name{ name }, m_AmountOfRows{ amountOfRow }, m_FrameTime{ frameTime }, m_FrameSec{ frameSec }
{
	SetTexture(path);
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
}

void dae::Sprite::Update()
{
	m_AccuSec += Time::GetInstance().GetElapsedTime();
	if (m_AccuSec > m_FrameTime)
	{
		++m_CurrentTime;
		if (m_CurrentTime == m_FrameSec)
		{
			m_CurrentTime = 0;
		}
		m_CurrentTime -= m_FrameTime;
	}
}

void dae::Sprite::FixedUpdate(float deltaTime)
{
	m_AccuSec += deltaTime;
	if (m_AccuSec > m_FrameTime)
	{
		++m_CurrentTime;
		if (m_CurrentTime == m_FrameSec)
		{
			m_CurrentTime = 0;
		}
		m_CurrentTime -= m_FrameTime;
	}
}

void dae::Sprite::Render(const Transform& spriteTransform)
{
	SDL_Rect dstRect{};

	dstRect.w = m_Width / m_AmountOfColumns;
	dstRect.h = m_Height / m_AmountOfRows;
	dstRect.x = (static_cast<int>(m_CurrentTime) % m_AmountOfColumns) * dstRect.w;
	dstRect.y = (static_cast<int>(m_CurrentTime) % m_AmountOfColumns + 1) * dstRect.h;

	SDL_Rect srcRect{};
	srcRect.w = dstRect.w;
	srcRect.h = dstRect.h;
	srcRect.x = static_cast<int>(spriteTransform.GetPosition().x);
	srcRect.y = static_cast<int>(spriteTransform.GetPosition().y);

	Renderer::GetInstance().RenderTexture(*m_Texture, dstRect, srcRect);
}

void dae::Sprite::SetTexture(std::string& path)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}
