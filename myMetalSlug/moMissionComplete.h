
#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Animator;
	class Scene;
	class MissionComplete : public GameObject
	{
	public:

		MissionComplete(eSceneType type);
		~MissionComplete();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		float mTime;
		int charNum;
		Scene* curScene;
	};
}
