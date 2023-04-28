#pragma once
#include "moGameObject.h"

namespace mo {
	class Scene;
	class Marco;
	class Boss1_Base : public GameObject
	{
	public:

		Boss1_Base(Marco* marco, Scene* scene);
		~Boss1_Base();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void EndEvent();

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		class Image* image;
		class Image* destroyImage;
		class Boss1_Towrd* mLeftTowrd;
		class Boss1_Towrd* mMiddleTowrd;
		class Boss1_Towrd* mRightTowrd;
		class AbulAbbas* abul;
		class ArabianFighter* fighter1;
		class ArabianFighter* fighter12;
		class ArabianFighter* fighter3;
		bool startEndEvent;
		Marco* mPlayer;
		Scene* curScene;
		float mTime;
		int charNum = 0;
	};
}

