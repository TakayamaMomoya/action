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
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionCube;
class CCollisionSphere;

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
	void Load(void);
	void Hit(float fDamage);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	static CPlayer *GetInstance(void) { return m_pPlayer; }

private:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// 待機状態
		MOTION_MOVE,	// 移動モーション
		MOTION_JUMP,	// ジャンプモーション
		MOTION_FALL,	// 落下モーション
		MOTION_ATTACK,	// 攻撃モーション
		MOTION_ATTACKTURN,	// 反転攻撃モーション
		MOTION_AIRATTACK,	// 空中攻撃モーション
		MOTION_MAX
	};
	struct AttackInfo
	{// 攻撃の情報
		int nIdxMotion;	// モーション番号
		int nIdxParent;	// 親パーツ番号
		D3DXVECTOR3 pos;	// オフセット位置
		int nKey;	// キー番号
		int nFrame;	// 発生するフレーム
		float fRadius;	// 半径
	};
	enum JUMPSTATE
	{// ジャンプ状態
		JUMPSTATE_NONE = 0,
		JUMPSTATE_NORMAL,
		JUMPSTATE_ATTACK,
		JUMPSTATE_MAX
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void InputCamera(void);
	void ManageMotion(void);
	void ManageCollision(void);
	void RotDest(void);
	void SetMotion(MOTION motion);
	void ManageAttack(void);

	int m_nLife;	// 体力
	int m_nCntAfterImage;	// 残像を出すカウンター
	bool m_bSprint;	// ダッシュ状態かどうか
	bool m_bAttack;	// 攻撃フラグ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_rotDest;	// 目標の向き
	CMotion *m_pBody;	// 体のポインタ
	CCollisionCube *m_pCollisionCube;	// 立方体の当たり判定
	CCollisionSphere *m_pClsnAttack;	// 攻撃の当たり判定
	CCollisionSphere *m_pClsnHit;	// 被弾当たり判定
	int m_nNumAttack;	// 攻撃判定の数
	AttackInfo *m_pAttackInfo;	// 攻撃の情報ポインタ
	JUMPSTATE m_jump;	// ジャンプ状態

	static CPlayer *m_pPlayer;	// 自身のポインタ
};

#endif
