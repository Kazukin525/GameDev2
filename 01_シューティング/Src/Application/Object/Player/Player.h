#pragma once
#include "../BaseObject.h"

//基本的にヘッダーファイルの中で
//別のヘッダーファイルをインクルードするのはNG
//継承元クラスのヘッダーのみインクルードが必須なので可とする
class GameScene;
class Player:public BaseObject
{
public:
	Player() {};
	~Player() { Release(); }
	
	//override指定子
	//overrideの判別しやすくするため

	void Update()override;
	void Draw()override;
	void Init()override;
	
	// 弾を発射させる関数
	void Shot();
	
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:
	GameScene* m_owner = nullptr;
	void Release()override;
	void Anime();

	Math::Vector3 m_move;	

	bool m_keyFlg;

	//アニメ
	int m_anime;
	int m_frame;

};

