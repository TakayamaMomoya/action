//*****************************************************
//
// ゲーム処理[game.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CScore;
class CTimer;
class CGame;

//*****************************************************
// クラスの定義
//*****************************************************
class CGame : public CScene
{
public:
	enum STATE
	{// 状態
		STATE_NONE,	// 何もしていない状態
		STATE_NORMAL,	// 通常状態
		STATE_RESULT,	// リザルト状態
		STATE_END,	// 終了状態
		STATE_MAX
	};

	CGame();	// コンストラクタ
	~CGame();	// デストラクタ

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();
	static CScore *GetScore(void) { return m_pScore; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static void ReleaseScore(void);
	static void ReleaseTimer(void);
	static void SetState(STATE state) { m_state = state; }
	static STATE GetState(void) { return m_state; }

private:
	void UpdateCamera(void);
	void ManageState(void);
	void Debug(void);

	static CScore *m_pScore;	// スコアのポインタ
	static CTimer *m_pTimer;	// タイマーのポインタ
	static STATE m_state;	// 状態
	bool m_bStop;	// 停止状態
};

#endif