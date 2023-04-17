
#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class ArabianCreator : public GameObject
	{
	public:

		ArabianCreator(Marco* marco);
		~ArabianCreator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		float time;
		bool startCreate;
		Marco* player;
	};
}
