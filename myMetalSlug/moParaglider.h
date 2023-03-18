#pragma once
#include "moGameObject.h"


namespace mo {
	class Animator;
	class Marco;
	class Image;
	class Paraglider : public GameObject
	{
	public:
		enum class eState{
			use,
			notUse,
		};

		Paraglider(Marco* owner);
		~Paraglider();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		void use();
		void notUse();

	private:
		Image* mImage;
		eState mState;
		Marco* mOwner;
		Animator* mAnimator;
	};
}
