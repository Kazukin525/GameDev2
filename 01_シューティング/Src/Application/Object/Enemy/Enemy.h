#pragma once
#include"Application/Object/BaseObject.h"
class GameScene;
class Enemy: public BaseObject
{
public:
	Enemy() {}
	~Enemy() { Release(); }

	void Update()override;
	void Draw()override;
	void Init()override;

	void OnHit()override;
	
	// セッター
	void SetOwner(GameScene* _owner) { m_owner = _owner; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = {_x,_y,0.0f}; }	// SetPos()をオーバーロード
	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }
private:
	GameScene* m_owner;
	Math::Vector3 m_movePow;		// 移動量

	void Release()override;
};
