#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Animator;
	class Scene;
	class MissionStart : public GameObject
	{
	public:

		MissionStart(eSceneType type);
		~MissionStart();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		float mTime;
		int charNum;
		Scene* curScene;
	};
}
