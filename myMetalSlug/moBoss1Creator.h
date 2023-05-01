#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class Boss1Creator : public GameObject
	{
	public:

		Boss1Creator(Marco* marco);
		~Boss1Creator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		float time;
		Marco* player;
		bool stopCreate;
		bool isFighterFoword;
	};
}
