#include "moOutSideWallL.h"
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
	OutSideWallL::OutSideWallL()
	{
	}
	OutSideWallL::~OutSideWallL()
	{
	}
	void OutSideWallL::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(0.0f, 0.0f));

		Collider* mCollider = AddComponent<Collider>();
		//mCollider->SetLeftTop(Vector2(0.0f, 0.0f));
		mCollider->SetSize(Vector2{ 20.0f, 850.0f });

		GameObject::Initialize();
	}
	void OutSideWallL::Update()
	{


		GameObject::Update();
	}
	void OutSideWallL::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void OutSideWallL::OnCollisionEnter(Collider* other)
	{
	}
	void OutSideWallL::OnCollisionStay(Collider* other)
	{
	}
	void OutSideWallL::OnCollisionExit(Collider* other)
	{
	}
}