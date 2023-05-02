#pragma once
#include "moGameObject.h"

namespace mo {
	class Animator;
	class Boss2LaserCollider : public GameObject
	{
	public:

		Boss2LaserCollider(eDirection dir);
		~Boss2LaserCollider();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		eDirection mDirection;
	};
}