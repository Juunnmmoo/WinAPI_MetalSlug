#include "moMarco.h"
#include "moImage.h"
#include "moResources.h"

namespace mo {
	Marco::Marco()
	{
	}
	Marco::~Marco()
	{
	}
	void Marco::Initialize()
	{
		Image* image = Resources::Load<Image>(L"Kirby", L"..\\Resources\\IceKirby.bmp");
		
		GameObject::Initialize();
	}
	void Marco::Update()
	{
		GameObject::Update();
	}
	void Marco::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
}