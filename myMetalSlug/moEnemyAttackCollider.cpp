#include "moEnemyAttackCollider.h"
#include "Collider.h"
#include "moTransform.h"
#include "moObject.h"
#include "moTime.h"

namespace mo {
	EnemyAttackCollider::EnemyAttackCollider(Vector2 pos, Vector2 leftTop, Vector2 size)
		: mPos(pos)
		, mLeftTop(leftTop)
		, mSize(size)
		, mTime(0.0f)
	{
	}
	EnemyAttackCollider::~EnemyAttackCollider()
	{
	}
	void EnemyAttackCollider::Initialize()
	{

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(mPos);

		Collider* collider = AddComponent<Collider>();
		collider->SetLeftTop(mLeftTop);
		collider->SetSize(mSize);

		SetBulletType(eBulletType::knife);

		GameObject::Initialize();
	}
	void EnemyAttackCollider::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 0.5f)
		{
			object::Destory(this);
		}

		GameObject::Update();
	}
	void EnemyAttackCollider::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void EnemyAttackCollider::OnCollisionEnter(Collider* other)
	{
	}
	void EnemyAttackCollider::OnCollisionStay(Collider* other)
	{
	}
	void EnemyAttackCollider::OnCollisionExit(Collider* other)
	{
	}
}