
#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class Sound;
	class Boss2Creator : public GameObject
	{
	public:

		Boss2Creator(Marco* marco, Sound* sound);
		~Boss2Creator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		float time;
		Marco* player;
		Sound* activeSound;
		Sound* BossBGM;
		bool stopCreate;
		bool isFighterFoword;
	};
}
