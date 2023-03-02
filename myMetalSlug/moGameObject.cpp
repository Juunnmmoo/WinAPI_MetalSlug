#include "moGameObject.h"

namespace mo {
	GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
		for (Component* comp : mComponents) {
			delete comp;
			comp = nullptr;
		}
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
	void GameObject::Render(HDC mHdc)
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;
			comp->Render(mHdc);
		}
	}
}
