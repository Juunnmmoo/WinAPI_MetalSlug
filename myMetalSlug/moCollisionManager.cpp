#include "moCollisionManager.h"
#include "moScene.h"
#include "moSceneManager.h"
#include "moAnimator.h"

namespace mo {

	DWORD CollisionManager::mMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)eLayerType::End; row++) {
			for (UINT col = 0; col < (UINT)eLayerType::End; col++) {
				
				if (mMatrix[row] & (1 << col)) {
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (auto leftObject : lefts) {
			Collider* leftCollider = leftObject->GetComponent<Collider>();
			if (leftCollider == nullptr)
				continue;

			for (auto rightObject : rights) {
				Collider* rightCollider = rightObject->GetComponent<Collider>();
				if (rightCollider == nullptr)
					continue;
				if (leftObject == rightObject)
					continue;

				ColliderCollision(leftCollider, rightCollider, left, right);

			}
		}
	}
	
	void CollisionManager::ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right)
	{
		ColliderID colliderID = {};
		colliderID.left = (UINT)leftCol->GetID();
		colliderID.right = (UINT)rightCol->GetID();

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		
		if (iter == mCollisionMap.end()) {
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		if (Intersect(leftCol, rightCol)) {
			if (iter->second == false) {
				leftCol->OnCollisionEnter(rightCol);
				rightCol->OnCollisionEnter(leftCol);

				iter->second = true;
			}
			else {
				leftCol->OnCollisionStay(rightCol);
				rightCol->OnCollisionStay(leftCol);
			}
		
		}
		else {
			if (iter->second == true) {
				leftCol->OnCollisionExit(rightCol );
				rightCol->OnCollisionExit(leftCol );

				iter->second = false;
			}
		}

	}
	
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPos();
		Vector2 rightPos = right->GetPos();

		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();
		
		leftPos.x = leftPos.x + leftSize.x / 2.0f;
		leftPos.y = leftPos.y + leftSize.y / 2.0f;

		rightPos.x = rightPos.x + rightSize.x / 2.0f;
		rightPos.y = rightPos.y + rightSize.y / 2.0f;

		if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f)
			&& left->GetOwner()->GetState() == GameObject::eState::Active
			&& right->GetOwner()->GetState() == GameObject::eState::Active
			) {

			return true;
		}
		else
			return false;
	}
	
	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool value)
	{
		UINT row = 0;
		UINT col = 0;

		UINT ileft = (UINT)left;
		UINT iright = (UINT)right;

		if (ileft <= iright) {
			row = ileft;
			col = iright;
		}
		else{
			row = iright;
			col = ileft;
		}

		if (value)
			mMatrix[row] |= (1 << col);
		else
			mMatrix[row] &= ~(1 << col);

	}

	void CollisionManager::Clear()
	{
		memset(mMatrix, 0, sizeof(DWORD) * (UINT)eLayerType::End);
		mCollisionMap.clear();
	}
}