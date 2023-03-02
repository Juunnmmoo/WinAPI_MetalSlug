#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco : public GameObject
	{
	public:

		Marco();
		~Marco();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:

	};
}
