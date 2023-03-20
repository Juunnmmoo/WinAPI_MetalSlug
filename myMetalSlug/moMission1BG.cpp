#include "moMission1BG.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"

extern mo::Application application;

namespace mo {
	Mission1BG::Mission1BG()
		:TopDiff(133)
	{
	}

	Mission1BG::~Mission1BG()
	{
	}

	void Mission1BG::Initialize()
	{
		
		mImage = Resources::Load<Image>(L"Mission1BG_02", L"..\\Resources\\BackGround\\Mission1BG_02.bmp");

		Vector2 pos = Camera::GetLookPosition();
		pos += Vector2(0.0f, 133.0f);
		Camera::SetLookPosition(pos);

		GameObject::Initialize();
	}

	void Mission1BG::Update()
	{
		Vector2 pos = Camera::GetLookPosition();

		if (pos.x >= 3400.0f
			&& pos.y>= 455.0f
			&& Camera::GetIsMove)
		{
			pos.y--;
			Camera::SetLookPosition(pos);
		}
		

		GameObject::Update();
	}

	void Mission1BG::Render(HDC mHdc)
	{
		Vector2 pos = Camera::GetDistance();


		// 한번더 공부
		TransparentBlt(mHdc, 0, 0, application.GetWidth(), application.GetHeight(), mImage->GetHdc(), pos.x, pos.y, application.GetWidth(), application.GetHeight(), RGB(248, 0, 248));
		//TransparentBlt(mHdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(),0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(248, 0, 248));


		GameObject::Render(mHdc);
	}

}