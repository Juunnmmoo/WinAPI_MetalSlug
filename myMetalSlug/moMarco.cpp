#include "moMarco.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"

namespace mo {
	Marco::Marco()
	{
	}
	Marco::~Marco()
	{
	}
	void Marco::Initialize()
	{
		image = Resources::Load<Image>(L"Kirby", L"..\\Resources\\IceKirby.bmp");
		
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 50.0f, 50.0f });

		GameObject::Initialize();
	}
	void Marco::Update()
	{

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
		GameObject::Update();
	}
	void Marco::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();

		TransparentBlt(mHdc, tr->GetPos().x, tr->GetPos().y
			,image->GetWidth(), image->GetHeight()
			,image->GetHdc(), 0, 0
			,image->GetWidth(), image->GetHeight(),
			RGB(0, 127, 0));

		GameObject::Render(mHdc);
	}
}