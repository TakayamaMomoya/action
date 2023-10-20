//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CInputManager : public CObject
{
public:
	CInputManager();	// �R���X�g���N�^
	~CInputManager();	// �f�X�g���N�^

	static CInputManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CInputManager *GetInstance(void) { return m_pInputManager; }

private:
	static CInputManager *m_pInputManager;	// ���g�̃|�C���^
};

#endif
