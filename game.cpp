//*****************************************************
//
// ゲーム処理[game.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "score.h"
#include "timer.h"
#include "object.h"
#include "universal.h"
#include "particle.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "fade.h"
#include "camera.h"
#include "effect3D.h"
#include "objectmanager.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "field.h"
#include "block.h"
#include "edit.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define TRANS_TIME	(60)	// 終了までの余韻のフレーム数
#define LIMIT_LENGTH	(10000)	// 移動制限の距離
#define LIMIT_WIDTH	(100)	// 推定プレイヤーの幅
#define LIMIT_HEIGHT	(2000)	// 制限高度
#define BONUS_TIME	(40)	// ボーナスが付与される最低限のタイム
#define RATE_BONUS	(0.015f)	// 1秒当たりのタイムボーナス
#define RESULT_TIME	(5)	// リザルト画面表示までのラグ

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CScore *CGame::m_pScore = nullptr;	// スコアのポインタ
CTimer *CGame::m_pTimer = nullptr;	// タイマーのポインタ
CGame::STATE CGame::m_state = STATE_NONE;

//=====================================================
// コンストラクタ
//=====================================================
CGame::CGame()
{

}

//=====================================================
// デストラクタ
//=====================================================
CGame::~CGame()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGame::Init(void)
{
	CObjectManager *pObjManager = CManager::GetObjectManager();

	if (m_pScore == nullptr)
	{// スコア生成
		m_pScore = CScore::Create();
	}

	if (m_pScore != nullptr)
	{// スコア初期化
		m_pScore->Init();
	}

	if (m_pTimer == nullptr)
	{// タイマー生成
		m_pTimer = CTimer::Create();
	}

	// カメラ距離の設定
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetDist(100.0f);
	}

	// プレイヤーの追従
	pCamera->FollowPlayer();

	// プレイヤー生成
	CPlayer::Create();

	//CField::Create();

	// ブロック配置読込
	CBlock::Load();

#ifdef _DEBUG

	CEdit::Create();

#endif

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGame::Uninit(void)
{
	if (m_pScore != nullptr)
	{// スコアの終了・破棄
		m_pScore->Uninit();

		m_pScore = nullptr;
	}

	if (m_pTimer != nullptr)
	{// タイマーの終了・破棄
		m_pTimer->Uninit();

		m_pTimer = nullptr;
	}

	// オブジェクト全棄
	CObject::ReleaseAll();
}

//=====================================================
// スコア終了処理
//=====================================================
void CGame::ReleaseScore(void)
{
	if (m_pScore != nullptr)
	{// スコアの終了・破棄
		m_pScore = nullptr;
	}
}

//=====================================================
// タイマー終了処理
//=====================================================
void CGame::ReleaseTimer(void)
{
	if (m_pTimer != nullptr)
	{// スコアの終了・破棄
		m_pTimer = nullptr;
	}
}

//=====================================================
// 更新処理
//=====================================================
void CGame::Update(void)
{
	// 入力取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad *pJoypad = CManager::GetJoypad();

	CFade *pFade = CManager::GetFade();

	// シーンの更新
	CScene::Update();

	// カメラ更新
	UpdateCamera();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			if (pFade != nullptr)
			{
				//pFade->SetFade(CScene::MODE_RANKING);
			}
		}
	}
}

//=====================================================
// カメラの更新
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	// プレイヤーの追従
	pCamera->FollowPlayer();
}

//=====================================================
// 描画処理
//=====================================================
void CGame::Draw(void)
{

}