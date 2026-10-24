#pragma once

#include "GameObject.h"

class CBullet : public CGameObject
{
public:
	CBullet(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	int IsBlocking() override { return 0; }
};
