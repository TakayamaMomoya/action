//*****************************************************
//
// 撃ってくる敵の処理[enemyshot.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYSHOT_H_
#define _ENEMYSHOT_H_

#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyShot : public CEnemy
{// 撃ってくる敵
public:
	CEnemyShot();	// コンストラクタ
	~CEnemyShot();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};

#endif
