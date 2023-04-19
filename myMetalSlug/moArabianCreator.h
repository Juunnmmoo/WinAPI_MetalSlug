
#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class ArabianCreator : public GameObject
	{
	public:

		ArabianCreator(Marco* marco,Vector2 pos, Vector2 size, Vector2 create);
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
		Vector2 createVector;
		Vector2 mPos;
		Vector2 mSize;
	};
}
