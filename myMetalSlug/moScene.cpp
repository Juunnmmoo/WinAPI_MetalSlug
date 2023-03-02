#include "moScene.h"

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
	void Scene::Render(HDC mHdc)
	{
		for (Layer& layer : mLayers) {
			layer.Render(mHdc);
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
}