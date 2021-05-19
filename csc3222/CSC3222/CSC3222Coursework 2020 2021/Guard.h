#pragma once
#include "SimObject.h"
#include <vector>

namespace NCL::CSC3222 {
	class Guard : public SimObject	{
	public:
		Guard();
		~Guard();

		bool UpdateObject(float dt) override;

		void AttackPlayer(float dt);
		void PatrolMap();
	protected:
		int frame = 0;
		int distance;
		float pathTimer = 0;
		bool pathFound = false;
		std::vector<Vector2> path;

		enum class State {
			PATROL,
			ATTACK
		};

		State state;
	};
}