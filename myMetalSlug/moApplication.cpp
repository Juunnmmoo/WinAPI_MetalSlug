#include "moApplication.h"
#include "moSceneManager.h"
#include "moTime.h"
#include "moInput.h"
#include "moCollisionManager.h"
#include "moCamera.h"

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

		mWidth = 1500;
		mHeight = 750;

		// ���ϴ�ũ��� RECT����� rect ������ ����â�� ũ�⸦ ������?
		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ������ ũ�� ����� ��¼���
		SetWindowPos(mHwnd
			, nullptr, 10, 10
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);


		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(defaultBitmap);


		Input::Initialize();
		Time::Initizlize();
		Camera::Initialize();
		SceneManager::Initialize();
		
	}
	void Application::Run()
	{
		Update();
		Render();
		SceneManager::Destroy();
	}
	void Application::Update()
	{

		Input::Update();
		Time::Update();
		Camera::Update();

		SceneManager::Update();
		CollisionManager::Update();
		
		
	}
	void Application::Render()
	{
		clear();

		Input::Render(mBackHdc);
		Time::Render(mBackHdc);
		SceneManager::Render(mBackHdc);
		Camera::Render(mBackHdc);

		// ����ۿ� �ִ� �׸��� �������ۿ� �׷�����Ѵ�.
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}

	void Application::clear()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);
		Rectangle(mBackHdc, -1, -1, 1501, 751);
		SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}
	
}