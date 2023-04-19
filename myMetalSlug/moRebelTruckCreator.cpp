#include "moRebelTruckCreator.h"
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
#include "moRebelTruck1.h"
#include "moRebelTruck2.h"
#include "moCamel.h"

namespace mo {
	RebelTruckCreator::RebelTruckCreator(Marco* marco)
		:player(marco)
	{
	}
	RebelTruckCreator::~RebelTruckCreator()
	{
	}
	void RebelTruckCreator::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(5200.0f, 0.0f));

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 750.0f });

		GameObject::Initialize();
	}
	void RebelTruckCreator::Update()
	{
		GameObject::Update();

	}
	void RebelTruckCreator::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void RebelTruckCreator::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			if (!stopCreate)
			{
				stopCreate = true;

				Scene* curScene = SceneManager::GetActiveScene();


				RebelTruck2* truck2 = new RebelTruck2();
				curScene->AddGameObject(truck2, eLayerType::front);

				RebelTruck1* truck1 = new RebelTruck1(player, truck2, curScene, Vector2(5650.0f, 0.0f));
				curScene->AddGameObject(truck1, eLayerType::Enemy);
				truck1->Initialize();
				truck2->Initialize();
				truck1->GetComponent<Transform>()->SetPos(Vector2(6200.0f, 650.0f));

				Camera::SetStop(true);

			}
		}
	}
	void RebelTruckCreator::OnCollisionStay(Collider* other)
	{
	}
	void RebelTruckCreator::OnCollisionExit(Collider* other)
	{
	}
}