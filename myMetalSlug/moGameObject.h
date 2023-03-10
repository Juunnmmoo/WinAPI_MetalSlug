#pragma once
#include "moEntity.h"
#include "moComponent.h"

namespace mo {
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Death,
		};
		
		GameObject();
		virtual ~GameObject();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC mHdc);

		virtual void OnCollisionEnter(class Collider* other, eLayerType otherType);
		virtual void OnCollisionStay(class Collider* other, eLayerType otherType);
		virtual void OnCollisionExit(class Collider* other, eLayerType otherType);

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

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }

	private:

		std::vector<Component*> mComponents;
		eState mState;
	};
}
