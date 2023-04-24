#include "moArmsUI.h"
#include "moAnimator.h"
#include "momoEngine.h"
#include "moObject.h"
#include "moTransform.h"
#include "moResources.h"
#include "moImage.h"
#include "moCharUI.h"
#include "moTime.h"
#include "moSceneManager.h"
#include "moScene.h"
#include "moMarco.h"

namespace mo {
	ArmsUI::ArmsUI(Marco* marco, Scene* scene)
		: curScene(scene)
		, mPlayer(marco)
		, unitsNum(0)
		, tensNum(0)
		, hundredsNum(0)
	{ 
	}	 
	ArmsUI::~ArmsUI()
	{
		/*delete hundreds;
		delete tens;
		delete units;
		delete tens_bomb;
		delete units_bomb;

		hundreds = nullptr;
		tens = nullptr;
		units = nullptr;
		tens_bomb = nullptr;
		units_bomb = nullptr;*/
	}
	void ArmsUI::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Vector2(250.0f, 50.0f);
		tr->SetPos(pos);
		
		armsImage = Resources::Load<Image>(L"Arms", L"..\\Resources\\UI\\Arms.bmp");
		bombImage = Resources::Load<Image>(L"Bombs", L"..\\Resources\\UI\\Bombs.bmp");

		hundreds = new CharUI(eCharType::None, Vector2(pos.x + 15.0f, pos.y + 60.0f), Vector2(1.5f, 1.5f));
		tens = new CharUI(eCharType::None, Vector2(pos.x + 40.0f, pos.y + 60.0f), Vector2(1.5f, 1.5f));
		units = new CharUI(eCharType::None, Vector2(pos.x + 65.0f, pos.y + 60.0f), Vector2(1.5f, 1.5f));
		tens_bomb = new CharUI(eCharType::None, Vector2(pos.x + 150.0f, pos.y + 60.0f), Vector2(1.5f, 1.5f));
		units_bomb = new CharUI(eCharType::None, Vector2(pos.x + 175.0f, pos.y + 60.0f), Vector2(1.5f, 1.5f));
		

		curScene->AddGameObject(units,eLayerType::Effect);
		curScene->AddGameObject(tens, eLayerType::Effect);
		curScene->AddGameObject(hundreds, eLayerType::Effect);
		curScene->AddGameObject(units_bomb, eLayerType::Effect);
		curScene->AddGameObject(tens_bomb, eLayerType::Effect);

		units->Initialize();
		tens->Initialize();
		hundreds->Initialize();
		units_bomb->Initialize();
		tens_bomb->Initialize();

		GameObject::Initialize();

	}
	void ArmsUI::Update()
	{
		

		if (mPlayer->GetMarcoWeaponType() == eMarcoWeapon::Pistol)
		{
			units->GetAnimator()->Play(L"None", false);
			tens->GetAnimator()->Play(L"&", false);
			hundreds->GetAnimator()->Play(L"None", false);
		}	
		else
		{
			int Cnt = mPlayer->GetBulletNum();
			
			unitsNum = Cnt % 10;
			Cnt /= 10;

			tensNum = Cnt % 10;
			Cnt /= 10;

			hundredsNum = Cnt % 10;

			if (unitsNum == 0)
			{
				units->GetAnimator()->Play(L"0", false);
			}else if (unitsNum == 1)
			{
				units->GetAnimator()->Play(L"1", false);
			}
			else if (unitsNum == 2)
			{
				units->GetAnimator()->Play(L"2", false);
			}
			else if (unitsNum == 3)
			{
				units->GetAnimator()->Play(L"3", false);
			}
			else if (unitsNum == 4)
			{
				units->GetAnimator()->Play(L"4", false);
			}
			else if (unitsNum == 5)
			{
				units->GetAnimator()->Play(L"5", false);
			}
			else if (unitsNum == 6)
			{
				units->GetAnimator()->Play(L"6", false);
			}
			else if (unitsNum == 7)
			{
				units->GetAnimator()->Play(L"7", false);
			}
			else if (unitsNum == 8)
			{
				units->GetAnimator()->Play(L"8", false);
			}
			else if (unitsNum == 9)
			{
				units->GetAnimator()->Play(L"9", false);
			}
			

			if (tensNum == 0)
			{
				tens->GetAnimator()->Play(L"0", false);
			}
			else if (tensNum == 1)
			{
				tens->GetAnimator()->Play(L"1", false);
			}
			else if (tensNum == 2)
			{
				tens->GetAnimator()->Play(L"2", false);
			}
			else if (tensNum == 3)
			{
				tens->GetAnimator()->Play(L"3", false);
			}
			else if (tensNum == 4)
			{
				tens->GetAnimator()->Play(L"4", false);
			}
			else if (tensNum == 5)
			{
				tens->GetAnimator()->Play(L"5", false);
			}
			else if (tensNum == 6)
			{
				tens->GetAnimator()->Play(L"6", false);
			}
			else if (tensNum == 7)
			{
				tens->GetAnimator()->Play(L"7", false);
			}
			else if (tensNum == 8)
			{
				tens->GetAnimator()->Play(L"8", false);
			}
			else if (tensNum == 9)
			{
				tens->GetAnimator()->Play(L"9", false);
			}


			if (hundredsNum == 0)
			{
				hundreds->GetAnimator()->Play(L"0", false);
			}
			else if (hundredsNum == 1)
			{
				hundreds->GetAnimator()->Play(L"1", false);
			}
			else if (hundredsNum == 2)
			{
				hundreds->GetAnimator()->Play(L"2", false);
			}
			else if (hundredsNum == 3)
			{
				hundreds->GetAnimator()->Play(L"3", false);
			}
			else if (hundredsNum == 4)
			{
				hundreds->GetAnimator()->Play(L"4", false);
			}
			else if (hundredsNum == 5)
			{
				hundreds->GetAnimator()->Play(L"5", false);
			}
			else if (hundredsNum == 6)
			{
				hundreds->GetAnimator()->Play(L"6", false);
			}
			else if (hundredsNum == 7)
			{
				hundreds->GetAnimator()->Play(L"7", false);
			}
			else if (hundredsNum == 8)
			{
				hundreds->GetAnimator()->Play(L"8", false);
			}
			else if (hundredsNum == 9)
			{
				hundreds->GetAnimator()->Play(L"9", false);
			}

		}

		
		int BombCnt = mPlayer->GetBombNum();

		unitsNum_bomb = BombCnt % 10;
		BombCnt /= 10;

		tensNum_bomb = BombCnt % 10;
		BombCnt /= 10;

		if (unitsNum_bomb == 0)
		{
			units_bomb->GetAnimator()->Play(L"0", false);
		}
		else if (unitsNum_bomb == 1)
		{
			units_bomb->GetAnimator()->Play(L"1", false);
		}
		else if (unitsNum_bomb == 2)
		{
			units_bomb->GetAnimator()->Play(L"2", false);
		}
		else if (unitsNum_bomb == 3)
		{
			units_bomb->GetAnimator()->Play(L"3", false);
		}
		else if (unitsNum_bomb == 4)
		{
			units_bomb->GetAnimator()->Play(L"4", false);
		}
		else if (unitsNum_bomb == 5)
		{
			units_bomb->GetAnimator()->Play(L"5", false);
		}
		else if (unitsNum_bomb == 6)
		{
			units_bomb->GetAnimator()->Play(L"6", false);
		}
		else if (unitsNum_bomb == 7)
		{
			units_bomb->GetAnimator()->Play(L"7", false);
		}
		else if (unitsNum_bomb == 8)
		{
			units_bomb->GetAnimator()->Play(L"8", false);
		}
		else if (unitsNum_bomb == 9)
		{
			units_bomb->GetAnimator()->Play(L"9", false);
		}


		if (tensNum_bomb == 0)
		{
			tens_bomb->GetAnimator()->Play(L"0", false);
		}
		else if (tensNum_bomb == 1)
		{
			tens_bomb->GetAnimator()->Play(L"1", false);
		}
		else if (tensNum_bomb == 2)
		{
			tens_bomb->GetAnimator()->Play(L"2", false);
		}
		else if (tensNum_bomb == 3)
		{
			tens_bomb->GetAnimator()->Play(L"3", false);
		}
		else if (tensNum_bomb == 4)
		{
			tens_bomb->GetAnimator()->Play(L"4", false);
		}
		else if (tensNum_bomb == 5)
		{
			tens_bomb->GetAnimator()->Play(L"5", false);
		}
		else if (tensNum_bomb == 6)
		{
			tens_bomb->GetAnimator()->Play(L"6", false);
		}
		else if (tensNum_bomb == 7)
		{
			tens_bomb->GetAnimator()->Play(L"7", false);
		}
		else if (tensNum_bomb == 8)
		{
			tens_bomb->GetAnimator()->Play(L"8", false);
		}
		else if (tensNum_bomb == 9)
		{
			tens_bomb->GetAnimator()->Play(L"9", false);
		}


		GameObject::Update();
	}
	void ArmsUI::Render(HDC mHdc)
	{

		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();

		TransparentBlt(mHdc, mPos.x, mPos.y, armsImage->GetWidth()*3, armsImage->GetHeight() * 3, armsImage->GetHdc(), 0,0, armsImage->GetWidth(), armsImage->GetHeight(), RGB(153, 217, 234));
		TransparentBlt(mHdc, mPos.x + 120.0f, mPos.y, bombImage->GetWidth() * 3, bombImage->GetHeight() * 3, bombImage->GetHdc(), 0, 0, bombImage->GetWidth(), bombImage->GetHeight(), RGB(153, 217, 234));

		 
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(180, 155, 155));

		HPEN oldPen = (HPEN)SelectObject(mHdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush);
		Rectangle(mHdc, mPos.x - 10.0f, mPos.y- 10.0f, mPos.x + 240.0f, mPos.y + 70.0f);

		(HPEN)SelectObject(mHdc, oldPen);
		(HBRUSH)SelectObject(mHdc, oldBrush);
		DeleteObject(pen);
		
		GameObject::Render(mHdc);
	}
}