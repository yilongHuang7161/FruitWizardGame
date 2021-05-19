#pragma once
#include "../../Common/Vector2.h"
#include "SimObject.h"
#include <vector>
#include <iostream>

//class Circle;
//class Square;

/// <summary>
///		For checking collisions between Shapes.
/// </summary>
namespace NCL {
	namespace CSC3222 {

		class CollisionVolume {
		public:
			enum Type {
				PLAYER,
				FROGGO,
				GUARD,
				PIXIE,
				DUST,
				SPELL,
				FRUIT,
				WALL,
				LADDER,
				QUADTREE
			};
			/* CONSTRUCTORS & DECONSTRUCTORS */
			CollisionVolume();
			CollisionVolume(float posX, float posY, Vector2 halfLength, SimObject* object, Type type);
			CollisionVolume(float posX, float posY, Vector2 halfLength, Type type);
			~CollisionVolume();

			/* ABSTRACT METHOD */
			virtual bool CheckCollision(CollisionVolume& Other) = 0;

			/* METHODS */
			float GetPosX() const;
			float GetPosY() const;
			std::string getType() const;
			Vector2 GetHalfLength() const;
			void SetPosX(const float x);
			void SetPosY(const float y);
			void SetHalfLength(const Vector2 halfLength);
			void Transform(float offsetX, float offsetY);
			SimObject* getObject()const {
				return object;
			}

		private:
			float posX, posY;
			Type type;
			Vector2 halfLength;
			SimObject* object;
		};
	}
}