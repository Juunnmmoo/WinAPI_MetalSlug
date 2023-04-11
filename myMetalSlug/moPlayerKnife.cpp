#include "moPlayerKnife.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"
#include "moObject.h"
#include "moInput.h"
#include "moCamera.h"
#include "moMarco.h"
#include "moObject.h"
#include "moArabian.h"
#include "moSceneManager.h"
#include "moObject.h"

namespace mo {
	PlayerKnife::PlayerKnife()
	{
	}
	PlayerKnife::~PlayerKnife()
	{
	}
	void PlayerKnife::Initialize()
	{
		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 50.0f, 110.0f });

		GameObject::Initialize();
	}
	void PlayerKnife::Update()
	{
		GameObject::Update();

	}
	void PlayerKnife::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void PlayerKnife::SetPos(Vector2 pos)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(pos);
	}
	void PlayerKnife::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerKnife::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Enemy)
		{
			isCollide = true;
			if (Input::GetKeyDown(eKeyCode::D) && isUse)
				other->GetOwner()->SetState(eState::Pause);
		}
	}
	void PlayerKnife::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Enemy)
		{
			isCollide = false;
		}
	}
}