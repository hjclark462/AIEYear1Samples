#include "EntityDisplayApp.h"

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{

}

EntityDisplayApp::~EntityDisplayApp()
{

}

bool EntityDisplayApp::Startup()
{
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);
	h = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedMemory");
	int* size = (int*)MapViewOfFile(h, FILE_MAP_READ, 0, 0, sizeof(int));
	ENTITY_COUNT = *size;	
	memptr = (int*)MapViewOfFile(h, FILE_MAP_READ, 0, 0, sizeof(int) + (sizeof(Entity)*ENTITY_COUNT));
	memptr++;
	m_entities = (Entity*)memptr;
	
	return true;
}

void EntityDisplayApp::Shutdown()
{
	UnmapViewOfFile(h);
	CloseHandle(h);
	CloseWindow();        // Close window and OpenGL context
}

void EntityDisplayApp::Update(float deltaTime)
{

}

void EntityDisplayApp::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (int i = 0; i < ENTITY_COUNT; i++) 
	{
		DrawRectanglePro(
			Rectangle{ m_entities[i].x, m_entities[i].y, m_entities[i].size, m_entities[i].size }, // rectangle
			Vector2{ m_entities[i].size / 2, m_entities[i].size / 2 }, // origin
			m_entities[i].rotation,
			Color{ m_entities[i].r, m_entities[i].g, m_entities[i].b, 255 });
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}