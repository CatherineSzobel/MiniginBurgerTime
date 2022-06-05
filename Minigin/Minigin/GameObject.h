#pragma once

#include "SceneObject.h"
#include "BaseComponent.h"
namespace dae
{
	class Texture2D;

	class GameObject final : public SceneObject
	{
	public:

		void Update() override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override;
		void Initialize();
		void SetParent(GameObject* parent) { m_Parent = parent; }
		GameObject* GetParent() const { return m_Parent; }
		Transform GetTransform() const { return m_Transform;}

		size_t GetChildCount() const { return m_Children.size(); };
		GameObject* GetChildAt(int index) const { return m_Children[index]; };
		void RemoveChild(int index);
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* go);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<class Type>
		Type* AddComponent();

		template<class Type>
		Type* GetComponent() const;

		template<class Type>
		void  RemoveComponent();
	protected:

		GameObject* m_Parent{ };
		std::vector<GameObject*> m_Children{};

	private:
		Transform m_Transform;
		std::vector<BaseComponent*> m_pComponents{};

	};


	template<class Type>
	inline Type* GameObject::AddComponent()
	{
		auto result = new Type();
		m_pComponents.push_back(result);
		return result;
	}
	template<class Type>
	inline Type* GameObject::GetComponent() const
	{
		for (auto& component : m_pComponents)
		{
			if (auto cast = dynamic_cast<Type*>(component))
			{
				return cast;
			}
		}
		return nullptr;
	}
	template<class Type>
	inline void GameObject::RemoveComponent()
	{

		auto result = new Type();
		const auto it = std::find(m_pComponents.begin(), m_pComponents.end(), result);
		m_pComponents.erase(it);
	}

}
