#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Marco;
	class Boss1_Missile : public GameObject
	{
	public:
		enum class eBoss1MisileState {
			Start,
			RotateDown,
			MoveDown,
			UnderStandard,
			MoveUp,
			RotateToBottom,
			RotateLeft,
		};
		Boss1_Missile(Marco* marco);
		~Boss1_Missile();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		void PlayAnimation(eDirection direction);

	private:
		void start(); 
		void rotateDown(); 
		void moveDown();
		void underStandard(); 
		void up(); 
		void moveUp();
		void rotateToBottom();
		void rotateLeft(); 

	private:
		eBoss1MisileState mState;
		Image* mImage;
		Marco* mPlayer;
		class Animator* mAnimator;
		eDirection mDir;
		bool isUsed;
		float mTime;
		bool isPlayed;
		Vector2 dir;
	};
}
