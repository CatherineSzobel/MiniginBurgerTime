#include "MiniginPCH.h"
#include "SceneGraph.h"
void dae::SceneGraph::SetParent(GameObject* parent)
{
    if (m_Parent != nullptr)
    {
        //remove the old parent as a child.
        const auto it = std::find(m_Children.begin(), m_Children.end(), m_Parent);
        m_Children.erase(it);
    }
    //set the given parent on itself and add it as a child.
    m_Parent = parent;
    m_Children.emplace_back(parent);

}

size_t dae::SceneGraph::GetChildCount() const
{
    return m_Children.size();
}


void dae::SceneGraph::RemoveChild(int index)
{

        const auto it = std::find(m_Children.begin(), m_Children.end(), m_Children[index]);
        if (it == m_Children.end())
        {
            return;
        }
        m_Children.erase(it);
}

void dae::SceneGraph::RemoveChild(GameObject* child)
{
        const auto it = std::find(m_Children.begin(), m_Children.end(), child);
        if (it == m_Children.end())
        {
            return;
        }
        m_Children.erase(it);
       
    

}

void dae::SceneGraph::AddChild(GameObject* go)
{
    m_Children.emplace_back(go);
  
}
