//*****************************************************
//
// UIマネージャー[UIManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "inputkeyboard.h"
#include "UIManager.h"
#include "UI.h"
#include "life.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CUIManager *CUIManager::m_pUIManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CUIManager::CUIManager()
{
	m_pLife = nullptr;
	m_bDisp = false;
}

//=====================================================
// デストラクタ
//=====================================================
CUIManager::~CUIManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CUIManager *CUIManager::Create(void)
{
	if (m_pUIManager == nullptr)
	{// インスタンス生成
		m_pUIManager = new CUIManager;

		// 初期化処理
		m_pUIManager->Init();
	}

	return m_pUIManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CUIManager::Init(void)
{
	m_bDisp = true;

	// ライフの生成
	m_pLife = CLife::Create();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CUIManager::Uninit(void)
{
	m_pUIManager = nullptr;

	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		m_pLife = nullptr;
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CUIManager::Update(void)
{
#ifdef _DEBUG
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_1))
		{
			m_bDisp = m_bDisp ? false : true;
		}
	}

#endif
}

//=====================================================
// 描画処理
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}