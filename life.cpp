//*****************************************************
//
// ���C�t�̏���[life.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "player.h"
#include "game.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE	(6)	// ����
#define GAUGE_WIDTH	(40.0f)	// �Q�[�W�̉���
#define GAUGE_HEIGTH	(250.0f)	// �Q�[�W�̏c�̒���
#define GAUGE_POS	(D3DXVECTOR3(1100.0f,650.0f,0.0f))	// �Q�[�W�̏����ʒu

//=====================================================
// �R���X�g���N�^
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pObjectGauge = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CLife::~CLife()
{

}

//=====================================================
// ��������
//=====================================================
CLife *CLife::Create(void)
{
	CLife *pLife = nullptr;

	if (pLife == nullptr)
	{
		pLife = new CLife;

		pLife->Init();
	}

	return pLife;
}

//=====================================================
// ����������
//=====================================================
HRESULT CLife::Init(void)
{
	if (m_pObjectGauge == nullptr)
	{// �Q�[�W�̐���
		m_pObjectGauge = CObject2D::Create(5);

		if (m_pObjectGauge != nullptr)
		{
			m_pObjectGauge->SetPosition(D3DXVECTOR3(GAUGE_POS.x, GAUGE_POS.y, 0.0f));
			m_pObjectGauge->SetSize(GAUGE_WIDTH, GAUGE_HEIGTH);
			m_pObjectGauge->SetVtx();
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CLife::Uninit(void)
{
	if (m_pObjectGauge != nullptr)
	{// �Q�[�W�̔j��
		m_pObjectGauge = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CLife::Update(void)
{

}