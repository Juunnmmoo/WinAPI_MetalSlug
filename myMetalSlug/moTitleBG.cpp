#include "moTitleBG.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"

extern mo::Application application;
namespace mo {



	TitleBG::TitleBG()
	{
	}

	TitleBG::~TitleBG()
	{
	}

	void TitleBG::Initialize()
	{

		mImage = Resources::Load<Image>(L"TitleBG", L"..\\Resources\\BackGround\\Title.bmp");
		GameObject::Initialize();
		GameObject::Initialize();
	}

	void TitleBG::Update()
	{
		GameObject::Update();
	}

	void TitleBG::Render(HDC mHdc)
	{
		TransparentBlt(mHdc, -1, -1, application.GetWidth(), application.GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		//BitBlt(mHdc, -1, -1, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		GameObject::Render(mHdc);
	}

}