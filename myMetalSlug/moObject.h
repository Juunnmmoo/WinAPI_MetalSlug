#pragma once
#include "moGameObject.h"
#include "moScene.h"
#include "moSceneManager.h"
#include "moTransform.h"


namespace mo::object {

	/*template <typename T>
	static inline T* Instantiate(eLayerType type) {
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type) {
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		return gameObj;
	}*/


	static void Destory(GameObject* obj) {
		if (obj != nullptr)
		{
			obj->SetState(GameObject::eState::Death);
		}
	}


}