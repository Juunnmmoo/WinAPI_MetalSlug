#include "moRigidBody.h"
#include "moTime.h"
#include "moTransform.h"
#include "moGameObject.h"
#include "moMath.h"

namespace mo {
	RigidBody::RigidBody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1500.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 1500.0f);
		mFriction = 100.0f;
	}
	RigidBody::~RigidBody()
	{
	}
	void RigidBody::Initialize()
	{
	}
	void RigidBody::Update()
	{
		mAccelation = mForce / mMass;

		mVelocity += mAccelation * Time::DeltaTime();


		if (mbGround) {
			
			Vector2 gravity = mGravity;
			gravity.Normalize();
			
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;	
		}
		else {
		
			mVelocity += mGravity * Time::DeltaTime();
		}

		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		pos = pos + mVelocity * Time::DeltaTime();

		if (pos.y >= 700.0f) {
			mbGround = true;
		}
		tr->SetPos(pos);
		mForce.Clear();
	
	}
	void RigidBody::Render(HDC mHdc)
	{
	}
	void RigidBody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}