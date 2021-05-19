#include "Guard.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "GameMap.h"
#include "FruitWizardGame.h"
#include "PlayerCharacter.h"

using namespace NCL;
using namespace CSC3222;

Vector4 guardIdleFrames[] = {
	Vector4(384,32, 64, 32),
	Vector4(448,32, 64, 32),	
	Vector4(512,32, 64, 32),	
	Vector4(576,32, 64, 32),	
	Vector4(448,64, 64, 32),	
	Vector4(512,64, 64, 32),
};

Vector4 guardWalkFrames[] = {
	Vector4(384,96, 64, 32),
	Vector4(448,96, 64, 32),
	Vector4(512,96, 64, 32),
	Vector4(576,96, 64, 32),
	Vector4(640,96, 64, 32),
	Vector4(704,96, 64, 32),
};

Vector4 guardAttackFrames[] = {
	Vector4(384,128, 64, 32),
	Vector4(448,128, 64, 32),
	Vector4(512,128, 64, 32),
	Vector4(576,128, 64, 32),
	Vector4(640,128, 64, 32),
	Vector4(704,128, 64, 32),
};

Vector4 guardStunFrames[] = {
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
};

Guard::Guard() : SimObject(),distance(0) {
	texture = texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	animFrameCount	= 6;
	state = State::PATROL;
}

Guard::~Guard() {
}

bool Guard::UpdateObject(float dt) {
	

	//if (pathTimer <= 0) {
	//	pathFound = false;
	//}

	switch (state) {
	case State::ATTACK: AttackPlayer(dt); break;
	case State::PATROL: PatrolMap(); break;
	}

	pathTimer -= dt;



	//if (!pathFound) {
	//	std::vector<Vector2> path = SimObject::game->currentMap->InitialiseNode(position, targetPos);
	//	pathFound = true;

	//	pathTimer = 5;
	//}

	return true;
}

void NCL::CSC3222::Guard::AttackPlayer(float dt)
{
	animFrameData = guardAttackFrames[currentanimFrame];

	float testSpeed = 10;
	int fps = 60;
	Vector4* animSource = guardIdleFrames;

	frame++;
	//if (frame <= 3 * fps) {
	//	AddForce(Vector2(testSpeed, 0) / inverseMass);
	//	flipAnimFrame = true;
	//}
	//else if (frame >= 3 * fps) {
	//	AddForce(Vector2(-testSpeed, 0) / inverseMass);
	//	flipAnimFrame = false;
	//}

	if (frame > 6 * fps) {
		frame = 0;
	}

	Vector2 normalVector = Vector2((SimObject::game->player->GetPosition().x - position.x), (SimObject::game->player->GetPosition().y - position.y));

	AddForce(normalVector);

	float magnitude = sqrt(((SimObject::game->player->GetPosition().x - position.x) * (SimObject::game->player->GetPosition().x - position.x))
		+ ((SimObject::game->player->GetPosition().y - position.y) * (SimObject::game->player->GetPosition().y - position.y)));

	if (magnitude > 80) {
		state = State::PATROL;
	}
}

void NCL::CSC3222::Guard::PatrolMap()
{
	animFrameData = guardWalkFrames[currentanimFrame];

	int testSpeed = 8;

	Vector4* animSource = guardWalkFrames;

	if (flipAnimFrame&&distance<=40*testSpeed ) {
		AddForce(Vector2(testSpeed, 0) / inverseMass);
		distance += testSpeed;
		flipAnimFrame = true;
	}
	else if (distance>40*testSpeed||flipAnimFrame==false ) {
		AddForce(Vector2(-testSpeed, 0) / inverseMass);
		distance -= testSpeed;
		flipAnimFrame = false;
		if (distance == 0) {
			flipAnimFrame = true;
		}
	}

	float magnitude = sqrt(((SimObject::game->player->GetPosition().x - position.x) * (SimObject::game->player->GetPosition().x - position.x))
		+ ((SimObject::game->player->GetPosition().y - position.y) * (SimObject::game->player->GetPosition().y - position.y)));

	if (magnitude <= 80) {
		state = State::ATTACK;
	}
}
