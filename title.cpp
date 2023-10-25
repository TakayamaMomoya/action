//*****************************************************
//
// タイトル処理[title.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "title.h"
#include "object.h"
#include "inputManager.h"
#include "manager.h"
#include "motion.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "skybox.h"
#include "edit.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define LOGO_PATH	"data\\TEXTURE\\UI\\logo000.png"	// ロゴのパス
#define START_PATH	"data\\TEXTURE\\UI\\start.png"	// スタート表示のパス
#define START_WIDTH	(200.0f)	// スタート表示の幅
#define START_HEIGHT	(50.0f)	// スタート表示の高さ
#define DEST_WIDTH	(500.0f)	// スタート表示の幅
#define CHANGE_FACT	(0.1f)	// 変化する係数
#define ALPHA_CHANGE	(0.05f)	// α値の変化量

//=====================================================
// コンストラクタ
//=====================================================
CTitle::CTitle()
{
	m_pStart = nullptr;
	m_state = STATE_NONE;
	m_pMotion = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTitle::Init(void)
{
	// ロゴの生成
	CObject2D *pObject2D = CObject2D::Create(7);
	pObject2D->SetSize(875.0f * 0.45f, 320.0f * 0.45f);
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.7f, 200.0f, 0.0f));

	int nIdx = CManager::GetTexture()->Regist(LOGO_PATH);
	pObject2D->SetIdxTexture(nIdx);
	pObject2D->SetVtx();

	// スタート表示の生成
	m_pStart = CObject2D::Create(7);

	if (m_pStart != nullptr)
	{
		m_pStart->SetSize(START_WIDTH, START_HEIGHT);
		m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f));

		int nIdx = CManager::GetTexture()->Regist(START_PATH);
		m_pStart->SetIdxTexture(nIdx);
		m_pStart->SetVtx();
	}

	// スカイボックスの生成
	CSkybox::Create();

	// ブロック配置読込
	CBlock::Load("data\\MAP\\map00.bin");

	m_pMotion = CMotion::Create("data\\MOTION\\rayleigh.txt");

	if (m_pMotion != nullptr)
	{
		m_pMotion->SetPosition(D3DXVECTOR3(10.0f, 35.0f, 460.0f));
		m_pMotion->SetRot(D3DXVECTOR3(0.0f, 0.7f, 0.0f));
		m_pMotion->SetMotion(9);
		m_pMotion->InitPose(9);
		m_pMotion->SetMatrix();
	}

	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetTitle();
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTitle::Uninit(void)
{
	// オブジェクト全破棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CTitle::Update(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	// シーンの更新
	CScene::Update();
	
	CFade *pFade = CManager::GetFade();

	if (m_state == STATE_NONE)
	{
		if (pInputManager != nullptr)
		{
			if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
			{// フェード
				if (m_pMotion != nullptr)
				{
					if (m_pMotion->GetMotion() != 10)
					{
						m_pMotion->SetMotion(10);

						m_state = STATE_MOTION;
					}
				}
			}
		}
	}
	else if(m_state == STATE_OUT)
	{
		// スタート表示の管理
		ManageStart();
	}

	if (m_state == STATE_MOTION)
	{
		if (m_pMotion != nullptr)
		{
			if (m_pMotion->IsFinish())
			{
				if (pFade != nullptr)
				{
					CGame::SetProgress(0);

					pFade->SetFade(CScene::MODE_GAME);
				}
			}
		}
	}
}

//=====================================================
// スタート表示の管理
//=====================================================
void CTitle::ManageStart(void)
{
	if (m_pStart == nullptr)
	{
		return;
	}

	float fWidth = m_pStart->GetWidth();
	float fHeight = m_pStart->GetHeight();
	float fDiffWidth;
	float fDiffHeight;

	// 減少分の計算
	fDiffWidth = (DEST_WIDTH - fWidth) * CHANGE_FACT;
	fDiffHeight = (0.0f - fHeight) * CHANGE_FACT;

	// 透明にする
	D3DXCOLOR col = m_pStart->GetCol();

	col.a -= ALPHA_CHANGE;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	m_pStart->SetCol(col);

	// サイズ設定
	m_pStart->SetSize(fWidth + fDiffWidth, fHeight + fDiffHeight);
	m_pStart->SetVtx();
}

//=====================================================
// 描画処理
//=====================================================
void CTitle::Draw(void)
{

}