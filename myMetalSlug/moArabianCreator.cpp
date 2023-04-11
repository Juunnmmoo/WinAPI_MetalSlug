#include "moArabianCreator.h"
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
	ArabianCreator::ArabianCreator(Marco* marco)
		: time(0.0f)
		, stopCreate(false)
		, player(marco)
	{
	}
	ArabianCreator::~ArabianCreator()
	{
	}
	void ArabianCreator::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(1100.0f, 750.0f));

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetLeftTop(Vector2(0.0f, -750.0f));
		mCollider->SetSize(Vector2{ 700.0f, 750.0f });

		GameObject::Initialize();
	}
	void ArabianCreator::Update()
	{
		time += Time::DeltaTime();

		if (time >= 5.0f && !stopCreate)
		{
			time = 0.0f;

			Scene* curScene = SceneManager::GetActiveScene();

			Arabian* arabian = new Arabian(player, curScene);

			curScene->AddGameObject(arabian, eLayerType::Enemy);
			arabian->Initialize();
			arabian->GetComponent<Transform>()->SetPos(Vector2(2500.0f, 600.0f));
		}
		GameObject::Update();
	}
	void ArabianCreator::Render(HDC mHdc)
	{

		GameObject::Render(mHdc);
	}
	void ArabianCreator::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player) {
			object::Destory(this);
		}
	}
	void ArabianCreator::OnCollisionStay(Collider* other)
	{
	}
	void ArabianCreator::OnCollisionExit(Collider* other)
	{
	}
}