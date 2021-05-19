#include "PixieDust.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "FruitWizardGame.h"
#include "GameSimsPhysics.h"

using namespace NCL;
using namespace CSC3222;

Vector4 animFrames[] = {
	Vector4(64 , 192, 32, 32),
	Vector4(96, 192, 32, 32),
	Vector4(128, 192, 32, 32),
	Vector4(160, 192, 32, 32)
};

PixieDust::PixieDust() : SimObject(),isHit(false) {
	animFrameCount = 4;
	texture = texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
}

PixieDust::~PixieDust() {
}

bool PixieDust::UpdateObject(float dt) {
	animFrameData = animFrames[currentanimFrame];

	if (isHit) {
		game->physics->RemoveCollider(GetCollider());
		game->physics->RemoveRigidBody(this);
		game->currentScore += 500;
		game->dustCount += 1;
		return false;
	}
	return true;
}