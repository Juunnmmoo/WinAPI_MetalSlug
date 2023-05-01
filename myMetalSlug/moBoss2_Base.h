#pragma once
#include "moGameObject.h"

namespace mo {
	class Scene;
	class Marco;
	class Boss2_Door;
	class Boss2_Weapon;
	class Boss2_Propeller;
	class Boss2_Base : public GameObject
	{
	public:

		Boss2_Base(Marco* marco, Scene* scene, Boss2_Door* door, Boss2_Weapon* energy, Boss2_Propeller* propeller);
		~Boss2_Base();

		enum class eBoss2FSM {
			None,
			Down,
			DropArabian,
			DropArmy,
			BeforeAttack,
			Attack,
			AfterAttack,
			Death,
		};

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void EndEvent();

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;


	private:
		void none(); 
		void down(); 
		void dropArabian(); 
		void dropArmy(); 
		void beforeAttack(); 
		void attack();
		void afterAttack(); 
		void death();

	private:
		class Image* image;
		class Image* destroyImage;
		class AbulAbbas* abul;
		class Sound* deathSound;
		class Animator* mAnimator;
		Boss2_Door* mDoor;
		Boss2_Weapon* mWeapon;
		Boss2_Propeller* mPropeller;
		bool startEndEvent;
		eBoss2FSM mState;
		Marco* mPlayer;
		Scene* curScene;
		float mTime;
		int charNum = 0;
	};
}

