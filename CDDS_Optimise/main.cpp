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
#include "ResourceManager.h"
#include "List.h"

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	//SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	srand(time(NULL));

	
	

	// create some critters
	const int CRITTER_COUNT = 50;
	const int MAX_VELOCITY = 80;

	//Resource Manager
	ResourceManager rM(CRITTER_COUNT);
	string critSprite = "res/10.png";
	string destSprite = "res/9.png";
	rM.Add(critSprite, LoadTexture(critSprite.c_str()));
	rM.Add(destSprite, LoadTexture(destSprite.c_str()));

	Critter critters[CRITTER_COUNT];
	List<Critter*> aliveCritters;
	List<Critter*> deadCritters;

	for (int i = 0; i < CRITTER_COUNT; i++)
	{
		// create a random direction vector for the velocity
		// create a random direction vector for the velocity
		Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
		// normalize and scale by a random speed
		velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);

		// create a critter in a random location

		critters[i].Init(
			{ (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) },
			velocity,
			12, rM.Find(critSprite));

		aliveCritters.pushBack(&critters[i]);
	}
	

	Critter destroyer;
	Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
	velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
	destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, rM.Find(destSprite));

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

		// update the critters
		// (dirty flags will be cleared during update)


		for (auto i = aliveCritters.begin(); i != aliveCritters.end(); )
		{
			(*i)->Update(delta);

			// check each critter against screen bounds
			if ((*i)->GetX() < 0) {
				(*i)->SetX(0);
				(*i)->SetVelocity(Vector2{ -(*i)->GetVelocity().x, (*i)->GetVelocity().y });
			}
			if ((*i)->GetX() > screenWidth) {
				(*i)->SetX(screenWidth);
				(*i)->SetVelocity(Vector2{ -(*i)->GetVelocity().x, (*i)->GetVelocity().y });
			}
			if ((*i)->GetY() < 0) {
				(*i)->SetY(0);
				(*i)->SetVelocity(Vector2{ (*i)->GetVelocity().x, -(*i)->GetVelocity().y });
			}
			if ((*i)->GetY() > screenHeight) {
				(*i)->SetY(screenHeight);
				(*i)->SetVelocity(Vector2{ (*i)->GetVelocity().x, -(*i)->GetVelocity().y });
			}

			// kill any critter touching the destroyer
			// simple circle-to-circle collision check
			float dist = Vector2Distance((*i)->GetPosition(), destroyer.GetPosition());
			if (dist < (*i)->GetRadius() + destroyer.GetRadius())
			{
				(*i)->Destroy();
				deadCritters.pushBack((*i));
				auto itr = aliveCritters.begin();
				for (; itr != i; )
					itr++;
				i = aliveCritters.erase(itr);
			}
			else
			{
				i++;
			}
		}

		// check for critter-on-critter collisions
		for (Critter* critteri : aliveCritters)
		{
			for (Critter* critterj : aliveCritters)
			{
				if (critteri == critterj || critteri->IsDirty()) // note: the other critter (j) could be dirty - that's OK
				{
					continue;
				}
				// check every critter against every other critter
				float dist = Vector2Distance(critteri->GetPosition(), critterj->GetPosition());
				if (dist < critteri->GetRadius() + critterj->GetRadius())
				{
					// collision!
					// do math to get critters bouncing
					Vector2 normal = Vector2Normalize(Vector2Subtract(critterj->GetPosition(), critteri->GetPosition()));

					// not even close to real physics, but fine for our needs
					critteri->SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
					// set the critter to *dirty* so we know not to process any more collisions on it
					critteri->SetDirty();

					// we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
					// to make sure the other critter is clean before we do the collision response
					if (!critterj->IsDirty()) {
						critterj->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
						critterj->SetDirty();
					}
					break;
				}
			}
		}

		timer -= delta;
		if (timer <= 0)
		{
			timer = 1;
			if (deadCritters.count() > 0)
			{
				// find any dead critters and spit them out (respawn)
				for (auto i = deadCritters.begin(); i != deadCritters.end(); i++)
				{
					if ((*i)->IsDead())
					{
						Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

						// get a position behind the destroyer, and far enough away that the critter won't bump into it again
						Vector2 pos = destroyer.GetPosition();
						pos = Vector2Add(pos, Vector2Scale(normal, -50));
						// its pretty ineficient to keep reloading textures. ...if only there was something else we could do
						(*i)->Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, rM.Find(critSprite));
						aliveCritters.pushBack(*i);
						deadCritters.popFront();
						break;
					}
				}
			}
			nextSpawnPos = destroyer.GetPosition();

		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// draw the critters
		for (Critter* critter : aliveCritters)
		{
			critter->Draw();
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



	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
