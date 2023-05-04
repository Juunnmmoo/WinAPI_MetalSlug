#include "moShotgunBox.h"
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
#include "moResources.h"
#include "moSound.h"
namespace mo {
	ShotgunBox::ShotgunBox()
	{
	}
	ShotgunBox::~ShotgunBox()
	{
	}
	void ShotgunBox::Initialize()
	{
		machinegunSound = Resources::Load<Sound>(L"machinegunSound", L"..\\Resources\\Sound\\machinegunSound.wav");


		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(650.0f, 600.0f));

		mImage = Resources::Load<Image>(L"M_Box", L"..\\Resources\\Weapon\\Icon\\MachinegunIcon.bmp");

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 55.0f, 50.0f });
		mCollider->SetLeftTop(Vector2{ -25.0f, -50.0f });


		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));

		GameObject::Initialize();
	}
	void ShotgunBox::Update()
	{
		mTime += Time::DeltaTime();


		GameObject::Update();
	}
	void ShotgunBox::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(tr->GetPos());

		TransparentBlt(mHdc, pos.x - 25.0f, pos.y - 50.0f, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));

		GameObject::Render(mHdc);
	}
	void ShotgunBox::OnCollisionEnter(Collider* other)
	{
	}
	void ShotgunBox::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player && mTime >= 0.3f) {
			Marco* marco = dynamic_cast<Marco*>(other->GetOwner());
			if (marco == nullptr)
				return;
			machinegunSound->Play(false);
			marco->ChangeWeapon(eMarcoWeapon::Shotgun);
			marco->AddBulletNum(20);
			object::Destory(this);
		}
	}
	void ShotgunBox::OnCollisionExit(Collider* other)
	{
	}
}