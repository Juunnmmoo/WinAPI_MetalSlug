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

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		template<typename T>
		T* AddComponent() {
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}
		template<typename T>
		void DeleteComponent() {
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			delete mComponents[compType];
			mComponents[compType] = nullptr;

			delete comp;
			comp = nullptr;
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

		eLayerType GetLayerType() { return mLayerType; }
		void SetLayerType(eLayerType type) { mLayerType = type; }

		bool GetIsCrash() { return isCrash; }
		void SetIsCrash(bool b) { isCrash = b; }

		void SetBulletType(eBulletType type) { mBulletType = type; };
		eBulletType GetBulletType() { return mBulletType; }

	private:

		std::vector<Component*> mComponents;
		eState mState;
		eLayerType mLayerType;
		bool isCrash;

		eBulletType mBulletType;
	};
}
