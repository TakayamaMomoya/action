//*****************************************************
//
// ライフの処理[life.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "player.h"
#include "game.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define NUM_PLACE	(6)	// 桁数
#define GAUGE_WIDTH	(40.0f)	// ゲージの横幅
#define GAUGE_HEIGTH	(250.0f)	// ゲージの縦の長さ
#define GAUGE_POS	(D3DXVECTOR3(1100.0f,650.0f,0.0f))	// ゲージの初期位置

//=====================================================
// コンストラクタ
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pObjectGauge = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CLife::~CLife()
{

}

//=====================================================
// 生成処理
//=====================================================
CLife *CLife::Create(void)
{
	CLife *pLife = nullptr;

	if (pLife == nullptr)
	{
		pLife = new CLife;

		pLife->Init();
	}

	return pLife;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CLife::Init(void)
{
	if (m_pObjectGauge == nullptr)
	{// ゲージの生成
		m_pObjectGauge = CObject2D::Create(5);

		if (m_pObjectGauge != nullptr)
		{
			m_pObjectGauge->SetPosition(D3DXVECTOR3(GAUGE_POS.x, GAUGE_POS.y, 0.0f));
			m_pObjectGauge->SetSize(GAUGE_WIDTH, GAUGE_HEIGTH);
			m_pObjectGauge->SetVtx();
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CLife::Uninit(void)
{
	if (m_pObjectGauge != nullptr)
	{// ゲージの破棄
		m_pObjectGauge = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CLife::Update(void)
{

}