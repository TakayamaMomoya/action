//*****************************************************
//
// �RD�A�j���[�V�����G�t�F�N�g����[animEffect3D.h]
// Author:���R����
//
//*****************************************************

#ifndef _ANIMEFFECT3D_H_
#define _ANIMEFFECT3D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "Object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CAnim3D;

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_STRING	(256)	// �ő啶����

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CAnimEffect3D : public CObject
{
public:
	enum TYPE
	{
		TYPE_EXPLOSION = 0,	// ����
		TYPE_FLASH,	// �Ή�
		TYPE_MAX
	};

	CAnimEffect3D(int nPriority = 4);	// �R���X�g���N�^
	~CAnimEffect3D();	// �f�X�g���N�^

	static CAnimEffect3D *Create(void);
	CAnim3D *CreateEffect(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAnimEffect3D *GetInstance(void) { return m_pAnimEffect3D; }

private:
	struct SInfoAnimEffect
	{// �A�j���[�V�����G�t�F�N�g���
		char acPath[MAX_STRING];	// �p�X
		int nNumAnim;	// �A�j���[�V������
		int nSpeedAnim;	// �A�j���[�V�������x
	};
	
	void Load(void);
	
	static CAnimEffect3D *m_pAnimEffect3D;	// ���g�̃|�C���^
	SInfoAnimEffect *m_apAnimEffect[TYPE_MAX];	// ���̃|�C���^
};

#endif