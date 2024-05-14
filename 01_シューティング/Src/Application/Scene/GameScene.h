#pragma once
class BaseObject;
class GameScene
{
public:
	GameScene() {}
	~GameScene() { Release(); }

	void PreUpdate();	//更新をよぶ前の処理
	void Update();		//更新
	void Draw();		//描画
	void Init();		//初期化
	
	// オブジェクトリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList() { return m_objList; }
	
	// オブジェクトリストにオブジェクトを追加
	void AddObject(std::shared_ptr<BaseObject> _obj);

private:
	//インスタンスが破棄されるタイミングでリリースをすればいい
	void Release();		//終了処理　※外部に安易によばれたくない
	
	// ポリモーフィズムのルール
	// ・基底クラスにあるものしか呼べない（派生先は知らない）
	// ・共同が変化するのはオーバライドされた関数のみ
	// ・デストラクタには絶対にvirtualをつけて仮想関数にする
	// ->しないと基底クラスのデストラクタしか呼ばれない
	
	//Player* m_player = nullptr;	//派生クラスのポインタ
	//BaseObject* m_player = nullptr;
	//std::shared_ptr<Player> m_player = nullptr;	//スマポ
	//std::shared_ptr<BaseObject> m_player = nullptr;	//ベースのスマポ
	//std::shared_ptr<BaseObject> m_enemy = nullptr;

	// 全オブジェクトを可変長配列で管理

	std::vector<std::shared_ptr<BaseObject>> m_objList;
};
