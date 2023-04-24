#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class SelectElevator : public GameObject
	{
	public:

		SelectElevator(Vector2 pos, float f);
		virtual ~SelectElevator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;
		void SetGoingBack();
		

	private:
		Image* mImage;
		Vector2 mPos;
		float aWaitTime;
		float time;
		bool stopMove;
		bool goingBack;
		class PlayerIdle* top;
		class PlayerIdleBottom* bottom;
	};
}