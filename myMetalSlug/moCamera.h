#pragma once
#include "momoEngine.h"


namespace mo{
	class GameObject;
	class Camera
	{
	public:
		enum eCameraEffectType 
		{
			None,
			FadeIn,
			FadeOut,
			End,
		};


		static void Initialize();
		static void Update();
		static void Render(HDC mHdc);
		static void Clear();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Vector2 CaluatePos(Vector2 pos) { return pos - mDistance; }
		static Vector2 GetDistance() { return mDistance; }


	private:

		static Vector2 mReslution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;


		static eCameraEffectType mType;
		static class Image* mCutton;
		static float mCuttonAlpha;
		static float mAlphaTime;
		static float mEndTime;

	};
}
