#include "moScene.h"

namespace mo {
	Scene::Scene()
	{
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
}