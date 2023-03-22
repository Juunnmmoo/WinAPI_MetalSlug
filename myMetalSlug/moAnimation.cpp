#include "moAnimation.h"
#include "moImage.h"
#include "moTime.h"
#include "moTransform.h"
#include "moAnimator.h"
#include "moGameObject.h"
#include "moCamera.h"

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
	void Animation::Render(HDC mHdc, bool isAlpha,int alpha)
	{

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		Vector2 disToBottom = tr->GetDisToBottom();

		Vector2 pos = tr->GetPos();

		// 카메라 좌표로 설정
		pos = Camera::CaluatePos(pos);
		
		pos += mSpriteSheet[mSpriteIndex].offSet;
		pos.x -= (mSpriteSheet[mSpriteIndex].size.x * scale.x) / 2;
		pos.y -= (mSpriteSheet[mSpriteIndex].size.x * scale.y);

		// 메인 캐릭터 sprite는 바닥부터 상체값을 없애고 출력해야하기 때문에

		pos.y += disToBottom.y * scale.y;
		if (isAlpha == false) {
			TransparentBlt(mHdc, pos.x, pos.y
				, mSpriteSheet[mSpriteIndex].size.x * scale.x
				, mSpriteSheet[mSpriteIndex].size.y * scale.y
				, mSheetImage->GetHdc()
				, mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
				, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
				, RGB(153, 217, 234));
		}
		else {

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = alpha; // 0(투명) ~ 255(불투명) 알파값

			AlphaBlend(mHdc, pos.x, pos.y
				, mSpriteSheet[mSpriteIndex].size.x * scale.x
				, mSpriteSheet[mSpriteIndex].size.y * scale.y
				, mSheetImage->GetHdc()
				, mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
				, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
				, func);
		
		}

	}
	void Animation::Create(Image* sheet, Vector2 leftTop, float next, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration)
	{
		mSheetImage = sheet;

		Vector2 size = Vector2::One; 
		size.x = mSheetImage->GetWidth() / (float)coulmn;
		size.y = mSheetImage->GetHeight() / (float)row;
			 
		for (size_t i = 0; i < spriteLength; i++) {
			Sprite sprite;
			sprite.leftTop.x = leftTop.x + (next * i);
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