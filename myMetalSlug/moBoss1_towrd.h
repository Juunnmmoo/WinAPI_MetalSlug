#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class Scene;
	class Boss1_Towrd : public GameObject
	{
	public:
		enum class TowrdDir {
			Left,
			Middle,
			Right,
		};
		enum class TowrdState {
			Nomal,
			Open,
			Destroyed,
		};

		enum class eTowrdFSM {
			Up,
			DoorOpen,
			CurtainOpen,
			Attack,
			Destroyed,
			None
		};

		Boss1_Towrd(Marco* marco, Scene* scene, TowrdDir dir);
		~Boss1_Towrd();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		eTowrdFSM GetTowrdFsm() { return mFsmState; }
		void SetTowrdFsm(eTowrdFSM fsm) { mFsmState = fsm; }

	private:
		void up();
		void dooropen();
		void curtainopen();
		void attack();
		void destroyed();



	private:
		class Image* mTowrdImage;
		class Image* mTowrdOpenImage;
		class Image* mTowrdDestroyedImage;
		class Boss1_CurtainIdle* mCurtainIdle;
		class Boss1_WindowOpen* mDoor;
		class Boss1_CurtainOpen* mCurtainOpen;
		class Boss1_Attackor* mAttackor;
		class Sound* attackSound;
		float mTime;
		bool isPlayed;
		bool useSfx;
		Marco* mPlayer;
		Scene* curScene;
		TowrdDir mTowrdDir;
		TowrdState mTowrdState;
		eTowrdFSM mFsmState;
	};
}
