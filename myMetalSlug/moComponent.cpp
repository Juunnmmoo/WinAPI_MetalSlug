#include "moComponent.h"

namespace mo {
	Component::Component(eComponentType type)
		: mType(type)
	{
	}
	Component::~Component()
	{
		
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::Render(HDC mHdc)
	{
	}
}