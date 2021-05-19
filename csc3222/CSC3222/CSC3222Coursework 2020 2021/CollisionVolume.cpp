#include "CollisionVolume.h"

using namespace NCL::CSC3222;
using namespace NCL::Maths;

CollisionVolume::CollisionVolume() {}

CollisionVolume::CollisionVolume(float posX, float posY, Vector2 halfLength, SimObject* object, Type type) :
	posX(posX),
	posY(posY),
	halfLength(halfLength),
	object(object),
	type(type){};


// Copy Constructor
CollisionVolume::CollisionVolume(float posX, float posY, Vector2 halfLength, Type type) :
	posX(posX),
	posY(posY), 
	halfLength(halfLength),
	type(type){};

CollisionVolume::~CollisionVolume() {}

float CollisionVolume::GetPosX() const { 
	if (object)
		return object->GetPosition().x;
	else
		return posX;
}

float CollisionVolume::GetPosY() const {
	if (object!=nullptr)
		return object->GetPosition().y;
	else
		return posY;
}

Vector2 CollisionVolume::GetHalfLength() const { return halfLength; }

void CollisionVolume::SetPosX(float x) { this->posX = x; }

void CollisionVolume::SetPosY(float y) { this->posY = y; }

void CollisionVolume::SetHalfLength(const Vector2 halfLength) { this->halfLength = halfLength; }

/* Moves CollisionVolume to a new position in the grid. */
void CollisionVolume::Transform(float newX, float newY) {
	this->SetPosX(newX);
	this->SetPosY(newY);
}

std::string CollisionVolume::getType() const
{
	std::string res;
	switch (type)
	{
	case NCL::CSC3222::CollisionVolume::PLAYER:
		res = "player";
		break;
	case NCL::CSC3222::CollisionVolume::FROGGO:
		res = "froggo";
		break;
	case NCL::CSC3222::CollisionVolume::GUARD:
		res = "guard";
		break;
	case NCL::CSC3222::CollisionVolume::PIXIE:
		res = "pixie";
		break;
	case NCL::CSC3222::CollisionVolume::DUST:
		res = "dust";
		break;
	case NCL::CSC3222::CollisionVolume::SPELL:
		res = "spell";
		break;
	case NCL::CSC3222::CollisionVolume::FRUIT:
		res = "fruit";
		break;
	case NCL::CSC3222::CollisionVolume::WALL:
		res = "wall";
		break;
	case NCL::CSC3222::CollisionVolume::LADDER:
		res = "ladder";
		break;
	case NCL::CSC3222::CollisionVolume::QUADTREE:
		res = "quadtree";
		break;
	default:
		break;
	}
	return res;
}
