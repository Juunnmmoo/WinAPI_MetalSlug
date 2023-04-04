#include "moGameObject.h"
#include "moTransform.h"
#include "moInput.h"
namespace mo {
	GameObject::GameObject()
		: mState(eState::Active)
		, mLayerType(eLayerType::End)
		, isDeath(false)
		, useColliderBox(false)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent<Transform>();
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
		if (Input::GetKeyDown(eKeyCode::P))
		{
			if (useColliderBox)
				useColliderBox = false;
			else
				useColliderBox = true;
		
		}
		
	}
	void GameObject::Render(HDC mHdc)
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;
			if (!useColliderBox && comp->GetType() == eComponentType::Collider)
				continue;
			comp->Render(mHdc);
		}
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}
