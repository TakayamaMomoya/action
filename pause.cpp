//*****************************************************
//
// ポーズの処理[pause.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "pause.h"
#include "manager.h"
#include "object2D.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "texture.h"
#include "fade.h"
#include "game.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define MENU_WIDTH	(200.0f)	// 項目の幅
#define MENU_HEIGHT	(50.0f)	// 項目の高さ
#define MOVE_FACT	(0.15f)	// 移動速度
#define LINE_ARRIVAL	(90.0f)	// 到着したとされるしきい値
#define LINE_UNINIT	(3.0f)	// 終了するまでのしきい値

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CPause *CPause::m_pPause = nullptr;	// 自身のポインタ

//====================================================
// コンストラクタ
//====================================================
CPause::CPause()
{
	m_menu = MENU_RESUME;
	m_state = STATE_NONE;
	ZeroMemory(&m_apMenu[0], sizeof(m_apMenu));
	ZeroMemory(&m_aPosDest[0], sizeof(D3DXVECTOR3) * MENU_MAX);
}

//====================================================
// デストラクタ
//====================================================
CPause::~CPause()
{

}

//====================================================
// 生成処理
//====================================================
CPause *CPause::Create(void)
{
	if (m_pPause == nullptr)
	{
		m_pPause = new CPause;

		if (m_pPause != nullptr)
		{
			m_pPause->Init();
		}
	}

	return m_pPause;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CPause::Init(void)
{
	// ゲームを停止する
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->EnableStop(true);
	}

	char *pPath[MENU_MAX] = 
	{// メニュー項目のパス
		"data\\TEXTURE\\UI\\menu_resume.png",
		"data\\TEXTURE\\UI\\menu_retry.png",
		"data\\TEXTURE\\UI\\menu_return.png",
		"data\\TEXTURE\\UI\\menu_quit.png",
	};

	int nIdxTexture;

	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{// メニュー項目のポリゴンを生成
		if (m_apMenu[nCntMenu] == nullptr)
		{
			m_apMenu[nCntMenu] = CObject2D::Create(6);

			if (m_apMenu[nCntMenu] != nullptr)
			{
				// ポリゴンの設定
				m_apMenu[nCntMenu]->SetPosition(D3DXVECTOR3(-MENU_WIDTH, SCREEN_HEIGHT * 0.1f + MENU_HEIGHT * nCntMenu * 2, 0.0f));
				m_aPosDest[nCntMenu] = m_apMenu[nCntMenu]->GetPosition();

				m_apMenu[nCntMenu]->SetSize(MENU_WIDTH, MENU_HEIGHT);

				m_apMenu[nCntMenu]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

				// テクスチャの設定
				nIdxTexture = CTexture::GetInstance()->Regist(pPath[nCntMenu]);

				m_apMenu[nCntMenu]->SetIdxTexture(nIdxTexture);

				m_apMenu[nCntMenu]->SetVtx();
			}
		}
	}

	m_state = STATE_IN;

	m_aPosDest[0].x = MENU_WIDTH;

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CPause::Uninit(void)
{
	// ゲームを再開する
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->EnableStop(false);
	}

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{// メニュー項目の破棄
		if (m_apMenu[nCnt] != nullptr)
		{
			m_apMenu[nCnt]->Uninit();

			m_apMenu[nCnt] = nullptr;
		}
	}

	m_pPause = nullptr;

	Release();
}

//====================================================
// 更新処理
//====================================================
void CPause::Update(void)
{
	// 状態管理
	ManageState();
}

//====================================================
// 状態管理
//====================================================
void CPause::ManageState(void)
{
	if (m_state != STATE_OUT)
	{
		Input();
	}

	// 終了フラグ用
	int nEnd = 0;

	// ポリゴンを目標位置に向かわせる
	for (int i = 0;i < MENU_MAX;i++)
	{
		if (m_apMenu[i] != nullptr)
		{
			D3DXVECTOR3 pos = m_apMenu[i]->GetPosition();
			D3DXVECTOR3 posOld = pos;
			D3DXVECTOR3 vecDiff = m_aPosDest[i] - pos;
			float fDiffOld = vecDiff.x;

			vecDiff *= MOVE_FACT;

			vecDiff += pos;

			m_apMenu[i]->SetPosition(vecDiff);

			m_apMenu[i]->SetVtx();

			float fDiff = m_aPosDest[i].x - vecDiff.x;

			if (fDiffOld * fDiffOld >= LINE_ARRIVAL * LINE_ARRIVAL &&
				fDiff * fDiff < LINE_ARRIVAL * LINE_ARRIVAL &&
				i < MENU_MAX - 1)
			{// 差分がしきい値より下になったら下のものを動かす
				if (m_state == STATE_IN)
				{
					m_aPosDest[i + 1].x = MENU_WIDTH;
				}
				else if (m_state == STATE_OUT)
				{
					m_aPosDest[i + 1].x = -MENU_WIDTH;
				}
			}

			if (fDiff * fDiff < LINE_UNINIT * LINE_UNINIT &&
				m_state == STATE_OUT)
			{// 終了のライン
				nEnd++;
			}
		}
	}

	if (nEnd == MENU_MAX - 1 &&
		m_state == STATE_OUT)
	{
		Uninit();
	}
}

//====================================================
// 操作処理
//====================================================
void CPause::Input(void)
{
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	CFade *pFade = CManager::GetFade();

	if (pFade == nullptr)
	{
		return;
	}
	else
	{
		if (pFade->GetState() != CFade::FADE_NONE)
		{
			return;
		}
	}

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_P))
	{// ポーズ解除、以降の操作を受け付けない
		m_state = STATE_OUT;
		m_aPosDest[0].x = -MENU_WIDTH;

		return;
	}

	if (m_apMenu[m_menu] != nullptr)
	{// 以前に選択してた項目を非選択色にする
		m_apMenu[m_menu]->SetCol(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	}

	// 項目切り替え
	if (pKeyboard->GetTrigger(DIK_S) || pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_DOWN, 0))
	{
		m_menu = (MENU)((m_menu + 1) % MENU_MAX);
	}

	if (pKeyboard->GetTrigger(DIK_W) || pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_UP, 0))
	{
		m_menu = (MENU)((m_menu + MENU_MAX - 1) % MENU_MAX);
	}

	if (m_apMenu[m_menu] != nullptr)
	{// 選択している項目の色変更
		m_apMenu[m_menu]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{// 選択項目にフェードする
		Fade(m_menu);
	}
}

//====================================================
// フェードする処理
//====================================================
void CPause::Fade(MENU menu)
{
	CFade *pFade = CManager::GetFade();

	if (pFade == nullptr)
	{
		return;
	}

	switch (menu)
	{
	case CPause::MENU_RESUME:

		m_state = STATE_OUT;
		m_aPosDest[0].x = -MENU_WIDTH;

		break;
	case CPause::MENU_RESTART:

		CGame::SetProgress(0);
		pFade->SetFade(CScene::MODE_GAME);

		break;
	case CPause::MENU_CHECKPOINT:

		pFade->SetFade(CScene::MODE_GAME);

		break;
	case CPause::MENU_QUIT:

		pFade->SetFade(CScene::MODE_TITLE);

		break;
	default:
		break;
	}
}

//====================================================
// 描画処理
//====================================================
void CPause::Draw(void)
{

}