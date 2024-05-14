#pragma once
class BaseObject
{
public:
	BaseObject() {};

	//派生先から消されるようになっている
	//メモリリークする可能性があるため
	//デストラクタにはvirtualを付ける
	virtual ~BaseObject() {};

	// オブジェクトの種類
	enum class ObjectType
	{
		Player,
		Enemy,
		Bullet
	};

	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Init()=0;
	virtual void Release()=0;

	// 引数は_を付ける
	void SetTex(std::string _fileName);

	// オブジェクトタイプを返す
	ObjectType GetObjType() { return m_objType; }
	bool GetAlive()			{ return m_aliveFlg; }

	Math::Vector3 GetPos() { return m_pos; }

	// Hit時の処理
	virtual void OnHit();

protected:
	Math::Vector3	m_pos;
	Math::Matrix	m_mat;
	KdTexture		m_tex;

	bool			m_aliveFlg = true;

	ObjectType		m_objType;
};
