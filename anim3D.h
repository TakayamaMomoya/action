//*****************************************************
//
// ��������[explosion.h]
// Author:���R����
//
//*****************************************************

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "Object3D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CAnim3D : public CObject3D
{
public:
	CAnim3D(int nPriority = 4);	// �R���X�g���N�^
	~CAnim3D();	// �f�X�g���N�^

	static CAnim3D *Create(D3DXVECTOR3 pos, int nNumAnim, int nTimeAnim);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void SetAnim(int nAnim, int nNumAnim);

	int m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	// �A�j���p�^�[��NO.
	int m_nSpeedAnim;	// �A�j���[�V�������x
	int m_nNumAnim;	// �A�j���[�V��������
};

#endif