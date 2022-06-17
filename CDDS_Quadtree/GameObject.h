#pragma once
#include "AABB.h"

class GameObject
{
protected:
	Vector2 velocity = {100,100};
public:
	GameObject(Texture2D* m_texture, Vector2 position);
	~GameObject();
	
	void Update(float deltaTime);
	void Draw();

	Texture2D* m_texture;
	AABB m_bounds;
};

