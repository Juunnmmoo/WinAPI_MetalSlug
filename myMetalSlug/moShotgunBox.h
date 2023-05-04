
#pragma once
#include "moGameObject.h"

namespace mo {
	class ShotgunBox : public GameObject
	{
	public:

		ShotgunBox();
		~ShotgunBox();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		class Image* mImage;
		class Sound* machinegunSound;
		float mTime;
	};
}
