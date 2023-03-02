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
		void Render(HDC mHdc);

		void addGameObject(GameObject* obj) {
			mGameObjects.push_back(obj);
		}
		
	private:

		std::vector<GameObject*> mGameObjects;
	};
}
