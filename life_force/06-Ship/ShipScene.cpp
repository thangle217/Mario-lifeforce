#include "ShipScene.h"
#include "Ship.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"
#include "AssetIDs.h"

namespace
{
	const ULONGLONG SHOT_INTERVAL_MS = 60;

	bool Overlaps(CGameObject* a, CGameObject* b)
	{
		float al, at, ar, ab, bl, bt, br, bb;
		a->GetBoundingBox(al, at, ar, ab);
		b->GetBoundingBox(bl, bt, br, bb);
		return al < br && ar > bl && at < bb && ab > bt;
	}
}

class CShipKeyHandler : public CSceneKeyHandler
{
public:
	CShipKeyHandler(LPSCENE scene) : CSceneKeyHandler(scene) {}
	void OnKeyDown(int KeyCode) override
	{
		if (KeyCode == DIK_S)
			static_cast<CShipScene*>(CGame::GetInstance()->GetCurrentScene())->OnFireKeyDown();
	}

	void OnKeyUp(int KeyCode) override
	{
		if (KeyCode == DIK_S)
			static_cast<CShipScene*>(CGame::GetInstance()->GetCurrentScene())->SetFiring(false);
	}

	void KeyState(BYTE* states) override
	{
		CGame* game = CGame::GetInstance();
		CShipScene* scene = static_cast<CShipScene*>(game->GetCurrentScene());
		CShip* ship = scene->GetPlayer();
		if (ship == NULL) return;

		int horizontal = (game->IsKeyDown(DIK_RIGHT) ? 1 : 0)
			- (game->IsKeyDown(DIK_LEFT) ? 1 : 0);
		int vertical = (game->IsKeyDown(DIK_DOWN) ? 1 : 0)
			- (game->IsKeyDown(DIK_UP) ? 1 : 0);
		ship->SetInput(horizontal, vertical);
		scene->SetFiring(game->IsKeyDown(DIK_S) != 0);
	}
};

CShipScene::CShipScene(int id) : CScene(id, L""), player(NULL), enemy(NULL), firing(false), lastShotAt(0)
{
	key_handler = new CShipKeyHandler(this);
}

void CShipScene::Load()
{
	LPTEXTURE texture = CTextures::GetInstance()->Get(ID_TEX_SHIP);
	if (texture == NULL) return;

	CSprites* sprites = CSprites::GetInstance();
	sprites->Add(ID_SPRITE_SHIP_LEFT,  24, 8,  47, 23, texture);
	sprites->Add(ID_SPRITE_SHIP_RIGHT, 56, 8,  79, 23, texture);
	sprites->Add(ID_SPRITE_SHIP_UP,    88, 8, 111, 23, texture);
	sprites->Add(ID_SPRITE_SHIP_DOWN, 120, 8, 143, 23, texture);
	sprites->Add(ID_SPRITE_SHIP_BULLET, 264, 32, 279, 47, texture);
	LPTEXTURE enemyTexture = CTextures::GetInstance()->Get(ID_TEX_LIFE_FORCE_ENEMY);
	if (enemyTexture != NULL)
	{
		sprites->Add(ID_SPRITE_SHIP_ENEMY, 24, 96, 47, 111, enemyTexture);
		CGame* game = CGame::GetInstance();
		enemy = new CEnemy(static_cast<float>(game->GetBackBufferWidth() - 40),
			static_cast<float>(game->GetBackBufferHeight()) / 2.0f);
	}

	player = new CShip(160.0f, 120.0f);

	CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
}

void CShipScene::Unload()
{
	for (CBullet* bullet : bullets) delete bullet;
	bullets.clear();
	delete enemy;
	enemy = NULL;
	delete player;
	player = NULL;
	firing = false;
	lastShotAt = 0;
}

void CShipScene::SetFiring(bool held)
{
	firing = held;
}

void CShipScene::OnFireKeyDown()
{
	firing = true;
	TryFire();
}

void CShipScene::TryFire()
{
	if (player == NULL) return;
	ULONGLONG now = GetTickCount64();
	if (lastShotAt != 0 && now - lastShotAt < SHOT_INTERVAL_MS) return;

	float x, y;
	player->GetPosition(x, y);
	bullets.push_back(new CBullet(x + 14.0f, y));
	lastShotAt = now;
}

void CShipScene::Update(DWORD dt)
{
	if (player != NULL) player->Update(dt);
	if (firing) TryFire();

	for (auto it = bullets.begin(); it != bullets.end();)
	{
		CBullet* bullet = *it;
		bullet->Update(dt);
		if (!bullet->IsDeleted() && enemy != NULL && Overlaps(bullet, enemy))
		{
			bullet->Delete();
			enemy->Delete();
		}
		if (bullet->IsDeleted())
		{
			delete bullet;
			it = bullets.erase(it);
		}
		else ++it;
	}
	if (enemy != NULL && enemy->IsDeleted())
	{
		delete enemy;
		enemy = NULL;
	}
}

void CShipScene::Render()
{
	if (enemy != NULL) enemy->Render();
	for (CBullet* bullet : bullets) bullet->Render();
	if (player != NULL) player->Render();
}
