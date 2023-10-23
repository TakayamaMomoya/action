//*****************************************************
//
// UI�}�l�[�W���[[UIManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CLife;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUIManager : public CObject
{
public:
	CUIManager();	// �R���X�g���N�^
	~CUIManager();	// �f�X�g���N�^

	static CUIManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIManager *GetInstance(void) { return m_pUIManager; }

private:
	static CUIManager *m_pUIManager;	// ���g�̃|�C���^
	bool m_bDisp;	// UI��\�����邩�ǂ���
	CLife *m_pLife;	// ���C�t
};

#endif
