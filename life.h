//*****************************************************
//
// ライフ管理の処理[life.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _LIFE_H_
#define _LIFE_H_

#include "Object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CObject2D;

//*****************************************************
// クラスの定義
//*****************************************************
class CLife : public CObject
{
public:
	CLife(int nPriority = 6);	// コンストラクタ
	~CLife();	// デストラクタ

	static CLife *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};

private:
	CObject2D *m_pObjectGauge;	// ゲージのポインタ
};

#endif
