//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "debugproc.h"
#include "particle.h"
#include "sound.h"
#include "collision.h"
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "collision.h"
#include "universal.h"
#include "game.h"
#include <stdio.h>
#include "motion.h"
#include "afterimage.h"
#include "effect3D.h"
#include "fade.h"
#include "enemyManager.h"
#include "bullet.h"
#include "animEffect3D.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define BODY_PATH	"data\\MOTION\\rayleigh.txt"	// 見た目のパス
#define PARAM_PATH	"data\\TEXT\\player.txt"	// パラメーターのパス
#define SPEED_MOVE	(0.3f)	// 移動速度
#define GRAVITY	(0.09f)	// 重力
#define JUMP_POW	(2.5f)	// ジャンプ力
#define MOVE_FACT	(0.8f)	// 移動量減衰
#define ROLL_FACT	(0.2f)	// 回転係数
#define LINE_STOP	(0.3f)	// 動いてる判定のしきい値
#define TIME_AFTERIMAGE	(4)	// 残像を出す頻度
#define ATTACK_JUMP	(2.8f)	// 空中攻撃のジャンプ力
#define BULLET_SPEED	(5.0f)	// 弾速度
#define BULLET_SIZE	(1.0f)	// 弾サイズ
#define TIME_DAMAGE	(30)	// ダメージ状態の時間
#define TIME_FLASH	(4)	// 点滅速度

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CPlayer *CPlayer::m_pPlayer = nullptr;	// 自身のポインタ

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	m_nLife = 0;
	m_nCntAfterImage = 0;
	m_nCntState = 0;
	m_fRadiusParry = 0.0f;
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_offsetParry = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_rotDest = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_bSprint = false;
	m_bAttack = false;
	m_pBody = nullptr;
	m_pCollisionCube = nullptr;
	m_pClsnAttack = nullptr;
	m_pClsnHit = nullptr;
	m_pAttackInfo = nullptr;
	m_state = STATE_NONE;
	m_jump = JUMPSTATE_NONE;
}

//=====================================================
// デストラクタ
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayer::Init(void)
{
	// 情報の読込
	Load();

	SetPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	// 値の初期化
	m_nLife = INITIAL_LIFE_PLAYER;
	m_state = STATE_NORMAL;
	m_jump = JUMPSTATE_NORMAL;

	if (m_pBody == nullptr)
	{// 体の生成
		m_pBody = CMotion::Create(BODY_PATH);
	}

	if (m_pCollisionCube == nullptr)
	{// 立方体の当たり判定
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		D3DXVECTOR3 vtxMax = { 5.0f,20.0f,5.0f };
		D3DXVECTOR3 vtxMin = { -5.0f,0.0f,-5.0f };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	if (m_pClsnAttack == nullptr)
	{// 球の当たり判定生成
		m_pClsnAttack = CCollisionSphere::Create(CCollision::TAG_NONE, CCollision::TYPE_SPHERE, this);

		if (m_pClsnAttack != nullptr)
		{// 情報の設定
			m_pClsnAttack->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_pClsnAttack->SetRadius(0.0f);
		}
	}

	if (m_pClsnHit == nullptr)
	{// 被弾当たり判定生成
		m_pClsnHit = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_pClsnHit != nullptr)
		{// 情報の設定
			m_pClsnHit->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pClsnHit->SetRadius(1.0f);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayer::Uninit(void)
{
	if (m_pBody != nullptr)
	{// 体の破棄
		m_pBody->Uninit();
		m_pBody = nullptr;
	}

	if (m_pCollisionCube != nullptr)
	{// 当たり判定破棄
		m_pCollisionCube->Uninit();
		m_pCollisionCube = nullptr;
	}

	if (m_pClsnAttack != nullptr)
	{// 攻撃当たり判定破棄
		m_pClsnAttack->Uninit();
		m_pClsnAttack = nullptr;
	}

	if (m_pClsnHit != nullptr)
	{// 被弾当たり判定破棄
		m_pClsnHit->Uninit();
		m_pClsnHit = nullptr;
	}

	if (m_pPlayer != nullptr)
	{// 自身のポインタを空にする
		m_pPlayer = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	// 前回の位置を保存
	m_posOld = m_pos;

	// 状態管理
	ManageState();

	// 操作処理
	Input();

	// モーションの管理
	ManageMotion();

	// 目標方向を向く処理
	RotDest();

	// 位置に移動量を反映
	m_pos += m_move;

	// 当たり判定管理
	ManageCollision();

	if (m_pBody != nullptr)
	{// 体の追従
		m_pBody->SetPosition(m_pos);
		m_pBody->SetRot(m_rot);
	}

	// 移動量減衰
	m_move.x *= MOVE_FACT;
	m_move.y -= GRAVITY;
}

//=====================================================
// 状態管理
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_state)
	{
	case CPlayer::STATE_NORMAL:
		break;
	case CPlayer::STATE_DAMAGE:

		m_nCntState++;

		if (m_nCntState >= TIME_DAMAGE)
		{
			m_state = STATE_NORMAL;

			if (m_pBody != nullptr)
			{
				m_pBody->ResetAllCol();
			}

			m_nCntState = 0;
		}

		break;
	default:
		break;
	}
}

//=====================================================
// 操作処理
//=====================================================
void CPlayer::Input(void)
{
	// 入力情報入手
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 移動操作
	InputMove();

	// 攻撃操作
	InputAttack();

	// カメラ操作
	InputCamera();
}

//=====================================================
// 移動操作
//=====================================================
void CPlayer::InputMove(void)
{
	// 情報入手
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputMouse *pMouse = CManager::GetMouse();
	CInputJoypad *pJoypad = CManager::GetJoypad();

	if (pKeyboard == nullptr || pMouse == nullptr)
	{
		return;
	}

	// 変数宣言
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecStick;
	int nMotion = m_pBody->GetMotion();

	if (nMotion != MOTION_ATTACK &&
		nMotion != MOTION_ATTACKTURN)
	{// 攻撃中でなければ
		if (nMotion != MOTION_PARRY ||
			m_jump > JUMPSTATE_NONE)
		{// 地上でパリィしてなければ移動
			if (pKeyboard->GetPress(DIK_A))
			{// 左移動
				move.x -= SPEED_MOVE;
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (pKeyboard->GetPress(DIK_D))
			{// 右移動
				move.x += SPEED_MOVE;
				m_rotDest.y = -D3DX_PI * 0.5f;
			}

			// ジャンプ操作
			if (m_jump == JUMPSTATE_NONE)
			{
				if (pKeyboard->GetTrigger(DIK_SPACE))
				{
					move.y += JUMP_POW;

					m_jump = JUMPSTATE_NORMAL;

					SetMotion(MOTION_JUMP);

					CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

					if (pAnim3D != nullptr)
					{
						D3DXVECTOR3 posEffect = GetPosition();
						posEffect.y += 15.0f;
						posEffect.x += move.x;
						posEffect.z -= 5.0f;

						pAnim3D->CreateEffect(posEffect, CAnimEffect3D::TYPE_JUMP);
					}
				}
			}

			// 移動量加算
			SetMove(GetMove() + move);
		}
	}

	if (pKeyboard->GetTrigger(DIK_G))
	{
		CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

		if (pAnim3D != nullptr)
		{
			pAnim3D->CreateEffect(GetPosition(), CAnimEffect3D::TYPE_FLASH);
		}
	}
}

//=====================================================
// 攻撃操作
//=====================================================
void CPlayer::InputAttack(void)
{
	// 情報入手
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputMouse *pMouse = CManager::GetMouse();
	CInputJoypad *pJoypad = CManager::GetJoypad();

	if (pKeyboard == nullptr || pMouse == nullptr)
	{
		return;
	}

	if (pMouse->GetTrigger(CInputMouse::BUTTON_LMB))
	{// 攻撃
		if (m_jump == JUMPSTATE_NORMAL)
		{// 空中攻撃
			SetMotion(MOTION_AIRATTACK);

			D3DXVECTOR3 move = { GetMove().x,ATTACK_JUMP,GetMove().z };

			// 移動量加算
			SetMove(move);

			m_jump = JUMPSTATE_ATTACK;
		}
		else if(m_jump == JUMPSTATE_NONE)
		{// 地上攻撃
			if (m_pBody->GetMotion() == MOTION_ATTACK || m_pBody->GetMotion() == MOTION_ATTACKTURN)
			{
				m_bAttack = true;
			}
			else
			{
				SetMotion(MOTION_ATTACK);

				m_bAttack = false;
			}
		}
	}

	if (m_pBody != nullptr)
	{
		if (m_pBody->IsFinish())
		{// 連撃の処理
			if (m_bAttack == true)
			{
				if (m_pBody->GetMotion() == MOTION_ATTACK)
				{
					SetMotion(MOTION_ATTACKTURN);

					m_bAttack = false;
				}
				else
				{
					SetMotion(MOTION_ATTACK);

					m_bAttack = false;
				}
			}
		}

		if (pMouse->GetTrigger(CInputMouse::BUTTON_RMB) &&
			m_pBody->GetMotion() != MOTION_PARRY)
		{// パリィ
			Parry();
		}
	}
}

//=====================================================
// パリィ
//=====================================================
void CPlayer::Parry(void)
{
	SetMotion(MOTION_PARRY);

	if (m_pClsnAttack == nullptr)
	{// 判定のエラー
		return;
	}

	CUniversal *pUniversal = CManager::GetUniversal();

	D3DXMATRIX mtx;
	D3DXVECTOR3 pos;
	bool bHit = false;

	pUniversal->SetOffSet(&mtx, *m_pBody->GetMatrix(), m_offsetParry);

	pos =
	{
		mtx._41,
		mtx._42,
		mtx._43
	};

	// 位置設定
	m_pClsnAttack->SetPosition(pos);

	// 半径の設定
	m_pClsnAttack->SetRadius(m_fRadiusParry);

#ifdef _DEBUG
	CEffect3D::Create(pos, m_fRadiusParry, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif

	// 命中したかの判定
	bHit = m_pClsnAttack->SphereCollision(CCollision::TAG_ENEMYBULLET);

	// 命中したオブジェクトの取得
	CObject *pObj = m_pClsnAttack->GetOther();

	if (bHit == true && pObj != nullptr)
	{//	パリィ成功
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR3 posTarget;

		pos = pObj->GetPosition();

		// 敵の取得
		CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

		CEnemy *pEnemy = nullptr;
		CEnemy *pLockEnemy = nullptr;
		float fLengthDest = FLT_MAX;

		if (pEnemyManager != nullptr)
		{
			pEnemy = pEnemyManager->GetHead();
		}

		int nNum = CEnemy::GetNumAll();

		while (pEnemy != nullptr)
		{
			// 次のアドレスを保存
			CEnemy *pEnemyNext = pEnemy->GetNext();

			// 差分ベクトルから移動量を設定
			posTarget = pEnemy->GetPosition();

			// プレイヤーとの距離を測る
			D3DXVECTOR3 vecDiff;
			vecDiff = posTarget - pos;

			float fLength = D3DXVec3Length(&vecDiff);
			
			if (fLength < fLengthDest)
			{// 近い敵の更新
				fLengthDest = fLength;
				pLockEnemy = pEnemy;
			}

			// 次のアドレスを代入
			pEnemy = pEnemyNext;
		}

		// 差分ベクトルから移動量を設定
		posTarget = pLockEnemy->GetPosition();

		move = posTarget - pos;

		D3DXVec3Normalize(&move, &move);

		move *= BULLET_SPEED;

		pObj->Uninit();

		// 弾いた弾の射出
		CBullet::Create(pos, move, 200, CBullet::TYPE_PLAYER,false, BULLET_SIZE);

		CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

		if (pAnim3D != nullptr)
		{
			pAnim3D->CreateEffect(pos, CAnimEffect3D::TYPE_SLASH);
			pAnim3D->CreateEffect(pos, CAnimEffect3D::TYPE_FLASH);
		}

		CParticle::Create(pos,CParticle::TYPE_FLASH);
	}
}

//=====================================================
// モーションの管理
//=====================================================
void CPlayer::ManageMotion(void)
{
	if (m_pBody == nullptr)
	{
		return;
	}

	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	bool bFinish = m_pBody->IsFinish();
	int nMotion = m_pBody->GetMotion();

	if (m_jump == JUMPSTATE_NONE)
	{
		if (m_bAttack == false &&
			(m_pBody->GetMotion() != MOTION_ATTACK && m_pBody->GetMotion() != MOTION_ATTACKTURN && m_pBody->GetMotion() != MOTION_PARRY))
		{// 移動モーション
			if (move.x * move.x > LINE_STOP * LINE_STOP)
			{// ある程度動いていれば歩きモーション
				SetMotion(MOTION_MOVE);
			}
			else
			{// 待機モーションへ移行
				SetMotion(MOTION_NEUTRAL);

				m_nCntAfterImage = 0;
			}
		}
		else
		{// 攻撃モーション管理
			if (bFinish == true)
			{
				SetMotion(MOTION_NEUTRAL);
			}
		}
	}
	else
	{
		if (move.y < 0.0f && 
			(nMotion == MOTION_AIRATTACK && bFinish == false) == false &&
			(nMotion == MOTION_PARRY && bFinish == false) == false)
		{// 落下モーション
			SetMotion(MOTION_FALL);
		}
	}

	// 移動量の計算
	float fSpeed = D3DXVec3Length(&move);

	if (fSpeed * fSpeed > LINE_STOP * LINE_STOP)
	{
		m_nCntAfterImage++;

		if (m_nCntAfterImage >= TIME_AFTERIMAGE)
		{
			// 残像の生成
			m_pBody->SetAfterImage(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20);

			m_nCntAfterImage = 0;
		}
	}
}

//=====================================================
// 当たり判定の管理
//=====================================================
void CPlayer::ManageCollision(void)
{
	bool bLandFloor = false;
	bool bLandBlock = false;

	CFade *pFade = CManager::GetFade();

	if (m_pCollisionCube != nullptr)
	{// 当たり判定の管理

		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// 押し出しの当たり判定
		bLandBlock = m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);

		if (m_jump != JUMPSTATE_NONE && 
			bLandBlock)
		{
			m_jump = JUMPSTATE_NONE;
		}
		else if(bLandBlock == false && 
			m_jump == JUMPSTATE_NONE)
		{
			m_jump = JUMPSTATE_NORMAL;
		}
	}

	if (m_pClsnHit != nullptr)
	{
		if (m_pBody != nullptr)
		{
			if (m_pBody->GetParts(0) != nullptr)
			{
				D3DXMATRIX mtx = *m_pBody->GetParts(0)->m_pParts->GetMatrix();
				D3DXVECTOR3 pos =
				{
					mtx._41,
					mtx._42,
					mtx._43,
				};

				m_pClsnHit->SetPositionOld(m_pClsnHit->GetPosition());
				m_pClsnHit->SetPosition(pos);

				if (m_pClsnHit->SphereCollision(CCollision::TAG_ENEMY))
				{
					Hit(5.0f);
				}
			}
		}
	}

	// 落下死判定=============
	if (m_pos.y <= -190.0f)
	{
		m_pos = 
		{
			0.0f,
			1.0f,
			0.0f
		};

		m_posOld = m_pos;

		m_move =
		{
			0.0f,
			0.0f,
			0.0f
		};
	}
	// =======================

	// 攻撃判定の管理
	ManageAttack();
}

//=====================================================
// 攻撃判定の管理
//=====================================================
void CPlayer::ManageAttack(void)
{
	if (m_pClsnAttack == nullptr)
	{// 判定のエラー
		return;
	}

	if (m_pBody == nullptr)
	{// モーションのエラー
		return;
	}

	CUniversal *pUniversal = CManager::GetUniversal();

	for (int i = 0; i < m_nNumAttack; i++)
	{
		if (m_pBody->GetMotion() == m_pAttackInfo[i].nIdxMotion)
		{// 攻撃モーション中の判定
			int nFrame = m_pBody->GetFrame();
			int nKey = m_pBody->GetKey();
			D3DXVECTOR3 pos;

			if (nFrame == m_pAttackInfo[i].nFrame && nKey == m_pAttackInfo[i].nKey)
			{// 当たり判定の設定
				bool bHit = false;
				D3DXMATRIX mtx;

				pUniversal->SetOffSet(&mtx, *m_pBody->GetMatrix(), m_pAttackInfo[i].pos);

				pos =
				{
					mtx._41,
					mtx._42,
					mtx._43
				};

				// 位置設定
				m_pClsnAttack->SetPosition(pos);
				
				// 半径の設定
				m_pClsnAttack->SetRadius(m_pAttackInfo[i].fRadius);

#ifdef _DEBUG
				CEffect3D::Create(pos, m_pAttackInfo[i].fRadius, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif
				// 命中したかの判定
				bHit = m_pClsnAttack->SphereCollision(CCollision::TAG_ENEMY);
				
				// 命中したオブジェクトの取得
				CObject *pObj = m_pClsnAttack->GetOther();

				if (bHit == true && pObj != nullptr)
				{// 命中時のヒット処理
					CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

					if (pAnim3D != nullptr)
					{
						pAnim3D->CreateEffect(pObj->GetPosition(), CAnimEffect3D::TYPE_FLASH);
					}

					pObj->Hit(5.0f);
				}
			}
		}
	}
}

//=====================================================
// 目標方向を向く処理
//=====================================================
void CPlayer::RotDest(void)
{
	// 変数宣言
	D3DXVECTOR3 vecDest;
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = m_rotDest.y - rot.y;

	// 角度の修正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	// 角度補正
	SetRot(D3DXVECTOR3(rot.x, rot.y + fRotDiff * ROLL_FACT, rot.z));

	// 角度の修正
	rot = GetRot();

	if (GetRot().y > D3DX_PI)
	{
		// 角度補正
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y - 6.28f, GetRot().z));
	}
	if (GetRot().y < -D3DX_PI)
	{
		// 角度補正
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y + 6.28f, GetRot().z));
	}
}

//=====================================================
// カメラ操作
//=====================================================
void CPlayer::InputCamera(void)
{

}

//=====================================================
// ヒット処理
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_state == STATE_NORMAL)
	{
		m_nLife -= (int)fDamage;

		if (m_nLife <= 0)
		{// 死亡判定
			m_nLife = 0;

			Uninit();
		}
		else
		{
			m_state = STATE_DAMAGE;

			CManager::GetCamera()->SetQuake(0.03f, 0.03f, 10);

			if (m_pBody != nullptr)
			{
				m_pBody->SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
}

//=====================================================
// モーション設定
//=====================================================
void CPlayer::SetMotion(MOTION motion)
{
	if (m_pBody == nullptr)
	{
		return;
	}

	if (m_pBody->GetMotion() != motion)
	{
		// モーション設定
		m_pBody->SetMotion(motion);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CPlayer::Draw(void)
{
	if (m_pBody != nullptr)
	{
		m_pBody->SetMatrix();
	}

#ifdef _DEBUG
	CManager::GetDebugProc()->Print("\nプレイヤーの位置：[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetDebugProc()->Print("\nプレイヤー体力[%d]", m_nLife);
	CManager::GetDebugProc()->Print("\nモーション[%d]", m_pBody->GetMotion());
	CManager::GetDebugProc()->Print("\n攻撃[%d]", m_bAttack);
	CManager::GetDebugProc()->Print("\nリセット[F3]");
#else
	CManager::GetDebugProc()->Print("\n\n\n\n\n\n\n\n\n\n\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("// プレイヤー基本操作\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("[WASD]移動\n");
	CManager::GetDebugProc()->Print("[LSHIFT + 移動]ダッシュ\n");
	CManager::GetDebugProc()->Print("[SPACE]ジャンプ\n");
	CManager::GetDebugProc()->Print("[LMB]射撃\n");
	CManager::GetDebugProc()->Print("[RMB]ズーム\n");
	CManager::GetDebugProc()->Print("\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("// 射撃の種類\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("[短押し]単発撃ち\n");
	CManager::GetDebugProc()->Print("[長押し]チャージショット\n");
	CManager::GetDebugProc()->Print("[ダブルクリック→長押し]連射\n");
#endif
}

//=====================================================
// 生成処理
//=====================================================
CPlayer *CPlayer::Create(void)
{
	if (m_pPlayer == nullptr)
	{// インスタンス生成
		m_pPlayer = new CPlayer;

		// 初期化処理
		m_pPlayer->Init();
	}

	return m_pPlayer;
}

//=====================================================
// 情報読込
//=====================================================
void CPlayer::Load(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntAttack = 0;

	// ファイルから読み込む
	FILE *pFile = fopen(PARAM_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_ATTACK") == 0)
			{// 攻撃判定読込開始
				// 攻撃判定数読込
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumAttack);
				
				if (m_pAttackInfo == nullptr)
				{// 判定情報の生成
					m_pAttackInfo = new AttackInfo[m_nNumAttack];

					for (int i = 0; i < m_nNumAttack; i++)
					{// 情報のクリア
						ZeroMemory(&m_pAttackInfo[i], sizeof(AttackInfo));
					}
				}
				else
				{
					break;
				}

				if (m_pAttackInfo == nullptr)
				{// 生成できなかった場合
					break;
				}

				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "ATTACKSET") == 0)
					{// パラメーター読込開始
						while (true)
						{
							// 文字読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "MOTION") == 0)
							{// モーションの種類
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_pAttackInfo[nCntAttack].nIdxMotion);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//位置読み込み
								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &m_pAttackInfo[nCntAttack].pos[nCntPos]);
								}
							}

							if (strcmp(cTemp, "KEY") == 0)
							{// キーの番号
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_pAttackInfo[nCntAttack].nKey);
							}

							if (strcmp(cTemp, "FRAME") == 0)
							{// フレーム番号
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_pAttackInfo[nCntAttack].nFrame);
							}

							if (strcmp(cTemp, "RADIUS") == 0)
							{// 半径
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_pAttackInfo[nCntAttack].fRadius);
							}

							if (strcmp(cTemp, "END_ATTACKSET") == 0)
							{// パラメーター読込終了
								nCntAttack++;

								break;
							}
						}
					}

					if (m_nNumAttack <= nCntAttack)
					{
						break;
					}
				}
			}

			if (strcmp(cTemp, "PARRYSET") == 0)
			{// 攻撃判定読込開始
				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "POS") == 0)
					{//位置読み込み
						fscanf(pFile, "%s", &cTemp[0]);

						for (int i = 0; i < 3; i++)
						{
							fscanf(pFile, "%f", &m_offsetParry[i]);
						}
					}

					if (strcmp(cTemp, "RADIUS") == 0)
					{// 半径
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%f", &m_fRadiusParry);
					}
					
					if (strcmp(cTemp, "END_PARRYSET") == 0)
					{// パラメーター読込終了
						nCntAttack++;

						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// 終了条件
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}