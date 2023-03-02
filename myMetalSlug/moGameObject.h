#pragma once
#include "moEntity.h"
#include "moComponent.h"

namespace mo {
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC mHdc);

		template<typename T>
		T* AddComponent() {
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template<typename T>
		T* GetComponent() {

			for (Component* comp : mComponents) {
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);

			}
			return nullptr;
		}


	private:

		std::vector<Component*> mComponents;

	};
}
