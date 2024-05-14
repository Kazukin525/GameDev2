#include "Enemy.h"
#include "Application/Scene/GameScene.h"

void Enemy::Update()
{
	// 座標更新
	m_pos += m_movePow;
	if (m_pos.y <= -360 - 64)
	{
		m_pos.y = 360 + 64;
	}

	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::Draw()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle src = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex
	(&m_tex, 0, 0, 64, 64, &src);
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/enemy.png");
	m_pos = {};						//0.0で初期化
	m_mat = Math::Matrix::Identity;	//単位行列で初期化
	m_movePow = { 0.0f,-2.5f,0.0f };
	m_objType = ObjectType::Enemy;
}

void Enemy::OnHit()
{
	m_aliveFlg = false;
}

void Enemy::Release()
{

}
