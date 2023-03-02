#pragma once
#include "moScene.h"

namespace mo
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC mHdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:

	};
}