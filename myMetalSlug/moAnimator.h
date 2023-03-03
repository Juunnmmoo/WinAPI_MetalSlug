#pragma once
#include "moComponent.h"
#include "moAnimation.h"

namespace mo {
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn, UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		void CreateAnimations();

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		Animation* mPrevAnimation;
		Image* mSpriteSheet;
		bool mbLoop;

	};
}
