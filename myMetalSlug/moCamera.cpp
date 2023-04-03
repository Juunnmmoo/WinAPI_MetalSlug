#include "moCamera.h"
#include "moApplication.h"
#include "moGameObject.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moImage.h"
#include "moTransform.h"


extern mo::Application application;

namespace mo{
	
	Vector2 Camera::mReslution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	Camera::eCameraEffectType Camera::mType = Camera::eCameraEffectType::None;
	class Image* Camera::mCutton = nullptr;
	float Camera::mCuttonAlpha = 1.0f;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 3.0f;
	bool Camera::isMove = false;

	void Camera::Initialize()
	{
		mReslution.x = application.GetWidth();
		mReslution.y = application.GetHeight();
		mLookPosition = mReslution / 2.0f;

		mType = eCameraEffectType::FadeIn;
		mCutton = Image::Create(L"Cutton", mReslution.x, mReslution.y, RGB(0, 0, 0));
	
	}

	void Camera::Update()
	{
		
		Transform* tr = mTarget->GetComponent<Transform>();
		Vector2 mTargetPos = tr->GetPos();

		/*if (Input::GetKey(eKeyCode::I))
			mLookPosition.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::L))
			mLookPosition.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::J))
			mLookPosition.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::K))
			mLookPosition.y += 100.0f * Time::DeltaTime();*/


		if (mTarget != nullptr) {
				
			if (mTargetPos.x >= mLookPosition.x - 120.0f)
			{
				isMove = true;
				if(Input::GetKey(eKeyCode::Right))
					mLookPosition.x += 300.0f * Time::DeltaTime();
			
			}
			else {
				isMove = false;
			}
			//mLookPosition = mTarget->GetComponent<Transform>()->GetPos();
		}
		


		if (mAlphaTime < mEndTime) {
			mAlphaTime += Time::DeltaTime();
			// ratio가 점점 1에 가까워짐.
			float ratio = (mAlphaTime / mEndTime);
			
			if (mType == eCameraEffectType::FadeIn)
				mCuttonAlpha = 1.0f - ratio;

			else if (mType == eCameraEffectType::FadeOut)
				mCuttonAlpha = ratio;

			else{}

		}


		//무조건 LookPosition이 가운대로오개끔
		mDistance = mLookPosition - (mReslution / 2.0f);

	}

	void Camera::Render(HDC mHdc)
	{
		if (mAlphaTime < mEndTime
			&& mType == eCameraEffectType::FadeIn) 
		{
			if (mAlphaTime < mEndTime
				&& mType == eCameraEffectType::FadeIn)
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = 0;
				func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

				AlphaBlend(mHdc, 0, 0
					, mReslution.x, mReslution.y
					, mCutton->GetHdc()
					, 0, 0
					, mCutton->GetWidth(), mCutton->GetHeight()
					, func);
			}

		}
	}

	void Camera::Clear() {
		
		mReslution.x = application.GetWidth();
		mReslution.y = application.GetHeight();

		mLookPosition = (mReslution / 2.0f);
		mDistance = Vector2::Zero;

	}

	void Camera::RestartFadeIn()
	{
		Camera::mCuttonAlpha = 1.0f;
		Camera::mAlphaTime = 0.0f;
	}

}