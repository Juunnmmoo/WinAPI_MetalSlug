#include "moMission1BG.h"
#include "moResources.h"
#include "moImage.h"

namespace mo {



	Mission1BG::Mission1BG()
	{
	}

	Mission1BG::~Mission1BG()
	{
	}

	void Mission1BG::Initialize()
	{

		mImage = Resources::Load<Image>(L"BG_Stage1", L"..\\Resources\\MissionBG_01.bmp");
		GameObject::Initialize();
		GameObject::Initialize();
	}

	void Mission1BG::Update()
	{
		GameObject::Update();
	}

	void Mission1BG::Render(HDC mHdc)
	{
		BitBlt(mHdc, -1, -1, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		GameObject::Render(mHdc);
	}

}