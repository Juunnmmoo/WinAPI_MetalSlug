
#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class ArabianWeapon : public GameObject
	{
	public:

		ArabianWeapon();
		~ArabianWeapon();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void PlayAnimation(eDirection direction);

	private:
		Image* mImage;
		class Animator* mAnimator;
		eDirection mDir;
		bool isUsed;
	};
}
