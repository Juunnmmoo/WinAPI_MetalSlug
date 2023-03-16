#pragma once
#include "moEntity.h"

namespace mo {
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		void SetKey(const std::wstring& name) { mKey = name; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::wstring mPath;
	};
}
