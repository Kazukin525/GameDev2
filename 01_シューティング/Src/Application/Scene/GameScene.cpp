#include "GameScene.h"
#include"../Object/Player/Player.h"
#include"../Object/Enemy/Enemy.h"

void GameScene::PreUpdate()
{
	// Updateの前の更新処理
	// オブジェクトリストの整理をしておく
	
	// イテレーターとは・・・コンテナクラス用のポインタ（のようなもの）
	// コンテナを先頭から末尾までたどる際に使用

	// イテレータ作成　ベタ書き
	//std::vector<std::shared_ptr<BaseObject>>::iterator itr;
	//itr = m_objList.begin();

	// イテレータ作成　auto番
	auto itr = m_objList.begin();

	
	// end()  は 最後の要素の1つ後ろを返す
	while (itr != m_objList.end())
	{
		// オブジェクトの有効チェック
		if (!(*itr)->GetAlive())
		{
			// 無効なオブジェクトをリストから削除
			itr = m_objList.erase(itr);
		}
		else { itr++; }
	}
	
	
	// ↑のあとには有効なオブジェクトだけのリストになっている
}

void GameScene::Update()
{
	// 3%の確率で敵を出現させる
	if ((rand() % 100) < 3)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(640 + 32, (float)360 + 32);
		enemy->SetMovePow({ -2.0f,-2.0f,0 });
		enemy->SetOwner(this);
		m_objList.push_back(enemy);
	}
	
	

	// 全オブジェクトの更新関数を一括で呼ぶ
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}
	/*for (std::shared_ptr<BaseObject> i : m_objList)
	{
		i->Update();
	}*/
	//if (m_enemy != nullptr)m_enemy->Update();
	//if (m_player != nullptr)m_player->Update();
	
}

void GameScene::Draw()
{
	// 型推論なし
	/*for (std::shared_ptr<BaseObject> i : m_objList)
	{
		i->Draw();
	}*/

	//// 先生のやつ（型推論あり）
	//for (auto& obj : m_objList)
	//{
	//	obj->Draw();
	//}

	// 普通のやつ
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
	
	//if (m_enemy != nullptr)m_enemy->Draw();
	//if (m_player != nullptr)m_player->Draw();
}

void GameScene::Init()
{
	// アップキャスト
	//生ポ
	//m_player = new Player();
	//m_player->Init();
	//m_player->SetOwner(this);

	//スマポ
	//m_player = std::make_shared<Player>();
	//m_player->Init();

	//m_enemy = std::make_shared<Enemy>();
	//m_enemy->Init();

	
	// 派生先の関数を先にやっちゃう
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(float( - 640 + i * 128 + 64),(float)360);
		enemy->SetOwner(this);
		//enemy->SetMovePow({ 0,-1.0f,0 });
		m_objList.push_back(enemy);
	}
	
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	player->SetOwner(this);
	m_objList.push_back(player);
}

// オブジェクトリストにオブジェクトを追加
void GameScene::AddObject(std::shared_ptr<BaseObject> _obj)
{
	// リストの末尾に引数で渡された１要素を追加
	m_objList.push_back(_obj);
}

void GameScene::Release()
{
	//delete m_player;	//生ポインスタンス破棄

}
