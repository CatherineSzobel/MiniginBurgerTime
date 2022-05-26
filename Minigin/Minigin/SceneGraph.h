#pragma once
#include "GameObject.h"
namespace dae {
	class SceneGraph final
	{
	public:


		void SetParent(GameObject* parent);
		GameObject* GetParent() const { return m_Parent; }

		size_t GetChildCount() const; 
		GameObject* GetChildAt(int index) const { return m_Children[index]; };
		void RemoveChild(int index);
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* go);

		SceneGraph() = default;
		~SceneGraph() = default;
		SceneGraph(const SceneGraph& other) = delete;
		SceneGraph(SceneGraph&& other) = delete;
		SceneGraph& operator=(const SceneGraph& other) = delete;
		SceneGraph& operator=(SceneGraph&& other) = delete;

	private:
		GameObject* m_Parent{ };
		std::vector<GameObject*> m_Children{};
	};
}


