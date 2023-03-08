#pragma once
#include "momoEngine.h"
#include "Collider.h"

namespace mo {
	class Scene;
	class CollisionManager
	{
	public:
		static void Update();
		static void LayerCollision(Scene* scene, eLayerType left, eLayerType right);
		static bool Intersect(Collider* left, Collider* right);
	
		static void SetLayer(eLayerType left, eLayerType right, bool value);
		static void Clear();
	private:
		static WORD mMatrix[(UINT)eLayerType::End];

	};
}
