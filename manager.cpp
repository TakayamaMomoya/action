//*****************************************************
//
// �}�l�[�W���[����[manager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "bg.h"
#include "debugproc.h"
#include "effect2D.h"
#include "effect3D.h"
#include "sound.h"
#include "score.h"
#include "timer.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectX.h"
#include "billboard.h"
#include "model.h"
#include "texture.h"
#include "universal.h"
#include "particle.h"
#include "fade.h"
#include "objectmanager.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CRenderer *CManager::m_pRenderer = nullptr;	// �����_���[�̃|�C���^
CInputKeyboard *CManager::m_pKeyboard = nullptr;	// �L�[�{�[�h�̃|�C���^
CInputMouse *CManager::m_pMouse = nullptr;	// �}�E�X�̃|�C���^
CInputJoypad *CManager::m_pJoypad = nullptr;	// �W���C�p�b�h�̃|�C���^
CDebugProc *CManager::m_pDebugProc = nullptr;	// �f�o�b�O�v���V�[�W���̃|�C���^
CSound *CManager::m_pSound = nullptr;	// �T�E���h�̃|�C���^
CCamera *CManager::m_pCamera = nullptr;	// �J�����̃|�C���^
CLight *CManager::m_pLight = nullptr;	// ���C�g�̃|�C���^
CTexture *CManager::m_pTexture = nullptr;	// �e�N�X�`���Ǘ��ւ̃|�C���^
CUniversal *CManager::m_pUniversal = nullptr;	// �ėp�����ւ̃|�C���^
CObjectManager *CManager::m_pObjectManager = nullptr;	// �I�u�W�F�N�g�Ǘ��ւ̃|�C���^
CScene *CManager::m_pScene = nullptr;	// �V�[���ւ̃|�C���^
CFade *CManager::m_pFade = nullptr;	// �t�F�[�h�ւ̃|�C���^
CScene::MODE CManager::m_mode = CScene::MODE_TITLE;	// ���݂̃��[�h
int CManager::m_nScore = 0;	// �X�R�A�ۑ��p

//=====================================================
// �R���X�g���N�^
//=====================================================
CManager::CManager()
{
	m_pScene = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CManager::~CManager()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == nullptr)
	{// �����_���[����
		m_pRenderer = new CRenderer;

		if (m_pRenderer != nullptr)
		{
			// �����_���[������
			if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pKeyboard == nullptr)
	{// �L�[�{�[�h����
		m_pKeyboard = new CInputKeyboard;

		if (m_pKeyboard != nullptr)
		{
			// �L�[�{�[�h������
			if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pMouse == nullptr)
	{// �}�E�X����
		m_pMouse = new CInputMouse;

		if (m_pMouse != nullptr)
		{
			// �}�E�X������
			if (FAILED(m_pMouse->Init(hInstance, hWnd)))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pJoypad == nullptr)
	{// �W���C�p�b�h����
		m_pJoypad = new CInputJoypad;

		if (m_pJoypad != nullptr)
		{
			// �W���C�p�b�h������
			if (FAILED(m_pJoypad->Init()))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pDebugProc == nullptr)
	{// �f�o�b�O�v���V�[�W������
		m_pDebugProc = new CDebugProc;

		if (m_pDebugProc != nullptr)
		{// �f�o�b�O�v���V�[�W��������
			m_pDebugProc->Init();
		}
	}

	if (m_pSound == nullptr)
	{// �T�E���h����
		m_pSound = new CSound;

		if (m_pSound != nullptr)
		{
			// �T�E���h������
			if (FAILED(m_pSound->Init(hWnd)))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pCamera == nullptr)
	{// �J��������
		m_pCamera = new CCamera;

		if (m_pCamera != nullptr)
		{
			// ������
			if (FAILED(m_pCamera->Init()))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pLight == nullptr)
	{// ���C�g����
		m_pLight = new CLight;

		if (m_pLight != nullptr)
		{
			// ������
			if (FAILED(m_pLight->Init()))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pTexture == nullptr)
	{// �e�N�X�`���Ǘ�����
		m_pTexture = new CTexture;

		if (m_pTexture != nullptr)
		{
			// ������
			if (FAILED(m_pTexture->Load()))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pFade == nullptr)
	{// �t�F�[�h����
		m_pFade = CFade::Create();

		if (m_pFade != nullptr)
		{
			m_pFade->Init();
		}
	}

	if (m_pUniversal == nullptr)
	{// �ėp��������
		m_pUniversal = new CUniversal;
	}

	if (m_pObjectManager == nullptr)
	{// �I�u�W�F�N�g�Ǘ��̐���
		m_pObjectManager = new CObjectManager;
	}

	// �p�[�e�B�N���̓Ǎ�
	CParticle::Load();

	SetMode(m_mode);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CManager::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
	}

	if (m_pObjectManager != nullptr)
	{// �I�u�W�F�N�g�Ǘ��̍폜
		delete m_pObjectManager;
		m_pObjectManager = nullptr;
	}

	// �p�[�e�B�N�����j��
	CParticle::Unload();

	if (m_pRenderer != nullptr)
	{// �����_���[�̏I���E�j��
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pUniversal != nullptr)
	{// �ėp�����̏I���E�j��

		delete m_pUniversal;
		m_pUniversal = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{// �L�[�{�[�h�̏I���E�j��
		m_pKeyboard->Uninit();

		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pMouse != nullptr)
	{// �}�E�X�̏I���E�j��
		m_pMouse->Uninit();

		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pJoypad != nullptr)
	{// �W���C�p�b�h�̏I���E�j��
		m_pJoypad->Uninit();

		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	if (m_pSound != nullptr)
	{// �T�E���h�̏I���E�j��
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{// �f�o�b�O�v���V�[�W���̏I���E�j��
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pLight != nullptr)
	{// ���C�g�̏I���E�j��
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{// �J�����̏I���E�j��
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pTexture != nullptr)
	{// �e�N�X�`���̏I���E�j��
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// ���f���j��
	CModel::Unload();
}

//=====================================================
// �X�V����
//=====================================================
void CManager::Update(void)
{
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}

	if (m_pKeyboard != nullptr)
	{
		// �L�[�{�[�h�̍X�V
		m_pKeyboard->Update();
	}

	if (m_pMouse != nullptr)
	{
		// �}�E�X�̍X�V
		m_pMouse->Update();
	}

	if (m_pJoypad != nullptr)
	{
		// �W���C�p�b�h�̍X�V
		m_pJoypad->Update();
	}

	if (m_pSound != nullptr)
	{
		// �T�E���h�̍X�V
		m_pSound->Update();
	}

#ifdef _DEBUG
	if (m_pDebugProc != nullptr)
	{
		// �f�o�b�O�v���V�[�W���̍X�V
		m_pDebugProc->Update();
	}
#endif

	if (m_pLight != nullptr)
	{
		// ���C�g�̍X�V
		m_pLight->Update();
	}
	
	if (m_pKeyboard != nullptr)
	{
		if (m_pKeyboard->GetTrigger(DIK_F3))
		{// �������Z�b�g
			CManager::SetMode(CScene::MODE_TITLE);
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CManager::Draw(void)
{
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Print("\n�X�R�A[%d]\n",m_nScore);
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}

	if (m_pRenderer != nullptr)
	{
		// �����_���[�̕`��
		m_pRenderer->Draw();
	}
}

//=====================================================
// ���[�h�ݒ�
//=====================================================
void CManager::SetMode(CScene::MODE mode)
{
	// �V�[����j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = nullptr;
	}

	// �V�[������
	m_pScene = CScene::Create(mode);

	// ���[�h�ݒ�
	m_mode = mode;

	if (m_pCamera != nullptr)
	{
		m_pCamera->Init();
	}
}