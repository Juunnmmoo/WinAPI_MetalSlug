#include "moScene.h"
#include "moCollisionManager.h"
namespace mo {
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::End);

	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	
		for (Layer& layer : mLayers) {
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers) {
			layer.Update();
		}
	}
	void Scene::Destroy()
	{
		std::vector<GameObject*>deleteGameObjects = {};
		
		for (Layer& layer : mLayers) {
			std::vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end() ; ) 
			{
				if ((*iter)->GetState() == GameObject::eState::Death) {
					deleteGameObjects.push_back((*iter));
					//원본에서도 삭제해야함 
					iter = gameObjects.erase(iter);
				}
				else {
					iter++;
				}
			}

		}

		for (GameObject* obj : deleteGameObjects) {
			delete obj;
			obj = nullptr;
		}

	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* obj, eLayerType layerType)
	{
		obj->SetLayerType(layerType);
		mLayers[(UINT)layerType].AddGameObject(obj);
	}
	std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}
}