#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::~GameObject()
{
	m_Parent = nullptr;
	delete m_Parent;
	for (auto& child : m_Children)
	{
		delete child;
	}
	for (auto& component : m_pComponents)
	{
		delete component;
	}

}

void dae::GameObject::Update()
{
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{

	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::Initialize()
{
	for (const auto& component : m_pComponents)
	{
		component->Initialize();
	}
}

void dae::GameObject::RemoveChild(int index)
{
	const auto it = std::find(m_Children.begin(), m_Children.end(), m_Children[index]);
	m_Children[index]->m_Parent = nullptr;
	m_Children.erase(it);

}

void dae::GameObject::RemoveChild(GameObject* child)
{
	const auto it = std::find(m_Children.begin(), m_Children.end(), child);
	m_Children.erase(it);
	child->m_Parent = nullptr;
}

void dae::GameObject::AddChild(GameObject* go)
{
	if (go->m_Children.empty())
	{
		m_Children.emplace_back(go);
		go->m_Parent = this;
	}
}


