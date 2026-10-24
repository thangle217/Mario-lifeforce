#include "Bullet.h"
#include "AssetIDs.h"
#include "Sprites.h"
#include "Game.h"

CBullet::CBullet(float x, float y) : CGameObject(x, y)
{
	vx = 0.35f; // Fly right in screen coordinates (pixels per millisecond).
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	if (x > CGame::GetInstance()->GetBackBufferWidth() + 8.0f) Delete();
}

void CBullet::Render()
{
	LPSPRITE sprite = CSprites::GetInstance()->Get(ID_SPRITE_SHIP_BULLET);
	if (sprite != NULL) sprite->Draw(x, y);
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 2.0f;
	top = y - 3.0f;
	right = x + 2.0f;
	bottom = y + 3.0f;
}
