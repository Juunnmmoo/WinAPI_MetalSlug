#include "moSelectBG.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"

extern mo::Application application;

namespace mo {
	SelectBG::SelectBG()
	{
	}
	SelectBG::~SelectBG()
	{
	}
	void SelectBG::Initialize()
	{
		mImage = Resources::Load<Image>(L"SelectBG", L"..\\Resources\\BackGround\\SelectScene\\SelectBG.bmp");

		GameObject::Initialize();

	}
	void SelectBG::Update()
	{

		GameObject::Update();

	}
	void SelectBG::Render(HDC mHdc)
	{
		TransparentBlt(mHdc, 0, 0, application.GetWidth(), application.GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		GameObject::Render(mHdc);

	}
}