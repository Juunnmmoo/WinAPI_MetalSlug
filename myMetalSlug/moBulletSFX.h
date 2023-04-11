#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Animator;
	class BulletSFX : public GameObject
	{
	public:

		BulletSFX( eLayerType layer, Vector2 pos);
		~BulletSFX();

		virtual void Initialize() override;	
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void PlayAnimation();
	private:
		void destroySFX();

	private:
		Animator* mAnimator;
		eLayerType mLayerType;
		Vector2 mPos;
	};
}
