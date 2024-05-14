#include "Player.h"
#include "Application/Scene/GameScene.h"
#include "../Bullet/Bullet.h"

void Player::Update()
{
	m_move = {};
	const float SPEED = 5.0f;
	if(GetAsyncKeyState(VK_UP) & 0x8000) { m_move.y += SPEED; }
	if(GetAsyncKeyState(VK_DOWN) & 0x8000) { m_move.y -= SPEED; }
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_move.x += SPEED; }
	if(GetAsyncKeyState(VK_LEFT) & 0x8000) { m_move.x -= SPEED; }

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_keyFlg)
		{
			Shot();
		}
		m_keyFlg = true;
	}
	else m_keyFlg = false;

	m_pos += m_move;

	// プレイヤーと敵の当たり判定　・・・　敵の情報が必要
	// オブジェクトリストを全て見ていく

	for (auto& obj : m_owner->GetObjList())
	{
		//// 自分自身とは当たり判定しない
		//if (obj->GetObjType() == ObjectType::Player ||
		//	obj->GetObjType() == ObjectType::Bullet) { continue; }
		//
		// 敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			// 対象座標　-　自分座標　＝　対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;
			
			// 球判定　・・・　ベクトルの長さで判定
			// v.Length...
			if (v.Length() <= 64.0f)
			{
				obj->OnHit();
			}
		}
	}

	//座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
	
	Anime();
}

void Player::Shot()
{
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
	bullet->Init();
	bullet->SetOwner(m_owner);
	bullet->SetPos(m_pos);
	m_owner->AddObject(bullet);
}


void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 64 * m_anime,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		&m_tex,0,0,64,64,&rc);

}

void Player::Init()
{
	m_tex.Load("Asset/Textures/player.png");
	m_pos = {};						// 0.0で初期化
	m_mat = Math::Matrix::Identity;	// 単位行列で初期化

	// アニメ
	m_anime = 0;
	m_frame = 0;

	m_keyFlg = false;

	m_objType = ObjectType::Player;

	// 単位行列・・・拡大率全て1.0、他の値は全て0
}


void Player::Release()
{
	//テクスチャはKdTexture型のデストラクタで
	//自動Releaseさせるので書かなくてよい
	//m_tex.Release();
}

void Player::Anime()
{
	const int MAX_FRAME = 5;	// 最大フレーム数
	const int MAX_ANIME = 4;
	m_frame++;
	if (m_frame >= MAX_FRAME)
	{
		m_frame = 0;
		m_anime++;
	}
	if (m_anime >= MAX_ANIME) { m_anime = 0; }
}
