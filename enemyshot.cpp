//*****************************************************
//
// 動く敵の処理[enemyshot.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyshot.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "particle.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define INITIAL_LIFE	(5)	// 初期体力
#define INITIAL_SCORE	(500)	// 初期スコア

//=====================================================
// コンストラクタ
//=====================================================
CEnemyShot::CEnemyShot()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyShot::~CEnemyShot()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyShot::Init(void)
{
	// 継承クラスの初期化
	CEnemy::Init();

	// 初期の体力設定
	SetLife(INITIAL_LIFE);

	// スコア設定
	SetScore(INITIAL_SCORE);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyShot::Uninit(void)
{
	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyShot::Update(void)
{
	// 位置を保存
	SetPositionOld(GetPosition());

	// 継承クラスの更新
	CEnemy::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyShot::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();
}