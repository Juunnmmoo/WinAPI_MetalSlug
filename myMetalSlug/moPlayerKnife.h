#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class PlayerKnife : public GameObject
	{
	public:

		PlayerKnife();
		~PlayerKnife();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		bool GetIsCollide() { return isCollide; }
		void SetIsUse(bool b) { isUse = b; }
		void SetPos(Vector2 pos);

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		Marco* player;
		Vector2 mPos;
		class Sound* knifeAttackSound;
		bool isCollide;
		bool isUse;
	};
}
