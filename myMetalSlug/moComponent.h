#pragma once
#include "moEntity.h"

namespace mo {
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC mHdc);

		eComponentType GetType() { return mType; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }
	
	private:

		const eComponentType mType;
		GameObject* mOwner;
		eLayerType mLayerType;
	};
}

