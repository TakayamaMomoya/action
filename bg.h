//*****************************************************
//
// �w�i�̏���[bg.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _BG_H_
#define _BG_H_

#include "object2D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBg : public CObject2D
{
public:
	CBg(int nPriority = 1);	// �R���X�g���N�^
	~CBg();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(void);	// ��������
	static HRESULT Load(void);	// �Ǎ�
	static void Unload(void);
	void SetScroll(float fSpeedV,float fSpeedU);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR2 m_texLeftUp;	// �e�N�X�`���E����W
	D3DXVECTOR2 m_texRightDown;	// �e�N�X�`���������W
	float m_fSpeedU;	// ���X�N���[�����x
	float m_fSpeedV;	// �c�X�N���[�����x
};

#endif
