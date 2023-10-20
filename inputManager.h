//*****************************************************
//
// 入力マネージャー[inputManager.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CInputManager : public CObject
{
public:
	CInputManager();	// コンストラクタ
	~CInputManager();	// デストラクタ

	static CInputManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CInputManager *GetInstance(void) { return m_pInputManager; }

private:
	static CInputManager *m_pInputManager;	// 自身のポインタ
};

#endif
