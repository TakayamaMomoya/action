//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;

//*****************************************************
// マクロ定義
//*****************************************************
#define INITIAL_LIFE_PLAYER	(100)	// 初期体力

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();	// デストラクタ

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	HRESULT Load(void);	// 読込
	static void Unload(void);
	void Hit(float fDamage);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

private:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// 待機状態
		MOTION_MOVE,	// 移動モーション
		MOTION_MAX
	};

	void Input(void);
	void InputMove(void);
	void InputCamera(void);
	void RotDest(void);

	int m_nLife;	// 体力
	bool m_bSprint;	// ダッシュ状態かどうか
	bool m_bJump;	// ジャンプしているかどうか
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_rotDest;	// 目標の向き
	CMotion *m_pBody;	// 体のポインタ
};

#endif
