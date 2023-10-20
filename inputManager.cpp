//*****************************************************
//
// 入力マネージャー[inputManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "inputManager.h"
#include "manager.h"
#include "inputjoypad.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CInputManager *CInputManager::m_pInputManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CInputManager::CInputManager()
{

}

//=====================================================
// デストラクタ
//=====================================================
CInputManager::~CInputManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CInputManager *CInputManager::Create(void)
{
	if (m_pInputManager == nullptr)
	{// インスタンス生成
		m_pInputManager = new CInputManager;

		// 初期化処理
		m_pInputManager->Init();
	}

	return m_pInputManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CInputManager::Init(void)
{
	// ジョイパッド生成
	CInputJoypad::Create();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CInputManager::Uninit(void)
{
	// ジョイパッド終了
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Uninit();
	}

	// 自身のポインタ破棄
	m_pInputManager = nullptr;
	delete this;
}

//=====================================================
// 更新処理
//=====================================================
void CInputManager::Update(void)
{
	// ジョイパッド更新
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Update();
	}
}