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
	void LimitRot(float *fRot);	//��]���䏈��
	void SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	//�I�t�Z�b�g�ݒ菈��
	void FactingRot(float *pfRot, float fRotDest, float rotateFact);	//�����␳����
	D3DXVECTOR3 LinePridiction(D3DXVECTOR3 pos, float fSpeedBullet, D3DXVECTOR3 posTarget, D3DXVECTOR3 moveTarget);
	float PlusMin(float fData1, float fData2);

private:
};

#endif