#include "moBombBox.h"
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
#include "moRigidBody.h"

namespace mo {
	BombBox::BombBox()
	{
	}
	BombBox::~BombBox()
	{
	}
	void BombBox::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(650.0f, 600.0f));

		mImage = Resources::Load<Image>(L"Bomb_Box", L"..\\Resources\\Weapon\\Icon\\BombBox.bmp");

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetLeftTop(Vector2{ -40.0f, -70.0f });
		mCollider->SetSize(Vector2{ 80.0f, 70.0f });


		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));

		GameObject::Initialize();
	}
	void BombBox::Update()
	{
		mTime += Time::DeltaTime();


		GameObject::Update();
	}
	void BombBox::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(tr->GetPos());

		TransparentBlt(mHdc, pos.x - 40.0f, pos.y - 70.0f, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));

		GameObject::Render(mHdc);
	}
	void BombBox::OnCollisionEnter(Collider* other)
	{
	}
	void BombBox::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player && mTime >= 0.3f) {
			Marco* marco = dynamic_cast<Marco*>(other->GetOwner());
			if (marco == nullptr)
				return;
			marco->AddBombNum(10);
			object::Destory(this);
		}
	}
	void BombBox::OnCollisionExit(Collider* other)
	{
	}
}