#include "moCamelArabianCreator.h"
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
#include "moCamelArabian01.h"
#include "moCamelArabian02.h"
#include "moCamel.h"
namespace mo {
	CamelArabianCreator::CamelArabianCreator(Marco* marco)
		:player(marco)
	{
	}
	CamelArabianCreator::~CamelArabianCreator()
	{
	}
	void CamelArabianCreator::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(3200.0f, 0.0f));

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 750.0f });

		GameObject::Initialize();
	}
	void CamelArabianCreator::Update()
	{
		GameObject::Update();

	}
	void CamelArabianCreator::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void CamelArabianCreator::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			if (!stopCreate)
			{
				stopCreate = true;

				Scene* curScene = SceneManager::GetActiveScene();

				Camel* camel = new Camel();
				CamelArabian02* camelArabian02 = new CamelArabian02();
				CamelArabian01* camelArabian01 = new CamelArabian01(player, camel, camelArabian02, curScene);

				curScene->AddGameObject(camelArabian01, eLayerType::Enemy);
				curScene->AddGameObject(camel, eLayerType::Enemy);
				curScene->AddGameObject(camelArabian02, eLayerType::Enemy);
			
			
			
				camelArabian01->Initialize();
				camel->Initialize();
				camelArabian02->Initialize();
				camelArabian01->GetComponent<Transform>()->SetPos(Vector2(4400.0f, 480.0f));

				Camera::SetStop(true);

			}
		}
	}
	void CamelArabianCreator::OnCollisionStay(Collider* other)
	{
	}
	void CamelArabianCreator::OnCollisionExit(Collider* other)
	{
	}
}