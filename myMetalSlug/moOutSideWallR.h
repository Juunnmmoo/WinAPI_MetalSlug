#pragma once
class OutSideWallR
{
};


#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class OutSideWallR : public GameObject
	{
	public:

		OutSideWallR();
		~OutSideWallR();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		float time;
		bool stopCreate;
		Marco* player;
	};
}
