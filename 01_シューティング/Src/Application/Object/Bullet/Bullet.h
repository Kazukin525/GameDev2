#pragma once

#include "Application/Object/BaseObject.h"
class GameScene;
class Bullet:public BaseObject
{
public:
	Bullet() {}
	~Bullet() { Release(); }

	void Update()override;
	void Draw()override;
	void Init()override;

	void OnHit()override;

	// セッター
	void SetOwner(GameScene* _owner) { m_owner = _owner; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = { _x,_y,0.0f }; }	// SetPos()をオーバーロード


	// ゲッター
	Math::Vector3 GetPos() { return m_pos; }

private:
	void Release()override;

	Math::Vector3 m_movePow;
	GameScene* m_owner;
};
