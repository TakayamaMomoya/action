//*****************************************************
//
// �^�C�}�[�̏���[timer.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "timer.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "game.h"
#include "debugproc.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE	(2)	// ����
#define INITIAL_TIME	(120)	// �����̎���

//=====================================================
// �R���X�g���N�^
//=====================================================
CTimer::CTimer()
{
	m_pObjMinute = nullptr;
	m_pObjSecond = nullptr;
	m_nSecond = 0;
	m_nCntSecond = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTimer::~CTimer()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CTimer::Init(void)
{
	m_nSecond = INITIAL_TIME;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	if (m_pObjMinute != nullptr)
	{
		m_pObjMinute = nullptr;
	}

	if (m_pObjSecond != nullptr)
	{
		m_pObjSecond = nullptr;
	}

	CGame::ReleaseTimer();

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CTimer::Update(void)
{
	if (CGame::GetState() != CGame::STATE_NORMAL)
	{
		return;
	}

	m_nCntSecond++;

	if (m_nCntSecond > 60)
	{
		m_nCntSecond = 0;
		
		if (m_nSecond >= 1)
		{
			m_nSecond--;
		}
	}

	// ���̌v�Z
	int nMinute = m_nSecond / 60;

	// �b�̌v�Z
	int nSecond = m_nSecond % 60;

	if (m_pObjMinute != nullptr)
	{// ���\���̐���
		m_pObjMinute->SetValue(nMinute, NUM_PLACE);
	}

	if (m_pObjSecond != nullptr)
	{// �b�\���̐���
		m_pObjSecond->SetValue(nSecond, NUM_PLACE);
	}

	if (m_nSecond <= 0)
	{
		m_nSecond = 0;
	}
}

//=====================================================
// ���ԉ��Z
//=====================================================
void CTimer::AddTimer(int nValue)
{
	m_nSecond += nValue;
}

//=====================================================
// ��������
//=====================================================
CTimer *CTimer::Create(void)
{
	CTimer *pTimer = nullptr;
	
	if (pTimer == nullptr)
	{
		pTimer = new CTimer;

		pTimer->Init();

		if (pTimer->m_pObjMinute == nullptr)
		{// ���\���̏I��
			pTimer->m_pObjMinute = CNumber::Create(NUM_PLACE, pTimer->m_nSecond);
			pTimer->m_pObjMinute->SetPosition(D3DXVECTOR3(520.0f, 80.0f, 0.0f));
			pTimer->m_pObjMinute->SetSizeAll(20.0f,50.0f);
		}

		if (pTimer->m_pObjSecond == nullptr)
		{// �b�\���̏I��
			pTimer->m_pObjSecond = CNumber::Create(NUM_PLACE, pTimer->m_nSecond);
			pTimer->m_pObjSecond->SetPosition(D3DXVECTOR3(620.0f, 80.0f, 0.0f));
			pTimer->m_pObjSecond->SetSizeAll(20.0f, 50.0f);
		}
	}

	return pTimer;
}

//=====================================================
// �`�揈��
//=====================================================
void CTimer::Draw(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n���݂̕b��[%d]", m_nSecond);
}