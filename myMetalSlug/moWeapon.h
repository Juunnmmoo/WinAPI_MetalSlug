#pragma once
#include "moMarco.h"

namespace mo {
	class Weapon : public Entity
	{
	public:

		Weapon();
		virtual~Weapon();

		
		void SetPlayer( Marco* marco) { mPlayer = marco; }
		Marco* GetPlayer() { return mPlayer; }

		void SetBottom(MarcoBottom* bottom) { mBottom = bottom; }
		MarcoBottom* GetBottom() { return mBottom; }

	private:
		Marco* mPlayer;
		MarcoBottom* mBottom;
	};
	
}
