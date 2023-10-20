//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "inputManager.h"
#include "manager.h"
#include "inputjoypad.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CInputManager *CInputManager::m_pInputManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CInputManager::CInputManager()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CInputManager::~CInputManager()
{

}

//=====================================================
// ��������
//=====================================================
CInputManager *CInputManager::Create(void)
{
	if (m_pInputManager == nullptr)
	{// �C���X�^���X����
		m_pInputManager = new CInputManager;

		// ����������
		m_pInputManager->Init();
	}

	return m_pInputManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CInputManager::Init(void)
{
	// �W���C�p�b�h����
	CInputJoypad::Create();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CInputManager::Uninit(void)
{
	// �W���C�p�b�h�I��
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Uninit();
	}

	// ���g�̃|�C���^�j��
	m_pInputManager = nullptr;
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CInputManager::Update(void)
{
	// �W���C�p�b�h�X�V
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Update();
	}
}