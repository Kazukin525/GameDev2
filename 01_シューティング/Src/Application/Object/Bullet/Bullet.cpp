#include "Bullet.h"
#include "Application/Scene/GameScene.h"

void Bullet::Update()
{
	if (!m_aliveFlg) { return; }
	
	m_pos += m_movePow;

	if (m_pos.y >= 360 + 37)
	{
		m_aliveFlg = false;
	}

	for (auto& obj : m_owner->GetObjList())
	{
		//// 自分自身とは当たり判定しない
		//if (obj->GetObjType() == ObjectType::Player ||
		//	obj->GetObjType() == ObjectType::Bullet) { continue; }

		// 敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			// 対象座標　-　弾座標　＝　対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			// 球判定　・・・　ベクトルの長さで判定
			// v.Length...
			if (v.Length() < 32.0f)
			{
				// Hitした敵の処理を行う
				obj->OnHit();

				// 弾もHitした時の処理を行う
				OnHit();
				break;
			}
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Bullet::Draw()
{
	if (!m_aliveFlg) { return; }
	Math::Rectangle rc = { 0,0,12,37 };
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		&m_tex, 0, 0, 12, 37, &rc);
}

void Bullet::Init()
{
	m_pos = {};
	m_movePow = { 0.0f,10.0f,0.0f };
	m_mat = Math::Matrix::Identity;
	m_tex.Load("Asset/Textures/bullet.png");

	m_aliveFlg = true;

	m_objType = ObjectType::Bullet;
}

void Bullet::OnHit()
{
	m_aliveFlg = false;
}

void Bullet::Release()
{
	m_tex.Release();
}
