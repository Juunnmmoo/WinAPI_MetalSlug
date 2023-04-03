#include "moSelectCharacters.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"

namespace mo {
	SelectCharactor::SelectCharactor(Vector2 pos, Vector2 iPos)
		: mPos(pos)
		, imagePos(iPos)
	{
	}
	SelectCharactor::~SelectCharactor()
	{
	}
	void SelectCharactor::Initialize()
	{

		mImage = Resources::Load<Image>(L"SelectCharactors", L"..\\Resources\\BackGround\\SelectScene\\SelectCharactor.bmp");

		GameObject::Initialize();

	}
	void SelectCharactor::Update()
	{
		GameObject::Update();

	}
	void SelectCharactor::Render(HDC mHdc)
	{

		TransparentBlt(mHdc, mPos.x, mPos.y, 223, 418, mImage->GetHdc(), imagePos.x, imagePos.y, 223, 418, RGB(255, 0, 255));

		GameObject::Render(mHdc);

	}
}