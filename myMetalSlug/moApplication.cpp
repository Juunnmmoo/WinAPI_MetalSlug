#include "moApplication.h"
#include "moSceneManager.h"
#include "moTime.h"
#include "moInput.h"

namespace mo {
	Application::Application()
		: mHdc(NULL)
		, mHwnd(NULL)
	{
	}
	Application::~Application()
	{
	}
	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

		Input::Initialize();
		Time::Initizlize();
		SceneManager::Initialize();
	}
	void Application::Run()
	{
		Update();
		Render();
	}
	void Application::Update()
	{

		Input::Update();
		Time::Update();
		SceneManager::Update();
		
	}
	void Application::Render()
	{

		Input::Render(mHdc);
		Time::Render(mHdc);
		SceneManager::Render(mHdc);
	}
	
}