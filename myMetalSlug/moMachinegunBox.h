#pragma once
#include "moGameObject.h"

namespace mo {
	class MachinegunBox : public GameObject
	{
	public:

		MachinegunBox();
		~MachinegunBox();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		void SetPlayer(class Marco* marco) { mPlayer = marco; }

	private:
		class Image* main;
		class Image* ground;
		class Marco* mPlayer;
		UINT TopDiff;
	};
}
