#include "moMission1BG.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"

extern mo::Application application;

namespace mo {



	Mission1BG::Mission1BG()
	{
	}

	Mission1BG::~Mission1BG()
	{
	}

	void Mission1BG::Initialize()
	{
		
		mImage = Resources::Load<Image>(L"Mission1BG_02", L"..\\Resources\\BackGround\\Mission1BG_02.bmp");

		GameObject::Initialize();
		GameObject::Initialize();
	}

	void Mission1BG::Update()
	{
		GameObject::Update();
	}

	void Mission1BG::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		//Vector2 pos = Camera::CaluatePos(tr->GetPos());
		Vector2 pos = Camera::GetDistance();


		// 한번더 공부
		TransparentBlt(mHdc, -1, -1, application.GetWidth(), application.GetHeight(), mImage->GetHdc(),pos.x, pos.y + 40, application.GetWidth(), application.GetHeight(), RGB(248, 0, 248));

		
		GameObject::Render(mHdc);
	}

}