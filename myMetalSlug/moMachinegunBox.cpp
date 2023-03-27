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
		tr->SetPos(Vector2(600.0f, 600.0f));
		tr->SetScale(Vector2{ 3.0f, 3.0f });

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 30.0f, 30.0f});
		//mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });

		GameObject::Initialize();

	}
	void MachinegunBox::Update()
	{
		GameObject::Update();

	}
	void MachinegunBox::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void MachinegunBox::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player) {
			Marco* marco = dynamic_cast<Marco*>(other->GetOwner());
			marco->ChangeWeapon(eMarcoWeapon::Machinegun);
		
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