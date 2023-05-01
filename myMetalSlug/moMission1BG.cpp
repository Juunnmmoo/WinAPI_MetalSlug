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
		ground = Resources::Load<Image>(L"Mission1BG_Ground", L"..\\Resources\\BackGround\\Mission1BG_GroundTest.bmp");
		sky = Resources::Load<Image>(L"Mission1BG_Sky", L"..\\Resources\\BackGround\\Mission1BG_Sky.bmp");
		sky2 = Resources::Load<Image>(L"Mission1BG_Sky2", L"..\\Resources\\BackGround\\Mission1BG_Sky2.bmp");

		weaponLayers.push_back(eLayerType::EnemyBulletR);
		weaponLayers.push_back(eLayerType::PlayerPistol);
		weaponLayers.push_back(eLayerType::PlayerMachinegun);
		weaponLayers.push_back(eLayerType::PlayerBomb);

		charLayers.push_back(eLayerType::BulletBox);
		charLayers.push_back(eLayerType::EnemyR);
		charLayers.push_back(eLayerType::Slave);
		charLayers.push_back(eLayerType::EnemyR_F);


		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(0.0f, 0.0f));

		Vector2 lookPosition = Camera::GetLookPosition();
		Camera::SetLookPosition(Vector2(550.0f, 525.0f));

		GameObject::Initialize();
	}

	void Mission1BG::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();
		Vector2 cameraPos = Camera::GetDistance();


		/*if (cameraPos.x >= 3250.0f &&
			mPos.y >= 96.0f &&
			Camera::GetIsMove())
		{
			mPos.y -= 2;
		}

		tr->SetPos(Vector2(cameraPos.x, mPos.y));*/

		Vector2 lookPosition = Camera::GetLookPosition();

		if (cameraPos.x >= 3250.0f &&
			lookPosition.y >= 465.0f &&
			Camera::GetIsMove())
		{
			lookPosition.y -= 2;
		}

		Camera::SetLookPosition(lookPosition);

		for (eLayerType layer : weaponLayers)
		{
			std::vector<GameObject*>& gameObj = curScene->GetGameObjects(layer);

			for (GameObject* obj : gameObj)
			{

				Transform* tr = obj->GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				
				if (layer == eLayerType::PlayerPistol || layer == eLayerType::PlayerMachinegun)
				{

					if (ground->GetPixel(pos.x, pos.y + mPos.y) == RGB(248, 0, 248)) {
						obj->SetState(eState::Pause);
					}
				}
				else
				{
					RigidBody* rb = obj->GetComponent<RigidBody>();

					if (ground->GetPixel(pos.x, pos.y + mPos.y) == RGB(248, 0, 248)) {
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

		for (eLayerType layer : charLayers)
		{
			std::vector<GameObject*>& gameObj = curScene->GetGameObjects(layer);

			for (GameObject* obj : gameObj)
			{
				Transform* tr = obj->GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				RigidBody* rb = obj->GetComponent<RigidBody>();

				if (ground->GetPixel(pos.x, pos.y + mPos.y) == RGB(248, 0, 248)) {
					pos.y--;
					rb->SetGround(true);
					rb->SetFall(false);
					tr->SetPos(pos);
				}
				else if (ground->GetPixel(pos.x, pos.y + mPos.y) == RGB(0, 255, 255)) {
					if (rb->GetVelocity().y >= 0.0f)
					{
						pos.y--;
						rb->SetGround(true);
						rb->SetFall(false);
						tr->SetPos(pos);
					}
					else
					{
						rb->SetGround(false);
					}
				}
				else if (ground->GetPixel(pos.x, pos.y + mPos.y) == RGB(255, 255, 0)) {
					rb->SetGround(false);
					rb->SetFall(true);
				}
				else {
					rb->SetGround(false);
				}
				
			}
		}

		Transform* marcoTR = mPlayer->GetComponent<Transform>();
		Vector2 pos = marcoTR->GetPos();
		RigidBody* rb = mPlayer->GetComponent<RigidBody>();

		if (ground->GetPixel(pos.x, pos.y + 40 + mPos.y) == RGB(248, 0, 248)) {
			pos.y--;
			rb->SetGround(true);
			marcoTR->SetPos(pos);
		}
		else if (ground->GetPixel(pos.x, pos.y + 40 + mPos.y) == RGB(0, 255, 255)) {
			if (rb->GetVelocity().y >= 0.0f)
			{
				pos.y--;
				rb->SetGround(true);
				marcoTR->SetPos(pos);
			}
			else
			{
				rb->SetGround(false);
			}
		}
		else {
			rb->SetGround(false);
		}
			
		if (pos.x >= 6950.0f && pos.x < 7150.0f && !stopOnce)
		{
			stopOnce = true;
			Camera::SetStop(true);
		}

		if (!boss2Stop)
		{
			if (pos.x >= 12350.0f)
			{
				boss2Stop = true;
				Camera::SetStop(true);
			}
		}
		if (!skyChange)
		{
			if (pos.x >= 7800.0f)
			{
				skyChange = true;
			}
		}


		GameObject::Update();
	}

	void Mission1BG::Render(HDC mHdc)
	{

		Transform* tr = GetComponent<Transform>();
		//Vector2 mPos = tr->GetPos();
		Vector2 mPos = Camera::GetDistance();


		//BitBlt(mHdc, 0, 0, application.GetWidth(), application.GetHeight(), ground->GetHdc(), pos.x, pos.y, SRCCOPY);
		BitBlt(mHdc, 0, 0, application.GetWidth(), application.GetHeight(), ground->GetHdc(), mPos.x, mPos.y, SRCCOPY);

		/*if (skyChange)
		{
			BitBlt(mHdc, 0, 0, application.GetWidth(), sky2->GetHeight(), sky2->GetHdc(), mPos.x * 0.5 - 4000, 0, SRCCOPY);
		}
		else
		{
			BitBlt(mHdc, 0, 0, application.GetWidth(), sky->GetHeight(), sky->GetHdc(), mPos.x * 0.5, 0, SRCCOPY);
		}*/

		BitBlt(mHdc, 0, 0, application.GetWidth(), sky->GetHeight(), sky->GetHdc(), mPos.x * 0.5, 0, SRCCOPY);

		//TransparentBlt(mHdc, -pos.x, -pos.y, main->GetWidth(), main->GetHeight(), main->GetHdc(), 0, 0, main->GetWidth(), main->GetHeight(), RGB(248, 0, 248));
		TransparentBlt(mHdc, 0, 0, application.GetWidth(), application.GetHeight(), main->GetHdc(), mPos.x, mPos.y, application.GetWidth(), application.GetHeight(), RGB(255, 0, 255));


		GameObject::Render(mHdc);
	}

}