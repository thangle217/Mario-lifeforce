#include <algorithm>

#include "Ship.h"
#include "Game.h"

CShip::CShip(float x, float y) : CGameObject(x, y), spriteId(ID_SPRITE_SHIP_LEFT)
{
}

void CShip::SetInput(int horizontal, int vertical)
{
	const float speed = 0.15f; // pixels per millisecond
	vx = horizontal * speed;
	vy = vertical * speed;

	if (horizontal != 0 && vertical != 0)
	{
		vx *= 0.70710678f;
		vy *= 0.70710678f;
	}

	// Vertical sprite takes priority while two directions are held.
	if (vertical < 0) spriteId = ID_SPRITE_SHIP_UP;
	else if (vertical > 0) spriteId = ID_SPRITE_SHIP_DOWN;
	else if (horizontal < 0) spriteId = ID_SPRITE_SHIP_LEFT;
	else if (horizontal > 0) spriteId = ID_SPRITE_SHIP_RIGHT;
	else spriteId = ID_SPRITE_SHIP_LEFT;
}

void CShip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	x += vx * dt;
	y += vy * dt;

	// The four sprite rectangles are currently 24 x 16 pixels.
	const float halfWidth = 12.0f;
	const float halfHeight = 8.0f;
	x = (std::max)(halfWidth, (std::min)(x, static_cast<float>(game->GetBackBufferWidth()) - halfWidth));
	y = (std::max)(halfHeight, (std::min)(y, static_cast<float>(game->GetBackBufferHeight()) - halfHeight));
}

void CShip::Render()
{
	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite != NULL) sprite->Draw(x, y);
}

void CShip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 12.0f;
	top = y - 8.0f;
	right = x + 12.0f;
	bottom = y + 8.0f;
}
