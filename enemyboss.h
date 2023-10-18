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

	static CEnemyBoss *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyBoss *GetInstance(void) { return m_pEnemyBoss; }

private:
	enum MOTION
	{// モーション
		MOTION_APPER = 0,	// 出現モーション
		MOTION_MAX
	};

	void ManageAttack(void);
	void ManageCollision(void);
	void FollowCollision(void);

	static CEnemyBoss *m_pEnemyBoss;
};

#endif
