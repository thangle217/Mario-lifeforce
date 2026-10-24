#pragma once

#include "Scene.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>

class CShipScene : public CScene
{
	CShip* player;
	CEnemy* enemy;
	std::vector<CBullet*> bullets;
	bool firing;
	ULONGLONG lastShotAt;
	void TryFire();

public:
	CShipScene(int id);
	void Load() override;
	void Unload() override;
	void Update(DWORD dt) override;
	void Render() override;
	void SetFiring(bool held);
	void OnFireKeyDown();
	CShip* GetPlayer() const { return player; }
};
