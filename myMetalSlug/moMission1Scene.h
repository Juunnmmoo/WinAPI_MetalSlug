#pragma once
#include "moScene.h"

namespace mo
{
	class Sound;
	class Mission1Scene : public Scene
	{
	public:
		Mission1Scene();
		~Mission1Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC mHdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		Sound* mission1BGM;
		Sound* missionStart;
	};
}