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
#include "missile.h"
#include "effect3D.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define INITIAL_LIFE	(50.0f)	// 初期体力
#define INITIAL_SCORE	(500)	// 初期スコア
#define TIME_SHOT	(240)	// 射撃までのカウンター
#define ROLL_FACT	(0.1f)	// 回転係数
#define BULLET_SPEED	(2.0f)	// 弾の速度
#define BULLET_SIZE	(2.5f)	// 弾の大きさ
#define GRAVITY	(0.3f)	// 重力
#define TIME_MISSILE	(20)	// ミサイル発射頻度
#define MISSILE_UP	(3.0f)	// ミサイルの初速
#define NUM_MISSILE	(3)	// ミサイルの発射数
#define MOVE_FACT	(0.05f)	// 移動係数
#define LINE_END	(5.0f)	// 移動終了のしきい値

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEnemyBoss::CEnemyBoss()
{
	// 自身の情報をクリア
	ZeroMemory(&m_info,sizeof(Sinfo));
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
	m_info.state = STATE_APPER;

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

	// 条件ごとの更新
	UpdateState();
	
	// 当たり判定管理
	ManageCollision();

	// 攻撃の管理
	ManageAttack();

	if (CEnemy::GetState() == STATE_DEATH)
	{
		Death();
	}
}

//=====================================================
// 状態ごとの更新分岐
//=====================================================
void CEnemyBoss::UpdateState(void)
{
	switch (m_info.state)
	{
	case STATE_APPER:
		UpdateApper();
		break;
	case STATE_BATTLE:
		UpdateAttackState();
		break;
	default:
		break;
	}
}

//=====================================================
// 出現状態の更新
//=====================================================
void CEnemyBoss::UpdateApper(void)
{
	bool bFinish = IsFinish();

	if (bFinish)
	{// 状態切り替え
		SwitchState();

		m_info.state = STATE_BATTLE;
		SwitchState();
	}
}

//=====================================================
// 戦闘状態の更新
//=====================================================
void CEnemyBoss::UpdateAttackState(void)
{
	switch (m_info.attackState)
	{
	case ATTACK_MISSILE:
		UpdateMissile();
		break;
	case ATTACK_DASH:
		UpdateDash();
		break;
	default:
		break;
	}
}

//=====================================================
// ミサイル攻撃の更新
//=====================================================
void CEnemyBoss::UpdateMissile(void)
{
	// プレイヤーの方を向く処理
	RotDest();

	m_info.posDest = { 2580.0f, 190.0f, 0.0f };

	// 目標位置追従
	bool bEnd = FollowDest();

	if (bEnd)
	{
		// ミサイル攻撃
		m_info.nCntAttack++;

		if (TIME_MISSILE <= m_info.nCntAttack)
		{// ミサイル発射
			D3DXVECTOR3 pos = GetMtxPos(IDX_SHOULDER_L);

			CMissile *pMissile = CMissile::Create(pos);

			if (pMissile != nullptr)
			{
				pMissile->SetMove(D3DXVECTOR3(0.0f, MISSILE_UP, 0.0f));
			}

			m_info.nCntAttack = 0;

			// 攻撃回数加算
			m_info.nNumAttack++;

			if (m_info.nNumAttack >= NUM_MISSILE)
			{
				SwitchState();
			}
		}
	}
}

//=====================================================
// 突進攻撃の更新
//=====================================================
void CEnemyBoss::UpdateDash(void)
{
	bool bFinish = IsFinish();

	if (bFinish)
	{// 状態切り替え
		m_info.posDest = { 2900.0f,190.0f,0.0f };

		// 目標位置追従
		bool bEnd = FollowDest();

		if (bEnd)
		{
			SwitchState();
		}
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
// 当たり判定の追従
//=====================================================
void CEnemyBoss::FollowCollision(void)
{
	CCollisionSphere *pCollision = GetClsnSphere();

	if (pCollision != nullptr)
	{
		D3DXVECTOR3 pos = GetMtxPos(IDX_WAIST);

		CEffect3D::Create(pos, pCollision->GetRadius(), 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		pCollision->SetPositionOld(pCollision->GetPosition());
		pCollision->SetPosition(pos);
	}
}

//=====================================================
// 目標位置への移動
//=====================================================
bool CEnemyBoss::FollowDest(void)
{
	bool bEnd = false;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 vecDiff = m_info.posDest - pos;

	// 差分距離の取得
	float fLength = D3DXVec3Length(&vecDiff);

	if (LINE_END > fLength)
	{
		bEnd = true;
	}

	vecDiff *= MOVE_FACT;

	pos += vecDiff;

	SetPosition(pos);

	return bEnd;
}

//=====================================================
// 状態の切り替え
//=====================================================
void CEnemyBoss::SwitchState(void)
{
	m_info.nNumAttack = 0;

	// 状態を振る
	m_info.attackState = (ATTACKSTATE)(rand() % (ATTACK_MAX));

	switch (m_info.attackState)
	{
	case ATTACK_MISSILE:

		SetMotion(MOTION_MISSILE);

		break;
	case ATTACK_DASH:

		SetMotion(MOTION_DASH);

		break;
	default:
		break;
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