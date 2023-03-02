#pragma once
#include "moEntity.h"

namespace mo {
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetName() { return mName; }
		const std::wstring& GetPath() { return mPath; }
		void SetName(const std::wstring& name) { mName = name; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mName;
		std::wstring mPath;
	};
}
