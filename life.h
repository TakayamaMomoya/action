//*****************************************************
//
// ���C�t�Ǘ��̏���[life.h]
// Author:���R����
//
//*****************************************************

#ifndef _LIFE_H_
#define _LIFE_H_

#include "Object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject2D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CLife : public CObject
{
public:
	CLife(int nPriority = 6);	// �R���X�g���N�^
	~CLife();	// �f�X�g���N�^

	static CLife *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};

private:
	CObject2D *m_pObjectGauge;	// �Q�[�W�̃|�C���^
};

#endif
