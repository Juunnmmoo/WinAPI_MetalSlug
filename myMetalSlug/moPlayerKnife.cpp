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
#include "moAnimator.h"
#include "moSlave.h"

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
		mCollider->SetSize(Vector2{ 70.0f, 110.0f });

		SetBulletType(eBulletType::knife);

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

	


		if (other->GetOwner()->GetLayerType() == eLayerType::EnemyR || other->GetOwner()->GetLayerType() == eLayerType::EnemyR_F||
			other->GetOwner()->GetLayerType() == eLayerType::Enemy || other->GetOwner()->GetLayerType() == eLayerType::Enemy_F)
		{

			Arabian* arabian = dynamic_cast<Arabian*>(other->GetOwner());
			if (arabian != nullptr)
			{
				isCollide = true;

				if (Input::GetKeyDown(eKeyCode::D) && isUse)
				{

					if (other->GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::Left)

					{
						other->GetOwner()->GetComponent<Animator>()->Play(L"KnifeDeathL", false);
					}
					else
					{
						other->GetOwner()->GetComponent<Animator>()->Play(L"KnifeDeathR", false);
					}
					other->GetOwner()->SetState(eState::Pause);

				}
			}
		}
		
		if (other->GetOwner()->GetLayerType() == eLayerType::Slave)
		{
			Slave* slave = dynamic_cast<Slave*>(other->GetOwner());
			if (slave != nullptr && !slave->GetIsRelease())
			{
				isCollide = true;

				if (Input::GetKeyDown(eKeyCode::D) && isUse)
				{
					
					
						slave->SetIsRelease(true);
						slave->GetAnimator()->Play(L"BeReleasedL", false);
						slave->SetSlaveState(Slave::eSlaveState::BeReleased);
					
				}
			}
		}

	}
	void PlayerKnife::OnCollisionExit(Collider* other)
	{
		isCollide = false;
	}
}