#pragma once
#include "moEntity.h"
#include "moGameObject.h"

namespace mo {
	class Layer : public Entity
	{
	public:

		Layer();
		~Layer();

		void Initialize();
		void Update();
		void Render(HWND mHwnd);
		
	private:

		std::vector<GameObject*> mGameObjects;
	};
}
