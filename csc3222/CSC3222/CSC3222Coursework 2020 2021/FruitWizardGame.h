#pragma once
#include <vector>

namespace NCL::CSC3222 {
	class Collision;
	class GameMap;
	class SimObject;
	class GameSimsRenderer;
	class GameSimsPhysics;
	class TextureBase;
	class TextureManager;
	class PlayerCharacter;
	class Guard;
	class Pixie;
	class Fruit;
	class PixieDust;

	class FruitWizardGame {
	public:
		FruitWizardGame();
		~FruitWizardGame();

		void Update(float dt);
		void AddNewObject(SimObject* object);
		void VisualiseEnviromentColliders();
		void SetEnviromentCollisions();
		float RandomNumber(float Min, float Max);
		GameMap* currentMap;
		PlayerCharacter* player;
		GameSimsPhysics* physics;
		int currentScore;
		void generateFruit();
		int fruitCount;
		std::vector<Fruit*> testFruit;
		std::vector<PixieDust*> allDusts;
		int dustCount;
		int magicCount;
		bool pixieMode;
	protected:
		void InitialiseGame();
		TextureManager*		texManager;
		GameSimsRenderer*	renderer;

		Guard*				testGuard;
		Pixie*				testPixie;

		float gameTime;

		int lives;

		std::vector<SimObject*> gameObjects;
		std::vector<SimObject*> newObjects;
		std::vector<Collision*> allColliders;
	};
}