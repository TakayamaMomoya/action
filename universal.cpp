//*****************************************
//
//���낢��ėp�����l�ߍ���
//Author:���R����
//
//*****************************************

//*****************************************
//�C���N���[�h
//*****************************************
#include "manager.h"
#include "renderer.h"
#include "universal.h"

//=========================================
// �R���X�g���N�^
//=========================================
CUniversal::CUniversal()
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CUniversal::~CUniversal()
{

}

//=========================================
//��]���䏈��
//=========================================
void CUniversal::LimitRot(float *fRot)
{
	if (*fRot > D3DX_PI)
	{
		*fRot -= 6.28f;
	}
	if (*fRot < -D3DX_PI)
	{
		*fRot += 6.28f;
	}
}

//========================================
//�I�t�Z�b�g�ݒ菈��
//========================================
void CUniversal::SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtxWorldOffset);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posOffset.x, posOffset.y, posOffset.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxTrans);

	//�}�g���b�N�X���������킹��
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxWorldOwner);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtxWorldOffset);
}

//========================================
// �����␳����
//========================================
void CUniversal::FactingRot(float *pfRot, float fRotDest, float rotateFact)
{
	//�����p�x���擾
	float fRotDiff = fRotDest - *pfRot;

	//�p�x�̏C��
	if (fRotDiff < 0)
	{
		fRotDiff += 6.28f;
	}
	else if (fRotDiff > 0)
	{
		fRotDiff -= 6.28f;
	}

	//�p�x�␳
	*pfRot += fRotDiff * rotateFact;

	//�p�x�̏C��
	if (fRotDiff < 0)
	{
		fRotDiff += 6.28f;
	}
	else if (fRotDiff > 0)
	{
		fRotDiff -= 6.28f;
	}

	//�p�x�␳
	*pfRot += fRotDiff * rotateFact;
}