
#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class CamelArabianCreator : public GameObject
	{
	public:

		CamelArabianCreator(Marco* marco);
		~CamelArabianCreator();

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
	};
}
