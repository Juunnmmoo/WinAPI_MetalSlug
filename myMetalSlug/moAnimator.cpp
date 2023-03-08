#include "moAnimator.h"

namespace mo {
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
		, mPrevAnimation(nullptr)
	{
	}
	Animator::~Animator()
	{
		for (auto animation : mAnimations)
		{
			delete animation.second;
			animation.second = nullptr;
		}

		for (auto events : mEvents) {
			delete events.second;
			events.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();
		
			if (mbLoop && mActiveAnimation->isComplete())
			{
				Animator::Events* events = FindEvents(mActiveAnimation->GetName());
				if (events != nullptr)
					events->mCompleteEvent();

				mActiveAnimation->Reset();
			}
		}
		
	}
	void Animator::Render(HDC mHdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(mHdc);
		}
	}
	void Animator::CreateAnimation(const std::wstring& name, Image* sheet, Vector2 leftTop, float next, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration)
	{
		Animation* animation = FindAnimation(name);

		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(sheet, leftTop, next, coulmn, row, spriteLength, offset, duration);
		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
		
		Events* event = new Events();
		mEvents.insert(std::make_pair(name, event));
	}
	void Animator::CreateAnimations()
	{
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::Play(const std::wstring& name, bool loop)
	{
		if (mActiveAnimation != nullptr) {
			
			Animator::Events* prevEvents = FindEvents(mActiveAnimation->GetName());

			if(prevEvents != nullptr)
				prevEvents->mEndEvent();
		}

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		Animator::Events* events = FindEvents(mActiveAnimation->GetName());
		events->mStartEvent();

	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map < std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Events* events= FindEvents(animation->GetName());

		return events->mStartEvent.mEvent;

		// TODO: 여기에 return 문을 삽입합니다.
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{

		Animation* animation = FindAnimation(name);

		Events* events = FindEvents(animation->GetName());

		return events->mCompleteEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Events* events = FindEvents(animation->GetName());

		return events->mEndEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}
}