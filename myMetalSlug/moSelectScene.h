#pragma once
#include "moScene.h"

namespace mo
{
	class Sound;
	class SelectElevator;
	class SelectCharactor;
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		~SelectScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC mHdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		SelectCharactor* charactor1;
		SelectCharactor* charactor2;
		SelectCharactor* charactor3;
		SelectCharactor* charactor4;
		SelectElevator* elevator1;
		SelectElevator* elevator2;
		SelectElevator* elevator3;
		SelectElevator* elevator4;
		Sound* selectBGM;
		int selectNum;
		bool SceneChange;
		float time;
	};
}


