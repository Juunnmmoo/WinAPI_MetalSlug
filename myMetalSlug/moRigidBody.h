#pragma once
#include "moComponent.h"

namespace mo {
	class RigidBody : public Component
	{
	public:

		RigidBody();
		~RigidBody();
		void Initialize() override;
		void Update() override;
		void Render(HDC mHdc) override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);

		void SetGround(bool b) { mbGround = b; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }


	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;


		Vector2 mGravity;
		float mFriction;
		bool mbGround;
	};
}
