#pragma once
#include "moGameObject.h"

namespace mo {
	class Scene;
	class Marco;
	class Boss1_Towrd;
	class AbulAbbas;
	class ArabianFighter;
	class Boss1_Base : public GameObject
	{
	public:

		Boss1_Base(Marco* marco, Scene* scene, Boss1_Towrd* LeftTowrd, Boss1_Towrd* MiddleTowrd, Boss1_Towrd* RightTowrd, ArabianFighter* figther);
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
		class ArabianFighter* fighter3;
		AbulAbbas* abul;
		class Sound* deathSound;
		bool startEndEvent;
		Marco* mPlayer;
		Scene* curScene;
		float mTime;
		int charNum = 0;
	};
}

