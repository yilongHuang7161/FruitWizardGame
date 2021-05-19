#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class PlayerCharacter : public SimObject {
		enum class PlayerState;
	public:
		PlayerCharacter();
		~PlayerCharacter();

		PlayerState GetCurrentAnimState();

		bool UpdateObject(float dt) override;

		bool isFall;
		bool isClimb;
		float activeIn;
	protected:
		enum class PlayerState {
			Left,
			Right,
			Attack,
			Fall,
			Die,
			Idle,
			Climb
		};
		PlayerState		currentAnimState;
	};
}