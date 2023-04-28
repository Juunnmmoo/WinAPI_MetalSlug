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
	ArabianCreator::ArabianCreator(Marco* marco, Vector2 pos, Vector2 size, Vector2 create)
		: time(0.0f)
		, startCreate(false)
		, player(marco)
		, mPos(pos)
		, createVector(create)
		, mSize(size)
	{
	}
	ArabianCreator::~ArabianCreator()
	{
	}
	void ArabianCreator::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(mPos);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(mSize);

		GameObject::Initialize();
	}
	void ArabianCreator::Update()
	{
		time += Time::DeltaTime();

		if (time >= 3.0f && startCreate)
		{
			time = 0.0f;

			Scene* curScene = SceneManager::GetActiveScene();

			Arabian* arabian = new Arabian(player, curScene, Arabian::eArabianState::Move);

			curScene->AddGameObject(arabian, eLayerType::EnemyR_F);
			arabian->Initialize();
			arabian->GetComponent<Transform>()->SetPos(createVector);
		}

		Collider* mCollider = GetComponent<Collider>();
		Transform* tr = GetComponent<Transform>();
		Vector2 cPos = Camera::CaluatePos(tr->GetPos() + mCollider->GetSize());

		if (player->GetComponent<Transform>()->GetPos().x > (tr->GetPos().x + mCollider->GetSize().x))
			object::Destory(this);


		GameObject::Update();
	}
	void ArabianCreator::Render(HDC mHdc)
	{

		GameObject::Render(mHdc);
	}
	void ArabianCreator::OnCollisionEnter(Collider* other)
	{
		
	}
	void ArabianCreator::OnCollisionStay(Collider* other)
	{
		startCreate = true;
	}
	void ArabianCreator::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player && other->GetOwner()->GetState() == eState::Active) {
			object::Destory(this);
		}
	}
}