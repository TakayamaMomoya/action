//*****************************************************
//
// 敵の処理[enemy.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "score.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyshot.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define SPEED_MOVE	(1.0f)	// 移動速度
#define RATE_RADIUS	(1.5f)	// 当たり判定の大きさの倍率
#define INITIAL_LIFE	(1.0f)	// 初期体力
#define DAMAGE_FRAME	(10)	// ダメージ状態の継続フレーム数
#define INITIAL_SCORE	(1000)	// 初期スコア

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
int CEnemy::m_nNumAll = 0;	// 総数
CEnemy *CEnemy::m_pHead = nullptr;	// 先頭のアドレス
CEnemy *CEnemy::m_pTail = nullptr;	// 最後尾のアドレス

//=====================================================
// コンストラクタ
//=====================================================
CEnemy::CEnemy()
{
	// 総数カウントアップ
	m_nNumAll++;

	m_fLife = 0;
	m_nScore = 0;
	m_nTimerState = 0;
	m_pCollisionSphere = nullptr;
	m_state = STATE_NORMAL;

	// 値のクリア
	m_pPrev = nullptr;
	m_pNext = nullptr;

	if (m_pHead == nullptr)
	{// 先頭と最後尾アドレスの代入
		m_pHead = this;
		m_pTail = this;

		return;
	}

	// 前のアドレスに最後尾のアドレスを代入する
	m_pPrev = m_pTail;

	// 最後尾のアドレスを自分にする
	m_pTail = this;

	// 前のオブジェクトの次のアドレスを自分にする
	m_pPrev->m_pNext = this;
}

//=====================================================
// デストラクタ
//=====================================================
CEnemy::~CEnemy()
{
	if (m_state != STATE_DEATH)
	{
		m_nNumAll--;
	}

	if (m_pHead == this)
	{// 先頭アドレスの破棄
	 //if (m_pNext != nullptr)
		{// 先頭アドレスを次のアドレスに引き継ぐ
			m_pHead = m_pNext;

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}
	else if (m_pTail == this)
	{// 最後尾アドレスの破棄
		if (m_pPrev != nullptr)
		{// 最後尾アドレスを前のアドレスに引き継ぐ
			m_pTail = m_pPrev;

			m_pPrev->m_pNext = nullptr;
		}
	}
	else
	{// 真ん中のアドレスの破棄
	 // 前のアドレスから次のアドレスをつなぐ
		m_pPrev->m_pNext = m_pNext;

		// 次のアドレスから前のアドレスをつなぐ
		m_pNext->m_pPrev = m_pPrev;
	}
}

//=====================================================
// 生成処理
//=====================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// インスタンス生成
		switch (type)
		{
		case TYPE_SHOT:

			pEnemy = new CEnemyShot;

			pEnemy->CMotion::Load("data\\MOTION\\robot00.txt");

			pEnemy->SetMotion(0);

			break;
		default:
			break;
		}

		// 位置設定
		pEnemy->SetPosition(pos);

		// 初期化処理
		pEnemy->Init();
	}

	return pEnemy;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemy::Init(void)
{
	// 最も大きいパーツの半径取得
	float fRadius = GetRadiusMax();

	// 継承クラスの初期化
	CMotion::Init();

	// タイプの設定
	SetType(TYPE_ENEMY);

	if (m_pCollisionSphere == nullptr)
	{// 球の当たり判定生成
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMY, CCollision::TYPE_SPHERE,this);

		if (m_pCollisionSphere != nullptr)
		{// 情報の設定
			m_pCollisionSphere->SetPosition(GetPosition());
			m_pCollisionSphere->SetRadius(fRadius * RATE_RADIUS);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// 立方体の当たり判定
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_ENEMY, this);

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,-fRadius,-fRadius };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	// 体力の初期設定
	m_fLife = INITIAL_LIFE;

	// 通常状態にする
	m_state = STATE_NORMAL;

	m_nScore = INITIAL_SCORE;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemy::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{// 当たり判定の消去
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	// 継承クラスの終了
	CMotion::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemy::Update(void)
{
	// 継承クラスの更新
	CMotion::Update();

	// 状態管理処理
	ManageState();

	// 位置の更新
	SetPosition(GetPosition() + GetMove());

	// 当たり判定管理
	ManageCollision();
}

//=====================================================
// 当たり判定の管理
//=====================================================
void CEnemy::ManageCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// 球の当たり判定の管理
		m_pCollisionSphere->SetPositionOld(m_pCollisionSphere->GetPosition());

		m_pCollisionSphere->SetPosition(GetPosition());
	}

	if (m_pCollisionCube != nullptr)
	{// 立方体の当たり判定の管理
	 // パーツの最大半径取得
		float fRadius = GetRadiusMax();

		// 当たり判定の位置設定
		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,10.0f,-fRadius };

		D3DXVECTOR3 move = GetMove();

		// 押し出しの当たり判定
		m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);
	}
}

//=====================================================
// 状態管理
//=====================================================
void CEnemy::ManageState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		if (m_nTimerState > DAMAGE_FRAME)
		{// 通常状態に戻る
			m_nTimerState = 0;
			m_state = STATE_NORMAL;
		}
		else
		{// カウントアップ
			m_nTimerState++;
		}

		break;
	case STATE_DEATH:



		break;
	default:
		break;
	}
}

//=====================================================
// 体力設定
//=====================================================
void CEnemy::SetLife(float fLife)
{
	m_fLife = fLife;

	if (m_fLife < 0)
	{
		m_fLife = 0;
	}
}

//=====================================================
// ヒット処理
//=====================================================
void CEnemy::Hit(float fDamage)
{
	Death();
}

//=====================================================
// 死亡処理
//=====================================================
void CEnemy::Death(void)
{
	// 自身の終了
	Uninit();
}

//=====================================================
// 描画処理
//=====================================================
void CEnemy::Draw(void)
{
	// マトリックスの設定
	SetMatrix();

	// 継承クラスの描画
	CMotion::Draw();

#ifdef _DEBUG
	CManager::GetDebugProc()->Print("\n敵の位置：[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetDebugProc()->Print("\n敵の半径：[%f]", m_pCollisionSphere->GetRadius());
#endif
}

//=====================================================
// 球の当たり判定の位置設定
//=====================================================
void CEnemy::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{// 位置設定
		m_pCollisionSphere->SetPosition(pos);
	}
}

//=====================================================
// 読込処理
//=====================================================
void CEnemy::Load(void)
{

}