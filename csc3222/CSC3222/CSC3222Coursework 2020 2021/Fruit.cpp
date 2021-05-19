#include "Fruit.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "FruitWizardGame.h"
#include "GameSimsPhysics.h"

using namespace NCL;
using namespace CSC3222;

Fruit::Fruit() : SimObject(),isHit(false) {
	texture = texManager->GetTexture("FruitWizard\\Fruit.png");

	int fruitID = rand() % 16;

	animFrameData = Vector4((fruitID / 4) * 16.0f, (fruitID % 4) * 16.0f, 16.0f, 16.0f);
}

Fruit::~Fruit() {
}

bool Fruit::UpdateObject(float dt) {
	if (isHit) {
		game->physics->RemoveCollider(GetCollider());
		game->physics->RemoveRigidBody(this);
		game->currentScore += 1000;
		game->fruitCount++;
		return false;
	}
	return true;
}