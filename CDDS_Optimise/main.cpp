/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"
#include "List.h"
#include "HashTable.h"

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	//SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	const int CRITTER_COUNT = 50;
	const int MAX_VELOCITY = 80;

	srand(time(NULL));
	HashTable<const char[], Texture2D> resources(CRITTER_COUNT);


	// create some critters

	List<Critter> aliveCritters;
	List<Critter> deadCritters;

	resources.operator["res/10.png"]

	for (int i = 0; i < CRITTER_COUNT; i++)
	{
		// create a random direction vector for the velocity
		Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
		// normalize and scale by a random speed
		velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
		Critter critter;
		// create a critter in a random location
		critter.Init(
			{ (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) },
			velocity,
			12, "res/10.png");
		aliveCritters.pushBack(critter);
	}

	Critter destroyer;
	Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
	velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
	destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, "res/9.png");

	float timer = 1;
	Vector2 nextSpawnPos = destroyer.GetPosition();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		float delta = GetFrameTime();

		// update the destroyer
		destroyer.Update(delta);
		// check each critter against screen bounds
		if (destroyer.GetX() < 0) {
			destroyer.SetX(0);
			destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
		}
		if (destroyer.GetX() > screenWidth) {
			destroyer.SetX(screenWidth);
			destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
		}
		if (destroyer.GetY() < 0) {
			destroyer.SetY(0);
			destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
		}
		if (destroyer.GetY() > screenHeight) {
			destroyer.SetY(screenHeight);
			destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
		}
		auto itr = aliveCritters.begin();
		itr--;
		// update the critters
		// (dirty flags will be cleared during update)
		for (Critter critter : aliveCritters)
		{
			itr++;
			critter.Update(delta);

			// check each critter against screen bounds
			if (critter.GetX() < 0) {
				critter.SetX(0);
				critter.SetVelocity(Vector2{ -critter.GetVelocity().x, critter.GetVelocity().y });
			}
			if (critter.GetX() > screenWidth) {
				critter.SetX(screenWidth);
				critter.SetVelocity(Vector2{ -critter.GetVelocity().x, critter.GetVelocity().y });
			}
			if (critter.GetY() < 0) {
				critter.SetY(0);
				critter.SetVelocity(Vector2{ critter.GetVelocity().x, -critter.GetVelocity().y });
			}
			if (critter.GetY() > screenHeight) {
				critter.SetY(screenHeight);
				critter.SetVelocity(Vector2{ critter.GetVelocity().x, -critter.GetVelocity().y });
			}

			// kill any critter touching the destroyer
			// simple circle-to-circle collision check
			float dist = Vector2Distance(critter.GetPosition(), destroyer.GetPosition());
			if (dist < critter.GetRadius() + destroyer.GetRadius())
			{
				deadCritters.pushBack(critter);
				aliveCritters.erase(itr);
			}
		}

		//  check for critter-on-critter collisions
		for (Critter crit1 : aliveCritters)
		{
			for (Critter crit2 : aliveCritters)
			{
				if (&crit1 == &crit2 || crit1.IsDirty()) // note: the other critter (j) could be dirty - that's OK
					continue;
				// check every critter against every other critter
				float dist = Vector2Distance(crit1.GetPosition(), crit2.GetPosition());
				if (dist < crit1.GetRadius() + crit2.GetRadius())
				{
					// collision!
					// do math to get critters bouncing
					Vector2 normal = Vector2Normalize(Vector2Subtract(crit2.GetPosition(), crit1.GetPosition()));

					// not even close to real physics, but fine for our needs
					crit1.SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
					// set the critter to *dirty* so we know not to process any more collisions on it
					crit1.SetDirty();

					// we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
					// to make sure the other critter is clean before we do the collision response
					if (!crit2.IsDirty()) {
						crit2.SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
						crit2.SetDirty();
					}
					break;
				}
			}
		}

		timer -= delta;
		if (timer <= 0)
		{
			timer = 1;

			// find any dead critters and spit them out (respawn)
			if (!deadCritters.empty())
			{
				Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

				// get a position behind the destroyer, and far enough away that the critter won't bump into it again
				Vector2 pos = destroyer.GetPosition();
				pos = Vector2Add(pos, Vector2Scale(normal, -50));
				// its pretty ineficient to keep reloading textures. ...if only there was something else we could do
				deadCritters.first().Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, "res/10.png");
				aliveCritters.pushBack(deadCritters.first());
				deadCritters.popFront();
				break;
			}
			nextSpawnPos = destroyer.GetPosition();
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// draw the critters
		for (Critter critter : aliveCritters)
		{
			critter.Draw();
		}
		// draw the destroyer
		// (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
		// destroyer, it's because the origin is at the top-left. ...you could fix that!)
		destroyer.Draw();

		DrawFPS(10, 10);
		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	aliveCritters.clear();
	deadCritters.clear();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}