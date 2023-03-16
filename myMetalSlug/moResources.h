#pragma once
#include "moResource.h"

namespace mo {
	class Resources
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& name) {
			
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(name);
			if (iter != mResources.end())
				return dynamic_cast<T*>(iter->second);
			
				return nullptr;
		}

		template<typename T>
		static T* Load(const std::wstring& name, const std::wstring& path) {

			T* resource = Resources::Find<T>(name);
			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(path))) {
				assert(false);
				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			mResources.insert(std::make_pair(name, resource));
			
			return dynamic_cast<T*>(resource);

		}
		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}


		static void Release() {
			for (auto pair : mResources) {
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource* > mResources;
	};
}

