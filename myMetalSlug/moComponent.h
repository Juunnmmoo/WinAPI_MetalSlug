#pragma once
#include "moEntity.h"

namespace mo {
	class Component : public Entity
	{
	public:
		Component();
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC mHdc);
	private:

	};
}

