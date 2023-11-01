//*****************************************
//
// �ėp�����Z�b�g
// Author:���R����
//
//*****************************************
#ifndef _UNIVERSAL_H_
#define _UNIVERSAL_H_

#include "main.h"

//*****************************************
// �N���X�̒�`
//*****************************************
class CUniversal
{
public:
	CUniversal();	// �R���X�g���N�^
	~CUniversal();	// �f�X�g���N�^

	static CUniversal *Create(void);
	void Uninit(void);
	void LimitRot(float *fRot);	//��]���䏈��
	void SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	//�I�t�Z�b�g�ݒ菈��
	void FactingRot(float *pfRot, float fRotDest, float rotateFact);	//�����␳����
	static CUniversal *GetInstance(void) { return m_pUniversal; }

private:
	static CUniversal *m_pUniversal;	// ���g�̃|�C���^
};

#endif