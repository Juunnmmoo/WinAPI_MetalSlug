#pragma once
#include "moComponent.h"
#include "moAnimation.h"

namespace mo {
	class Animator : public Component
	{
	public:
		
		struct Event {
			void operator=(std::function<void()> func) {
				mEvent = std::move(func);
			}
			void operator()() {
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};

		struct Events {
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};


		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, float next
			, UINT coulmn, UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		void CreateAnimations();

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);


		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		Animation* GetActiveAnimation() { return mActiveAnimation; };
		Animation* GetPrevAniamtion() { return mPrevAnimation; };

		void SetAlpha(bool b) { isAlpha = b; }

		void SetUseinvincibility(bool b) { Useinvincibility = b; }
		bool GetUseinvincibility() {return Useinvincibility;}
		bool IsComplte() { return mActiveAnimation->isComplete(); }

		void SetunUseCameraPos(bool b) { unUseCameraPos = b; }
		void SetUnUseCameraY(bool b) { unUseCameraY = b; }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map < std::wstring, Events* > mEvents;
		Animation* mActiveAnimation;
		Animation* mPrevAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
		bool isAlpha;
		bool Useinvincibility;
		int alpha;
		float mTime;
		int TimeCheck;
		bool unUseCameraPos;
		bool unUseCameraY;
	};
}
