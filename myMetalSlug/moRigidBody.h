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

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
	};
}
