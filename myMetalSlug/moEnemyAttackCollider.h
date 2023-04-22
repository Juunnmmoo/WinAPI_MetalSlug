	
#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class EnemyAttackCollider : public GameObject
	{
	public:

		EnemyAttackCollider( Vector2 pos, Vector2 leftTop, Vector2 size, float stop);
		~EnemyAttackCollider();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		Vector2 mPos;
		Vector2 mLeftTop;
		Vector2 mSize;
		float mTime;
		float stopTime;
	};
}
