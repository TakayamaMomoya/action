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

//*****************************************************
// マクロ定義
//*****************************************************
#define BODY_PATH	"data\\MOTION\\motionArms00.txt"	// 見た目のパス
#define SPEED_MOVE	(2.0f)	// 移動速度
#define GRAVITY	(0.98f)	// 重力
#define JUMP_POW	(1.2f)	// ジャンプ力
#define MOVE_FACT	(0.8f)	// 移動量減衰
#define ROLL_FACT	(0.2f)	// 回転係数

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	m_nLife = 0;
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_rotDest = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_bSprint = false;
	m_pBody = nullptr;
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

	// 目標方向を向く処理
	RotDest();

	// 位置に移動量を反映
	m_pos += m_move;

	if (m_pBody != nullptr)
	{// 体の追従
		m_pBody->SetPosition(m_pos);
		m_pBody->SetRot(m_rot);
	}

	// 移動量減衰
	m_move *= MOVE_FACT;
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

	// 移動量加算
	SetMove(GetMove() + move);
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
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{// インスタンス生成
		pPlayer = new CPlayer;

		// 初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=====================================================
// テクスチャ破棄
//=====================================================
void CPlayer::Unload(void)
{

}