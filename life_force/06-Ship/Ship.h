#pragma once

#include "GameObject.h"
#include "AssetIDs.h"

class CShip : public CGameObject
{
	int spriteId;

public:
	CShip(float x, float y);
	void SetInput(int horizontal, int vertical);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};
