#include "GameObject.h"
#include "raylib.h"

GameObject::GameObject(Texture2D* texture, Vector2 position)
{
	m_texture = texture;

	m_bounds.m_centre = position;
	m_bounds.m_halfSize.x = m_texture->height >> 1;
	m_bounds.m_halfSize.y = m_texture->width >> 1;
}


GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
    if (m_bounds.m_centre.x < 0) 
    {
        m_bounds.m_centre.x = 0;
        velocity = { -velocity.x, velocity.y };
    }
    if (m_bounds.m_centre.x > GetScreenWidth()) 
    {
        m_bounds.m_centre.x = GetScreenWidth();
        velocity = {-velocity.x, velocity.y };
    }
    if (m_bounds.m_centre.y < 0) 
    {
        m_bounds.m_centre.y=0;
        velocity = { velocity.x, -velocity.y };
    }
    if (m_bounds.m_centre.y > GetScreenHeight()) 
    {
        m_bounds.m_centre.y = GetScreenHeight();
        velocity = {velocity.x, -velocity.y };
    }
	m_bounds.m_centre.x += velocity.x * deltaTime;
	m_bounds.m_centre.y += velocity.y * deltaTime;
}

void GameObject::Draw()
{	
	DrawTexture(*m_texture, m_bounds.m_centre.x, m_bounds.m_centre.y, WHITE);
}