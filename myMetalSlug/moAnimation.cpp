#include "moAnimation.h"
#include "moImage.h"
#include "moTime.h"
#include "moTransform.h"
#include "moAnimator.h"
#include "moGameObject.h"

namespace mo {
	Animation::Animation()
		: mAnimator(nullptr)
		, mSheetImage(nullptr)
		, mTime(0.0f)
		, mbComplete(false)
		, mSpriteIndex(0)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Initialize()
	{

	}
	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime) {

			mTime = 0.0f;
			if (mSpriteSheet.size() <= mSpriteIndex + 1) {
				mbComplete = true;
			}
			else {
				mSpriteIndex++;
			}

		}
	}
	void Animation::Render(HDC mHdc)
	{
		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 scale = tr->GetScale();

		TransparentBlt(mHdc, tr->GetPos().x + mSpriteSheet[mSpriteIndex].offSet.x
			, tr->GetPos().y + mSpriteSheet[mSpriteIndex].offSet.y
			, mSpriteSheet[mSpriteIndex].size.x * scale.x
			, mSpriteSheet[mSpriteIndex].size.y * scale.y
			, mSheetImage->GetHdc()
			, mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
			, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
			RGB(255, 0, 229));
	}
	void Animation::Create(Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration)
	{
		mSheetImage = sheet;

		Vector2 size = Vector2::One; 
		size.x = mSheetImage->GetWidth() / (float)coulmn;
		size.y = mSheetImage->GetHeight() / (float)row;
			 
		for (size_t i = 0; i < spriteLength; i++) {
			Sprite sprite;
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.offSet = offset;
			sprite.size = size;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}

	}
	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mbComplete = false;
		mTime = 0.0f;
	}
}