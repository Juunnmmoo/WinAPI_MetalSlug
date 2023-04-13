#include "moMachinegunBox.h"
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
	MachinegunBox::MachinegunBox()
	{
	}
	MachinegunBox::~MachinegunBox()
	{
	}
	void MachinegunBox::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(650.0f, 600.0f));

		mImage = Resources::Load<Image>(L"M_Box", L"..\\Resources\\Weapon\\Icon\\MachinegunIcon.bmp");
		
		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 55.0f, 50.0f });

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));
		
		GameObject::Initialize();

	}
	void MachinegunBox::Update()
	{
		GameObject::Update();

	}
	void MachinegunBox::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(tr->GetPos());
		
		TransparentBlt(mHdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));

		GameObject::Render(mHdc);

	}
	void MachinegunBox::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player) {
			Marco* marco = dynamic_cast<Marco*>(other->GetOwner());
			marco->ChangeWeapon(eMarcoWeapon::Machinegun);
			marco->SetBulletNum(1000);
			object::Destory(this);
		}
	}
	void MachinegunBox::OnCollisionStay(Collider* other)
	{
	}
	void MachinegunBox::OnCollisionExit(Collider* other)
	{
	}
}