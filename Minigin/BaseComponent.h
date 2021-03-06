#pragma once
#include "SceneObject.h"
#include "Transform.h"
namespace dae
{
	class Texture2D;
	class Font;
	class GameObject;
	class BaseComponent
	{
	public:

		virtual void Initialize() = 0;

		virtual void Update() = 0;
		virtual void FixedUpdate(float deltaTime) = 0;

		virtual void Render() const = 0;

		explicit BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		void SetCurrentGameObject(GameObject* gameobject) { m_pOwner = gameobject; }
		GameObject* GetOwner() const { return m_pOwner; }
		GameObject* m_pOwner;
	protected:
		explicit BaseComponent(GameObject* pOwner) : m_pOwner(pOwner) {}

	};
}

