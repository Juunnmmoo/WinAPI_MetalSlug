#pragma once
#include "CommonInclude.h"

namespace mo {
	class Time
	{
	public:

		Time();
		~Time();

		static void Initizlize();
		static void Update();
		static void Render(HDC mHdc);
		
		__forceinline static double DeltaTime() { return mDeltaTime; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

	};
}
