#include "BaseObject.h"

void BaseObject::Update()
{
}

void BaseObject::Draw()
{
}

void BaseObject::Init()
{
	
}

void BaseObject::Release()
{
}

//引数は_を付ける

void BaseObject::SetTex(std::string _fileName) 
{
	m_tex.Load(_fileName);
}

void BaseObject::OnHit()
{
}
