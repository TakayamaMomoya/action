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

//*****************************************************
// マクロ定義
//*****************************************************
#define BODY_PATH	"data\\MOTION\\rayleigh.txt"	// 見た目のパス
#define SPEED_MOVE	(0.3f)	// 移動速度
#define GRAVITY	(0.09f)	// 重力
#define JUMP_POW	(3.0f)	// ジャンプ力
#define MOVE_FACT	(0.8f)	// 移動量減衰
#define ROLL_FACT	(0.2f)	// 回転係数
#define LINE_STOP	(0.3f)	// 動いてる判定のしきい値
#define TIME_AFTERIMAGE	(4)	// 残像を出す頻度

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
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_rotDest = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_bJump = false;
	m_bSprint = false;
	m_pBody = nullptr;
	m_pCollisionCube = false;
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
	// 値の初期化
	m_nLife = INITIAL_LIFE_PLAYER;
	
	if (m_pBody == nullptr)
	{// 体の生成
		m_pBody = CMotion::Create(BODY_PATH);
	}

	if (m_pCollisionCube == nullptr)
	{// 立方体の当たり判定
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		D3DXVECTOR3 vtxMax = { 0.1f,3.0f,0.1f };
		D3DXVECTOR3 vtxMin = { -0.1f,0.0f,-0.1f };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
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
// 操作処理
//=====================================================
void CPlayer::Input(void)
{
	// 入力情報入手
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 移動操作
	InputMove();

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
	if (m_bJump == false)
	{
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{// 右移動
			move.y += JUMP_POW;

			m_bJump = true;

			SetMotion(MOTION_JUMP);
		}
	}

	if (pMouse->GetTrigger(CInputMouse::BUTTON_LMB))
	{// 攻撃
		SetMotion(MOTION_ATTACK);
	}

	// 移動量加算
	SetMove(GetMove() + move);
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

	if (m_bJump == false)
	{
		if (m_pBody->GetMotion() != MOTION_ATTACK)
		{
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
	}
	else
	{
		if (move.y < 0.0f)
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

	if (m_pCollisionCube != nullptr)
	{// 当たり判定の管理

		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// 押し出しの当たり判定
		bLandBlock = m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);
	}

	// 仮の床判定=============
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
		bLandFloor = true;
	}
	// =======================

	if (bLandBlock || bLandFloor)
	{
		m_bJump = false;
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
	m_nLife -= (int)fDamage;

	if (m_nLife <= 0)
	{// 死亡判定
		m_nLife = 0;

		Uninit();
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
// テクスチャ破棄
//=====================================================
void CPlayer::Unload(void)
{

}