#include "moCharUI.h"
#include "moAnimator.h"
#include "momoEngine.h"
#include "moObject.h"
#include "moTransform.h"
#include "moResources.h"
#include "moImage.h"
#include "moTime.h"
#include "moCamera.h"
#include "moObject.h"

namespace mo {
	CharUI::CharUI(eCharType type, Vector2 pos, Vector2 scale)
		: mType(type)
		, mPos(pos)
		, mScale(scale)
		, mTime(0.0f)
		, stopTime(0.0f)
	{
	}
	CharUI::~CharUI()
	{
	}
	void CharUI::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(mPos);
		tr->SetScale(mScale);

		SetState(eState::Active);

		Image* uiImage = Resources::Load<Image>(L"CharUI", L"..\\Resources\\UI\\CharUI.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->SetunUseCameraPos(true);

		mAnimator->CreateAnimation(L"A", uiImage, Vector2(50.0f* 0, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"B", uiImage, Vector2(50.0f* 1, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"C", uiImage, Vector2(50.0f* 2, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"D", uiImage, Vector2(50.0f* 3, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"E", uiImage, Vector2(50.0f* 4, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"F", uiImage, Vector2(50.0f* 5, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"G", uiImage, Vector2(50.0f* 6, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"H", uiImage, Vector2(50.0f* 7, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"I", uiImage, Vector2(50.0f* 8, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"J", uiImage, Vector2(50.0f* 9, 50.0f* 0), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"K", uiImage, Vector2(50.0f* 10,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"L", uiImage, Vector2(50.0f* 11,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M", uiImage, Vector2(50.0f* 12,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"N", uiImage, Vector2(50.0f* 13,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"O", uiImage, Vector2(50.0f* 14,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P", uiImage, Vector2(50.0f* 15,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Q", uiImage, Vector2(50.0f* 16,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"R", uiImage, Vector2(50.0f* 17,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"S", uiImage, Vector2(50.0f* 18,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"T", uiImage, Vector2(50.0f* 19,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"U", uiImage, Vector2(50.0f* 20,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"V", uiImage, Vector2(50.0f* 21,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"W", uiImage, Vector2(50.0f* 22,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"X", uiImage, Vector2(50.0f* 23,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Y", uiImage, Vector2(50.0f* 24,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Z", uiImage, Vector2(50.0f* 25,50.0f* 0),50.0f, 30, 15, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"A_B", uiImage, Vector2(50.0f* 0, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"B_B", uiImage, Vector2(50.0f* 1, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"C_B", uiImage, Vector2(50.0f* 2, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"D_B", uiImage, Vector2(50.0f* 3, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"E_B", uiImage, Vector2(50.0f* 4, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"F_B", uiImage, Vector2(50.0f* 5, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"G_B", uiImage, Vector2(50.0f* 6, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"H_B", uiImage, Vector2(50.0f* 7, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"I_B", uiImage, Vector2(50.0f* 8, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"J_B", uiImage, Vector2(50.0f* 9, 50.0f* 1), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"K_B", uiImage, Vector2(50.0f* 10,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"L_B", uiImage, Vector2(50.0f* 11,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_B", uiImage, Vector2(50.0f* 12,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"N_B", uiImage, Vector2(50.0f* 13,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"O_B", uiImage, Vector2(50.0f* 14,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P_B", uiImage, Vector2(50.0f* 15,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Q_B", uiImage, Vector2(50.0f* 16,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"R_B", uiImage, Vector2(50.0f* 17,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"S_B", uiImage, Vector2(50.0f* 18,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"T_B", uiImage, Vector2(50.0f* 19,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"U_B", uiImage, Vector2(50.0f* 20,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"V_B", uiImage, Vector2(50.0f* 21,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"W_B", uiImage, Vector2(50.0f* 22,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"X_B", uiImage, Vector2(50.0f* 23,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Y_B", uiImage, Vector2(50.0f* 24,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Z_B", uiImage, Vector2(50.0f* 25,50.0f* 1),50.0f, 30, 15, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"M1", uiImage, Vector2(50.0f * 0, 50.0f * 2),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M2", uiImage, Vector2(50.0f * 1, 50.0f * 2),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M3", uiImage, Vector2(50.0f * 2, 50.0f * 2),50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"!", uiImage, Vector2(50.0f * 3, 50.0f * 2), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"M1_B", uiImage, Vector2(50.0f * 0, 50.0f * 2), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M2_B", uiImage, Vector2(50.0f * 1, 50.0f * 2), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M3_B", uiImage, Vector2(50.0f * 2, 50.0f * 2), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"!_B", uiImage, Vector2(50.0f * 3, 50.0f * 2), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"0", uiImage, Vector2(50.0f * 0, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"1", uiImage, Vector2(50.0f * 1, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"2", uiImage, Vector2(50.0f * 2, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"3", uiImage, Vector2(50.0f * 3, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"4", uiImage, Vector2(50.0f * 4, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"5", uiImage, Vector2(50.0f * 5, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"6", uiImage, Vector2(50.0f * 6, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"7", uiImage, Vector2(50.0f * 7, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"8", uiImage, Vector2(50.0f * 8, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"9", uiImage, Vector2(50.0f * 9, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"&", uiImage, Vector2(50.0f * 12, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"None", uiImage, Vector2(50.0f * 13, 50.0f * 4), 50.0f, 30, 15, 1, Vector2::Zero, 0.05);

		//mAnimator->Play(L"M_B", true);

		mState = eUiType::None;

		GameObject::Initialize();
	}
	void CharUI::Update()
	{
		switch (mState) {
		case mo::CharUI::eUiType::StartUi:
			startUi();
			break;
		case mo::CharUI::eUiType::BulletNumUi:
			bulletNumUi();
			break;
		case mo::CharUI::eUiType::TimeUi:
			timeUi();
			break;
		case mo::CharUI::eUiType::GoUi:
			goUi();
			break;

		}

		mTime += Time::DeltaTime();

		GameObject::Update();
	}
	void CharUI::Render(HDC mHdc)
	{
		

		GameObject::Render(mHdc);
	}
	void CharUI::ChangeAnimation(eCharType type)
	{
		if (type == eCharType::M)
		{
			mAnimator->Play(L"M", false);
		}
		else if (type == eCharType::I)
		{
			mAnimator->Play(L"I", false);

		}
		else if (type == eCharType::S)
		{
			mAnimator->Play(L"S", false);

		}
		else if (type == eCharType::O)
		{
			mAnimator->Play(L"O", false);

		}
		else if (type == eCharType::N)
		{
			mAnimator->Play(L"N", false);

		}
		else if (type == eCharType::S)
		{
			mAnimator->Play(L"S", false);

		}
		else if (type == eCharType::T)
		{
			mAnimator->Play(L"T", false);

		}
		else if (type == eCharType::A)
		{
			mAnimator->Play(L"A", false);

		}
		else if (type == eCharType::R)
		{
			mAnimator->Play(L"R", false);

		}
		else if (type == eCharType::Mission1)
		{
			mAnimator->Play(L"M1", false);
		}
		else if (type == eCharType::ExclamationMark)
		{
			mAnimator->Play(L"!", false);
		}
		else if (type == eCharType::C)
		{
			mAnimator->Play(L"C", false);
		}
		else if (type == eCharType::P)
		{
			mAnimator->Play(L"P", false);
		}
		else if (type == eCharType::L)
		{
			mAnimator->Play(L"L", false);
		}
		else if (type == eCharType::T)
		{
			mAnimator->Play(L"T", false);
		}
		else if (type == eCharType::E)
		{
			mAnimator->Play(L"E", false);
		}

	}
	void CharUI::startUi()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(tr->GetPos());

		if (mTime <= 0.5f)
		{
			pos.x += 250.0f * Time::DeltaTime();
			pos.y += 250.0f * Time::DeltaTime();
		}
		else if (mTime > 0.5f && mTime <= stopTime)
		{
			if(!isChanged)
			{ 

				isChanged = true;
				ChangeAnimation(mType);
			}
		}
		if (mTime > stopTime)
		{
			pos.y += 1000.0f * mDir.y * Time::DeltaTime();
			pos.x += 1000.0f * mDir.x * Time::DeltaTime();
		}

		if ((cPos.x < 0.0f || cPos.x > 1100.0f) && (cPos.y < 0.0f || cPos.y > 750.0f))
		{
			object::Destory(this);
		}

		tr->SetPos(pos);
	}
	void CharUI::bulletNumUi()
	{
	}
	void CharUI::timeUi()
	{
	}
	void CharUI::goUi()
	{
	}
}