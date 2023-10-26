//*****************************************************
//
// �`���[�g���A���}�l�[�W���[[tutorialManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _TUTORIALMANAGER_H_
#define _TUTORIALMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CAnim2D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTutorialManager : public CObject
{
public:
	CTutorialManager();	// �R���X�g���N�^
	~CTutorialManager();	// �f�X�g���N�^

	static CTutorialManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorialManager *GetInstance(void) { return m_pTutorialManager; }

private:
	void Load(void);

	static CTutorialManager *m_pTutorialManager;	// ���g�̃|�C���^
};

#endif
