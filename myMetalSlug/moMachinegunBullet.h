#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Marco;
	class MachinegunBullet : public GameObject
	{
	public:
		MachinegunBullet(Marco* marco);
		~MachinegunBullet();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		void SetDirection(eDirection direction, int num) {
			mDirection = direction;
			animationNum = num;
		}
		void SetDir(Vector2 dir);
		void PlayAnimation();
		void SetTime(float t) { mTime = t; }

	private:
		float mTime;
		Image* mImage;
		eDirection mDirection;
		Vector2 mDir;
		Marco* mPlayer;
		class Animator* mAnimator;
		int animationNum;
		bool isPlayed;
		float time;
	};
}
