#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "QuadTree.h"
#include "../../Common/Vector2.h"
#include "Spell.h"
#include "Fruit.h"
#include "FruitWizardGame.h"
#include "PixieDust.h"
#include "Pixie.h"
#include "PlayerCharacter.h"

using namespace NCL;
using namespace CSC3222;

GameSimsPhysics::GameSimsPhysics()	{

}

GameSimsPhysics::~GameSimsPhysics()	{

}

void GameSimsPhysics::Update(float dt) {
	IntegrationAcceleration(dt);
	CollisionDetection(dt);
	IntegrationVelocity(dt);

	for (auto it : allBodies) {
		it->force = Vector2(0, 0);
	}
}

void GameSimsPhysics::AddRigidBody(RigidBody* b) {
	allBodies.emplace_back(b);
}

void GameSimsPhysics::RemoveRigidBody(RigidBody* b) {
	auto at = std::find(allBodies.begin(), allBodies.end(), b);

	if (at != allBodies.end()) {
		//maybe delete too?
		allBodies.erase(at);
	}
}

void GameSimsPhysics::AddCollider(CollisionVolume* c) {
	allColliders.emplace_back(c);
}

void GameSimsPhysics::UpdateCollider(CollisionVolume* c) {
	for (int i = 0; i < allColliders.size(); i++) {
		if (allColliders[i] == c)
			allColliders[i] = c;			
	}
}

void GameSimsPhysics::RemoveCollider(CollisionVolume* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
	}
}

float NCL::CSC3222::GameSimsPhysics::clamp(float val, float minValue, float maxValue)
{
	val = std::min(val, maxValue);
	val = std::max(val, minValue);
	return val;
}

void GameSimsPhysics::IntegrationAcceleration(float dt) {
	for (auto i : allBodies) {
		Vector2 accleration = i->force * i->inverseMass;
		i->velocity += accleration * dt;
	}
}

void GameSimsPhysics::IntegrationVelocity(float dt) {
	for (auto i : allBodies) {
		i->position = i->position + i->velocity;
		i->velocity *= 0.6;
	}
}

void GameSimsPhysics::CollisionDetection(float dt) {
	QuadTree quadTree = QuadTree(0, Box(0, 0, Vector2(480, 320), CollisionVolume::Type::QUADTREE));

	quadTree.Clear();

	for (int i = 0; i < allColliders.size(); i++)
		quadTree.Insert(allColliders[i]);

	std::vector<CollisionVolume*> retrievedObjects;
	for (int i = 0; i < allColliders.size(); i++) {
		retrievedObjects.clear();
		retrievedObjects = quadTree.RetrieveObjects(retrievedObjects, allColliders[i]);
		
		for (int j = 0; j < retrievedObjects.size(); j++) {
			for (int k = j + 1; k < retrievedObjects.size(); k++) {
				if (retrievedObjects[j]->CheckCollision(*retrievedObjects[k])) {
					std::cout << "Collision between: [" << allColliders[j]->getType() << "," << allColliders[k]->getType() << "]" << std::endl;

					if (allColliders[j]->getType() == "fruit" && allColliders[k]->getType() == "player") {
						dynamic_cast<Fruit*>(allColliders[j]->getObject())->isHit = true;
					}

					else if (allColliders[j]->getType() == "player" && allColliders[k]->getType() == "fruit") {
						dynamic_cast<Fruit*>(allColliders[k]->getObject())->isHit = true;
					}

					if (allColliders[j]->getType() == "spell" && allColliders[k]->getType()!="player") {
						dynamic_cast<Spell*>(allColliders[j]->getObject())->SpellBounced();
					}
					else if (allColliders[k]->getType() == "spell" && allColliders[j]->getType() != "player") {
						dynamic_cast<Spell*>(allColliders[k]->getObject())->SpellBounced();
					}

					if (allColliders[j]->getType() == "dust" && allColliders[k]->getType() == "player") {
						dynamic_cast<PixieDust*>(allColliders[j]->getObject())->isHit = true;
					}

					else if (allColliders[k]->getType() == "dust" && allColliders[j]->getType() == "player") {
						dynamic_cast<PixieDust*>(allColliders[k]->getObject())->isHit = true;
					}

					if (allColliders[j]->getType() == "pixie" && allColliders[k]->getType() == "player") {
						dynamic_cast<Pixie*>(allColliders[j]->getObject())->isHit = true;
					}

					else if (allColliders[k]->getType() == "pixie" && allColliders[j]->getType() == "player") {
						dynamic_cast<Pixie*>(allColliders[k]->getObject())->isHit = true;
					}

					if (allColliders[j]->getType() == "wall" && allColliders[k]->getType() == "player") {
						dynamic_cast<PlayerCharacter*>(allColliders[k]->getObject())->isFall = false;
					}

					else if (allColliders[k]->getType() == "wall" && allColliders[j]->getType() == "player") {
						dynamic_cast<PlayerCharacter*>(allColliders[j]->getObject())->isFall = false;
					}

					if (allColliders[j]->getType() == "ladder" && allColliders[k]->getType() == "player") {
						dynamic_cast<PlayerCharacter*>(allColliders[k]->getObject())->isClimb = true;
					}

					else if (allColliders[k]->getType() == "ladder" && allColliders[j]->getType() == "player") {
						dynamic_cast<PlayerCharacter*>(allColliders[j]->getObject())->isClimb = true;
					}
				}
			}
		}
	}
}
