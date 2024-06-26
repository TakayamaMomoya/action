//*****************************************************
//
// ��������[explosion.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "anim3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CAnim3D::CAnim3D(int nPriority) : CObject3D(nPriority)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nSpeedAnim = 0;
	m_nNumAnim = 0;
	m_bFinish = false;
	m_bLoop = false;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CAnim3D::~CAnim3D()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CAnim3D::Init(void)
{
	// �p���N���X�̏�����
	CObject3D::Init();

	SetAnim(m_nPatternAnim, m_nNumAnim);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CAnim3D::Uninit(void)
{
	// �p���N���X�̏I��
	CObject3D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CAnim3D::Update(void)
{
	// �J�E���^�[�����Z
	m_nCounterAnim++;

	if (m_nCounterAnim % m_nSpeedAnim == 0)
	{// ��莞�Ԃ��ƂɃA�j���[�V�������s��
		m_nCounterAnim = 0;
		m_nPatternAnim++;

		// �A�j���[�V�������𒴂�����0���ɖ߂�
		m_nPatternAnim = m_nPatternAnim % m_nNumAnim;

		// �A�j���[�V�����ݒ�
		SetAnim(m_nPatternAnim, m_nNumAnim);

		if (m_nPatternAnim == m_nNumAnim - 1)
		{// �A�j���[�V�����I��
			if (m_bLoop == false)
			{
				Uninit();
			}
		}
	}

	// �p���N���X�̍X�V
	CObject3D::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CAnim3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �p���N���X�̕`��
	CObject3D::Draw();

	// ���C�e�B���O��߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\n�p�X�F[%d]", GetIdxTexture());
#endif
}

//=====================================================
// ��������
//=====================================================
CAnim3D *CAnim3D::Create(D3DXVECTOR3 pos, int nNumAnim, int nTimeAnim, bool bLoop)
{
	CAnim3D *pAnim3D = nullptr;

	pAnim3D = new CAnim3D;

	if (pAnim3D != nullptr)
	{
		pAnim3D->SetPosition(pos);
		pAnim3D->SetSize(20.0f, 20.0f);
		pAnim3D->m_nNumAnim = nNumAnim;
		pAnim3D->m_nSpeedAnim = nTimeAnim;
		pAnim3D->m_bLoop = bLoop;

		// ����������
		pAnim3D->Init();
	}

	return pAnim3D;
}

//=====================================================
// �A�j���[�V�����ݒ�
//=====================================================
void CAnim3D::SetAnim(int nAnim, int nNumAnim)
{
	// ���_�o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	if (pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2
		(
			(1.0f / nNumAnim) * nAnim,
			0.0f
		);
		pVtx[1].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim + 1.0f / nNumAnim * nAnim,
			0.0f
		);
		pVtx[2].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim * nAnim,
			1.0f
		);
		pVtx[3].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim + 1.0f / nNumAnim * nAnim,
			1.0f
		);

		// ���_�o�b�t�@�̃A�����b�N
		pVtxBuff->Unlock();
	}
}