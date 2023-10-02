//*****************************************************
//
// �X�R�A�̏���[score.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE	(6)	// ����
#define SCORE_SPEED	(71)	// �X�R�A�̕ς��X�s�[�h
#define RANK_BONUS	(0.05f)	// 1�����N�ɂ�����{�[�i�X�{��
#define RANK_RATE	(0.0004f)	// �����N�̏オ��{��

//=====================================================
// �R���X�g���N�^
//=====================================================
CScore::CScore()
{
	m_pObjNumber = nullptr;
	m_nScore = 0;
	m_nSocreDest = 0;
	m_nIdxTexture = -1;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CScore::~CScore()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CScore::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CScore::Uninit(void)
{
	if (m_pObjNumber != nullptr)
	{
		m_pObjNumber = nullptr;
	}

	CGame::ReleaseScore();

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CScore::Update(void)
{
	//�X�R�A�l�㏸���o==============================
	m_nScore += (int)((m_nSocreDest - m_nScore) * 0.1f);

	if (m_pObjNumber != nullptr)
	{
		m_pObjNumber->SetValue(m_nScore, NUM_PLACE);
	}
}

//=====================================================
// �X�R�A���Z
//=====================================================
int CScore::AddScore(int nValue)
{
	m_nSocreDest += nValue;

	return nValue;
}

//=====================================================
// ��������
//=====================================================
CScore *CScore::Create(void)
{
	CScore *pScore = nullptr;
	
	CObject2D *pObject2D = CObject2D::Create(7);

	if (pObject2D != nullptr)
	{
		pObject2D->SetPosition(D3DXVECTOR3(1030.0f, 80.0f, 0.0f));
		pObject2D->SetSize(70.0f, 35.0f);

		// �e�N�X�`���ԍ��擾
		int nIdx = CManager::GetTexture()->Regist("data\\TEXTURE\\UI\\scoreBack.png");

		pObject2D->SetIdxTexture(nIdx);
		pObject2D->SetVtx();
	}

	if (pScore == nullptr)
	{
		pScore = new CScore;

		if (pScore->m_pObjNumber == nullptr)
		{
			pScore->m_pObjNumber = CNumber::Create(NUM_PLACE, pScore->m_nScore);
			pScore->m_pObjNumber->SetPosition(D3DXVECTOR3(1100.0f, 80.0f, 0.0f));
			pScore->m_pObjNumber->SetSizeAll(15.0f,32.5f);
		}
	}

	return pScore;
}