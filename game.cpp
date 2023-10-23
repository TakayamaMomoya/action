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
#include "enemy.h"
#include "skybox.h"
#include "enemyManager.h"
#include "animEffect3D.h"
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"

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
#define BOSS_LINE	(2737.0f)	// ボス戦に突入するライン
#define CHECKPOINT_PATH "data\\MAP\\checkpoint.txt"	// チェックポイントデータのパス

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CScore *CGame::m_pScore = nullptr;	// スコアのポインタ
CTimer *CGame::m_pTimer = nullptr;	// タイマーのポインタ
CGame::STATE CGame::m_state = STATE_NONE;
int CGame::m_nProgress = 0;

//=====================================================
// コンストラクタ
//=====================================================
CGame::CGame()
{
	m_pPosCheckPoint = nullptr;
	m_nNumCheckPoint = 0;
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
	m_state = STATE_NORMAL;

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
		pCamera->SetDist(180.0f);
	}

	// リスポーン地点設定
	LoadCheckPoint();

	// プレイヤー生成
	CPlayer *pPlayer = CPlayer::Create();

	if (pPlayer != nullptr && m_pPosCheckPoint != nullptr)
	{// スポーン地点の設定
		pPlayer->SetPosition(m_pPosCheckPoint[m_nProgress]);
	}

	// スカイボックス
	CSkybox::Create();

	// ブロック配置読込
	CBlock::Load();

	// 敵マネージャー生成
	CEnemyManager::Create();

	// ３Dエフェクト管理生成
	CAnimEffect3D::Create();

	// UIマネージャー
	CUIManager::Create();

#ifdef _DEBUG
	//CEdit::Create();
#endif

	m_bStop = false;

	return S_OK;
}

//=====================================================
// チェックポイントの読込
//=====================================================
void CGame::LoadCheckPoint(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntPos = 0;

	// ファイルから読み込む
	FILE *pFile = fopen(CHECKPOINT_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_CHECKPOINT") == 0)
			{// チェックポイント数読込
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumCheckPoint);

				if (m_pPosCheckPoint == nullptr)
				{// 判定情報の生成
					m_pPosCheckPoint = new D3DXVECTOR3[m_nNumCheckPoint];

					for (int i = 0; i < m_nNumCheckPoint; i++)
					{// 情報のクリア
						ZeroMemory(&m_pPosCheckPoint[i], sizeof(D3DXVECTOR3));
					}
				}
				else
				{
					break;
				}

				if (m_pPosCheckPoint == nullptr)
				{// 生成できなかった場合
					break;
				}

				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "CHECKPOINTSET") == 0)
					{// パラメーター読込開始
						while (true)
						{
							// 文字読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "POS") == 0)
							{//位置読み込み
								fscanf(pFile, "%s", &cTemp[0]);

								for (int i = 0; i < 3; i++)
								{
									fscanf(pFile, "%f", &m_pPosCheckPoint[nCntPos][i]);
								}
							}

							if (strcmp(cTemp, "END_CHECKPOINTSET") == 0)
							{// パラメーター読込終了
								nCntPos++;

								break;
							}
						}
					}

					if (m_nNumCheckPoint <= nCntPos)
					{
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

	if (m_pPosCheckPoint != nullptr)
	{
		delete[] m_pPosCheckPoint;
		m_pPosCheckPoint = nullptr;
	}

	// ブロック情報削除
	CBlock::DeleteAll();

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
	//CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	CFade *pFade = CManager::GetFade();

	if (m_bStop == false)
	{
		// シーンの更新
		CScene::Update();
	}
	else
	{
		CEdit *pEdit = CEdit::GetInstatnce();

		if (pEdit != nullptr)
		{
			pEdit->Update();
		}
	}

	// カメラ更新
	UpdateCamera();

	// 状態管理
	ManageState();

	//if (pKeyboard != nullptr)
	//{
	//	if (pKeyboard->GetTrigger(DIK_RETURN))
	//	{
	//		if (pFade != nullptr)
	//		{
	//			//pFade->SetFade(CScene::MODE_RANKING);
	//		}
	//	}
	//}

#ifdef _DEBUG
	Debug();
#endif
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

	if (m_bStop == false)
	{
		if (m_state == STATE_NORMAL)
		{
			// プレイヤーの追従
			pCamera->FollowPlayer();
		}
		else if (m_state == STATE_BOSS)
		{
			// ボス戦の動き
			pCamera->BossBattle();
		}
	}
	else
	{
		// 操作
		pCamera->Control();
	}
}

//=====================================================
// 状態管理
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CManager::GetFade();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
	{
		// プレイヤー取得
		CPlayer *pPlayer = nullptr;
		pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 pos = pPlayer->GetPosition();

			if (pos.x >= BOSS_LINE)
			{// ボス戦へ移行
				CEnemyManager *pEnemyManager = nullptr;

				pEnemyManager = CEnemyManager::GetInstance();

				if (pEnemyManager != nullptr)
				{
					pEnemyManager->CreateEnemy(D3DXVECTOR3(BOSS_LINE,190.0f,0.0f), CEnemy::TYPE_BOSS);
				}

				m_state = STATE_BOSS;
			}

			if (m_nProgress < m_nNumCheckPoint - 1)
			{
				if (pos.x >= m_pPosCheckPoint[m_nProgress + 1].x)
				{// チェックポイントの設定
					m_nProgress++;
				}
			}
		}
	}
		break;
	case CGame::STATE_BOSS:
		break;
	case CGame::STATE_RESULT:
		break;
	case CGame::STATE_END:
		
		if(pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// デバッグ処理
//=====================================================
void CGame::Debug(void)
{
	// 入力取得
	//CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//if (pKeyboard == nullptr)
	//{
	//	return;
	//}

	//if (pKeyboard->GetTrigger(DIK_F))
	//{
	//	m_bStop = m_bStop ? false : true;
	//}
}

//=====================================================
// 描画処理
//=====================================================
void CGame::Draw(void)
{
	CManager::GetDebugProc()->Print("\n進行状況：[%d]", m_nProgress);
}