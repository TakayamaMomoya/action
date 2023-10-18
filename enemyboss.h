//*****************************************************
//
// ボス敵の処理[enemyboss.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_

#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyBoss : public CEnemy
{// 撃ってくる敵
public:
	CEnemyBoss();	// コンストラクタ
	~CEnemyBoss();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	enum MOTION
	{// モーション
		MOTION_NEUTRAL = 0,	// 待機モーション
		MOTION_SHOT,	// 射撃モーション
		MOTION_MAX
	};

	void RotDest(void);
	void ManageAttack(void);
};

#endif
