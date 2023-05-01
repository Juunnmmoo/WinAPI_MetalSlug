
#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class PlayerBomb : public GameObject
	{
	public:
		enum class eWeaponObjectState {
			First,
			Second,
			End,
		};
		PlayerBomb();
		~PlayerBomb();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		void PlayAnimation(eDirection direction);

	private:
		void first();
		void second();
		void end();


	private:
		eWeaponObjectState mState;
		Image* mImage;
		class Animator* mAnimator;
		eDirection mDir;
		bool isUsed;
		class Sound* bombSound;
	};
}
