#pragma once

#include "GameObject.h"

class CEnemy : public CGameObject
{
public:
	CEnemy(float x, float y) : CGameObject(x, y) {}
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	int IsBlocking() override { return 0; }
};
