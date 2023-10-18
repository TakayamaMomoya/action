//*****************************************************
//
// ボス敵の処理[enemyboss.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyboss.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "bullet.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define INITIAL_LIFE	(5)	// 初期体力
#define INITIAL_SCORE	(500)	// 初期スコア
#define TIME_SHOT	(240)	// 射撃までのカウンター
#define ROLL_FACT	(0.1f)	// 回転係数
#define BULLET_SPEED	(2.0f)	// 弾の速度
#define BULLET_SIZE	(2.5f)	// 弾の大きさ
#define GRAVITY	(0.3f)	// 重力

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEnemyBoss::CEnemyBoss()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBoss::~CEnemyBoss()
{

}

//=====================================================
// 生成処理
//=====================================================
CEnemyBoss *CEnemyBoss::Create(void)
{
	if (m_pEnemyBoss == nullptr)
	{
		m_pEnemyBoss = new CEnemyBoss;
	}

	return m_pEnemyBoss;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyBoss::Init(void)
{
	// 継承クラスの初期化
	CEnemy::Init();

	// 初期の体力設定
	SetLife(INITIAL_LIFE);

	// スコア設定
	SetScore(INITIAL_SCORE);

	// モーション設定
	SetMotion(MOTION_APPER);

	// 出現地点合わせ
	SetMatrix();
	CMotion::Update();
	CMotion::Update();

	FollowCollision();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyBoss::Uninit(void)
{
	CGame::SetState(CGame::STATE_END);

	m_pEnemyBoss = nullptr;

	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyBoss::Update(void)
{
	// 位置を保存
	SetPositionOld(GetPosition());

	// 継承クラスの更新
	CEnemy::Update();
	
	// 当たり判定管理
	ManageCollision();

	// 攻撃の管理
	ManageAttack();

	// 重力
	D3DXVECTOR3 move = GetMove();

	move.y -= GRAVITY;

	SetMove(move);

	if (GetState() == STATE_DEATH)
	{
		Death();
	}
}

//=====================================================
// 当たり判定管理
//=====================================================
void CEnemyBoss::ManageCollision(void)
{
	// 当たり判定追従
	FollowCollision();
}

//=====================================================
// 当たりの追従
//=====================================================
void CEnemyBoss::FollowCollision(void)
{
	CCollisionSphere *pCollision = GetClsnSphere();

	if (GetParts(0) != nullptr)
	{
		D3DXMATRIX mtx = *GetParts(0)->m_pParts->GetMatrix();
		D3DXVECTOR3 pos =
		{
			mtx._41,
			mtx._42,
			mtx._43,
		};

		pCollision->SetPositionOld(pCollision->GetPosition());
		pCollision->SetPosition(pos);
	}
}

//=====================================================
// 攻撃管理
//=====================================================
void CEnemyBoss::ManageAttack(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CEnemyBoss::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();

#ifdef _DEBUG
	CManager::GetDebugProc()->Print("\nボスモーション：[%d]", GetMotion());
	CManager::GetDebugProc()->Print("\nキー：[%d]", GetKey());
	CManager::GetDebugProc()->Print("\nフレーム：[%d]", GetFrame());
	CManager::GetDebugProc()->Print("\nIsFinish：[%d]", IsFinish());
#endif
}