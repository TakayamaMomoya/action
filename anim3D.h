//*****************************************************
//
// 爆発処理[explosion.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*****************************************************
// インクルード
//*****************************************************
#include "Object3D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CAnim3D : public CObject3D
{
public:
	CAnim3D(int nPriority = 4);	// コンストラクタ
	~CAnim3D();	// デストラクタ

	static CAnim3D *Create(D3DXVECTOR3 pos, int nNumAnim, int nTimeAnim);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void SetAnim(int nAnim, int nNumAnim);

	int m_nCounterAnim;	// アニメーションカウンター
	int m_nPatternAnim;	// アニメパターンNO.
	int m_nSpeedAnim;	// アニメーション速度
	int m_nNumAnim;	// アニメーション枚数
};

#endif