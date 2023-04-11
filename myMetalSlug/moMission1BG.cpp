#include "moMission1BG.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"
#include "moMarco.h"
#include "moRigidBody.h"
#include "moScene.h"
#include "moObject.h"
#include "moBulletSFX.h"

extern mo::Application application;

namespace mo {
	Mission1BG::Mission1BG(Scene* scene)
		:TopDiff(133)
		, curScene(scene)
	{
	}

	Mission1BG::~Mission1BG()
	{
	}

	void Mission1BG::Initialize()
	{		

		main = Resources::Load<Image>(L"Mission1BG_Main", L"..\\Resources\\BackGround\\Mission1BG_Main.bmp");
		ground = Resources::Load<Image>(L"Mission1BG_Ground", L"..\\Resources\\BackGround\\Mission1BG_Ground.bmp");
		
		layers.push_back(eLayerType::BulletBox);
		layers.push_back(eLayerType::Enemy);
		layers.push_back(eLayerType::EnemyBulletR);
		layers.push_back(eLayerType::PlayerPistol);

		GameObject::Initialize();
	}

	void Mission1BG::Update()
	{

		for (eLayerType layer : layers)
		{
			std::vector<GameObject*>& gameObj = curScene->GetGameObjects(layer);

			for (GameObject* obj : gameObj)
			{

				Transform* tr = obj->GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				
				if (layer == eLayerType::PlayerPistol)
				{

					if (ground->GetPixel(pos.x, pos.y) == RGB(248, 0, 248)) {
						obj->SetState(eState::Pause);
					}
				}
				else
				{
					RigidBody* rb = obj->GetComponent<RigidBody>();

					if (ground->GetPixel(pos.x, pos.y) == RGB(248, 0, 248)) {
						pos.y--;
						rb->SetGround(true);
						tr->SetPos(pos);
					}
					else {
						rb->SetGround(false);
					}
				}
			}
		}

		Transform* marcoTR = mPlayer->GetComponent<Transform>();
		Vector2 pos = marcoTR->GetPos();
		RigidBody* rb = mPlayer->GetComponent<RigidBody>();

		if (ground->GetPixel(pos.x, pos.y + 40) == RGB(248, 0, 248)) {
			pos.y--;
			rb->SetGround(true);
			marcoTR->SetPos(pos);
		}
		else {
			rb->SetGround(false);
		}
		
		GameObject::Update();
	}

	void Mission1BG::Render(HDC mHdc)
	{

		Vector2 pos = Camera::GetDistance();

		BitBlt(mHdc, -pos.x, -pos.y, ground->GetWidth(), ground->GetHeight(), ground->GetHdc(), 0, 0, SRCCOPY);
		//TransparentBlt(mHdc, -pos.x, -pos.y, main->GetWidth(), main->GetHeight(), main->GetHdc(), 0, 0, main->GetWidth(), main->GetHeight(), RGB(248, 0, 248));
		TransparentBlt(mHdc, 0, 0, application.GetWidth(), application.GetHeight(), main->GetHdc(), pos.x, pos.y, application.GetWidth(), application.GetHeight(), RGB(248, 0, 248));


		GameObject::Render(mHdc);
	}

}