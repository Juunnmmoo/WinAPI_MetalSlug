#pragma once
#include "moGameObject.h"

namespace mo {
	class Scene;
	class Marco;
	class Boss2_Door;
	class Boss2_Weapon;
	class Boss2_Propeller;
	class Boss2LaserCollider;
	class ArmyRoket;
	class Boss2_Base : public GameObject
	{
	public:

		Boss2_Base(Marco* marco, Scene* scene, Boss2_Door* door, Boss2_Weapon* energy, Boss2_Propeller* propeller, Boss2LaserCollider* left, Boss2LaserCollider* right
		, ArmyRoket* leftRoket, ArmyRoket* rightRokey);
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
		class Sound* downSound;
		Boss2LaserCollider* mLeft;
		Boss2LaserCollider* mRight;
		Boss2_Door* mDoor;
		Boss2_Weapon* mWeapon;
		Boss2_Propeller* mPropeller;
		ArmyRoket* mLeftRoket;
		ArmyRoket* mRightRoket;
		bool startEndEvent;
		eBoss2FSM mState;
		Marco* mPlayer;
		Scene* curScene;
		class Sound* missionComplete;
		class Sound* BossBGM;
		float mTime;
		int charNum = 0;
		bool isOpened;
		bool gotoDeath;
		bool outArmyOnce;
		int heart;
	};
}

