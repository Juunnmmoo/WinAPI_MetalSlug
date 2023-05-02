#include "moBoss2LaserCollider.h"
#include "moTransform.h"
#include "Collider.h"

namespace mo {
	Boss2LaserCollider::Boss2LaserCollider(eDirection dir)
		: mDirection(dir)
	{
	}
	Boss2LaserCollider::~Boss2LaserCollider()
	{
	}
	void Boss2LaserCollider::Initialize()
	{

		if (mDirection == eDirection::Left)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPos(Vector2(12512.0f - 280.0f, 300.0f));
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPos(Vector2(12512.0f + 280.0f, 300.0f));
		}

		Collider* collider = AddComponent<Collider>();
		collider->SetLeftTop(Vector2(0.0f, 0.0f));
		collider->SetSize(Vector2(80.0f, 450.0f));

		SetState(eState::Pause);
		SetBulletType(eBulletType::Laser);
		GameObject::Initialize();
	}
	void Boss2LaserCollider::Update()
	{
		GameObject::Update();

	}
	void Boss2LaserCollider::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss2LaserCollider::OnCollisionEnter(Collider* other)
	{
	}
	void Boss2LaserCollider::OnCollisionStay(Collider* other)
	{
	}
	void Boss2LaserCollider::OnCollisionExit(Collider* other)
	{
	}
}