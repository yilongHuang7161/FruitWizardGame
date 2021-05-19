#pragma once
#include "Circle.h"
#include "CollisionVolume.h"
#include "SimObject.h"

using namespace NCL::CSC3222;
using namespace NCL::Maths;

/// <summary>
///		Class for the Square Shape.
/// </summary>
class Box : public CollisionVolume {
public:
	/* CONSTRUCTOR & DESTRUCTOR */
	Box();
	Box(float posX, float posY, SimObject* object, Vector2 halfLength,Type type);
	Box(float posX, float posY, Vector2 halfLength, Type type);
	~Box();

	/* METHODS */
	Vector2 GetHalfLength() const;
	bool CheckCollision(CollisionVolume& Other);
private:
	Vector2 halfLength;
};
	