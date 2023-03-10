#pragma once
#include "momoEngine.h"


namespace mo{
	class GameObject;
	class Camera
	{
	public:

		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Vector2 CaluatePos(Vector2 pos) { return pos - mDistance; }

		static void Clear();
	private:

		static Vector2 mReslution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

	};
}
