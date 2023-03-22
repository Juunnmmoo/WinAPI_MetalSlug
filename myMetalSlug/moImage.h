#pragma once
#include "moResource.h"

namespace mo {
	class Image : public Resource
	{
	public:
		Image();
		~Image();

		static Image* Create(const std::wstring& name, UINT width, UINT height, COLORREF rgb = RGB(255, 255, 255));

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		void SetPixel(int x, int y, COLORREF color);
		COLORREF GetPixel(int x, int y);


	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

