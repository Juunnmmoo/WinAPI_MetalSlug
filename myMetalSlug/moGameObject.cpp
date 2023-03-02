#include "moGameObject.h"

namespace mo {
	GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;
			comp->Update();
		}
	}
	void GameObject::Render(HWND mHwnd)
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;
			comp->Render(mHwnd);
		}
	}
}
