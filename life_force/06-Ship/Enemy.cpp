#include "Enemy.h"
#include "AssetIDs.h"
#include "Sprites.h"

void CEnemy::Render()
{
	LPSPRITE sprite = CSprites::GetInstance()->Get(ID_SPRITE_SHIP_ENEMY);
	if (sprite != NULL) sprite->Draw(x, y);
}

void CEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	// Placeholder hitbox; adjust after setting the real sprite rectangle.
	left = x - 12.0f;
	top = y - 12.0f;
	right = x + 12.0f;
	bottom = y + 12.0f;
}
