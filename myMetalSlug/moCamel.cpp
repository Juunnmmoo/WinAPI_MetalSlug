#include "moCamel.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moScene.h"
#include "moObject.h"
#include "moArabianWeapon.h"
#include "moMarco.h"
#include "moScene.h"
#include "moRigidBody.h"
#include "moEnemyAttackCollider.h"
#include "moCamera.h"
#include "moApplication.h"

namespace mo {
	Camel::Camel()
	{
	}
	Camel::~Camel()
	{
	}
	void Camel::Initialize()
	{
		GameObject::Initialize();
	}
	void Camel::Update()
	{
		GameObject::Update();
	}
	void Camel::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
}