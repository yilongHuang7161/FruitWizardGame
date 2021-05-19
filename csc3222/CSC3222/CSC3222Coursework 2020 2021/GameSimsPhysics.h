#pragma once
#include <vector>
#include "Math.h"
#include "CollisionVolume.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3222 {
		class RigidBody;
		class CollisionVolume;

		class GameSimsPhysics	{
		public:
			GameSimsPhysics();
			~GameSimsPhysics();

			void Update(float dt);

			void AddRigidBody(RigidBody* b);
			void RemoveRigidBody(RigidBody* b);

			void AddCollider(CollisionVolume* c);
			void UpdateCollider(CollisionVolume* c);
			void RemoveCollider(CollisionVolume* c);

			float clamp(float val, float minValue, float maxValue);

		protected:
			void IntegrationAcceleration(float dt);
			void IntegrationVelocity(float dt);
			void CollisionDetection(float dt);

			std::vector<RigidBody*>			allBodies;
			std::vector<CollisionVolume*>	allColliders;
		};
	}
}

