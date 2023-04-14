#pragma once
class OutSideWallT
{
};


#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class OutSideWallT : public GameObject
	{
	public:

		OutSideWallT();
		~OutSideWallT();

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
