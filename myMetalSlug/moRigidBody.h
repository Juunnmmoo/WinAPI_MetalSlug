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
		bool GetGround() { return mbGround; }

		void SetFall(bool b) { mbFall = b; }
		bool GetFall() { return mbFall; }

		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }

		void SetGravity(Vector2 gravity) { mGravity = gravity; }


	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;


		Vector2 mGravity;
		float mFriction;
		bool mbGround;
		bool mbFall;
	};
}
