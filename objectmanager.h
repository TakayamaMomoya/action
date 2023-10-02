//*****************************************************
//
// �I�u�W�F�N�g�Ǘ�[objectmanager.h]
// Author:���R����
//
//*****************************************************
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPlayer;
class CTutorialPlayer;
class CMeshField;
class CScore;
class CTimer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CObjectManager
{
public:
	CObjectManager();	// �R���X�g���N�^
	~CObjectManager();	// �f�X�g���N�^

	CPlayer *GetPlayer(void) { return m_pPlayer; }
	CMeshField *GetMeshField(void) { return m_pMeshField; }
	CScore *GetScore(void) { return m_pScore; }
	CTimer *GetTimer(void) { return m_pTimer; }
	
	void BindPlayer(CPlayer *pPlayer) { m_pPlayer = pPlayer; }
	void BindTutorialPlayer(CTutorialPlayer *pPlayer) { m_pTutorialPlayer = pPlayer; }
	void BindMeshField(CMeshField *pMeshField) { m_pMeshField = pMeshField; }

	void ReleasePlayer(void);
	void ReleaseMeshField(void) { m_pMeshField = nullptr; }
	void ReleaseScore(void);
	void ReleaseTimer(void);
	
private:
	CPlayer *m_pPlayer;	// �v���C���[�̃N���X
	CTutorialPlayer *m_pTutorialPlayer;	// �`���[�g���A���v���C���[�̃N���X
	CMeshField *m_pMeshField;	// ���b�V���t�B�[���h�ւ̃|�C���^
	CScore *m_pScore;	// �X�R�A�̃|�C���^
	CTimer *m_pTimer;	// �^�C�}�[�̃|�C���^
};

#endif