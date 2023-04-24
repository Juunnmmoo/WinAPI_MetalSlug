#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Animator;
	class CharUI : public GameObject
	{
	public:
		enum class eUiType {
			StartUi,
			BulletNumUi,
			TimeUi,
			GoUi,
			None,
		};
		CharUI(eCharType type, Vector2 pos, Vector2 scale);
		~CharUI();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void PlayStartAnimation(float stop, Vector2 dir) {
			mState = eUiType::StartUi;
			stopTime = stop;
			mDir = dir;
			mDir.Normalize();
		}

		void ChangeAnimation(eCharType type);
		Animator* GetAnimator() { return mAnimator; }

	private:
		void startUi();
		void bulletNumUi();
		void timeUi();
		void goUi();

	private:
		Animator* mAnimator;
		Vector2 mPos;
		Vector2 mScale;
		eCharType mType;
		eUiType mState;
		Vector2 mDir;
		float mTime;
		float stopTime;
		bool isChanged;

	};
}
