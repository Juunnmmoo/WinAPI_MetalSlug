#include "moSelectElevator.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"
#include "moTime.h"
#include "moPlayerIdle.h"
#include "moPlayerIdleBottom.h"
#include "moScene.h"
#include "moSceneManager.h"

namespace mo {
	SelectElevator::SelectElevator(Vector2 pos, float f)
		: mPos(pos)
		, aWaitTime(f)
		, time(0.0f)
		, stopMove(false)
	{
	}
	SelectElevator::~SelectElevator()
	{
	}
	void SelectElevator::Initialize()
	{
		
		mImage = Resources::Load<Image>(L"SelectElevator", L"..\\Resources\\BackGround\\SelectScene\\SelectElevator.bmp");

		GameObject::Initialize();

	}
	void SelectElevator::Update()
	{
		
		
		time += Time::DeltaTime();

		if (mPos.y < -400.0f)
			stopMove = true;

		if (time >= aWaitTime && !stopMove)
		{
			mPos.y -= 300.0f * Time::DeltaTime();
		}

		if (goingBack && mPos.y < 205)
		{
			mPos.y += 500.0f * Time::DeltaTime();


			top->GetComponent<Transform>()->SetPos(mPos + Vector2(100.0f, 440.0f));
			bottom->GetComponent<Transform>()->SetPos(mPos + Vector2(100.0f, 480.0f));



		}
		GameObject::Update();

	}
	void SelectElevator::Render(HDC mHdc)
	{
	
		TransparentBlt(mHdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(mHdc);

	}
	void SelectElevator::SetGoingBack()
	{
		goingBack = true; 
		stopMove = true;

		Scene* curScene = SceneManager::GetActiveScene();
		
		top= new PlayerIdle();
		bottom = new PlayerIdleBottom();

		top->GetComponent<Transform>()->SetPos(mPos + Vector2(100.0f, 440.0f));
		bottom->GetComponent<Transform>()->SetPos(mPos + Vector2(100.0f, 480.0f));

		top->GetComponent<Transform>()->SetScale(Vector2(3.0f, 3.0f));
		bottom->GetComponent<Transform>()->SetScale(Vector2(3.0f, 3.0f));

		curScene->AddGameObject(bottom, eLayerType::Slave);
		curScene->AddGameObject(top, eLayerType::Slave);
		

		top->Initialize();
		bottom->Initialize();
	}
}