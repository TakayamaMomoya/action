//*****************************************************
//
// �^�C�g������[title.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "title.h"
#include "object.h"
#include "inputManager.h"
#include "manager.h"
#include "motion.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "skybox.h"
#include "edit.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define LOGO_PATH	"data\\TEXTURE\\UI\\logo000.png"	// ���S�̃p�X
#define START_PATH	"data\\TEXTURE\\UI\\start.png"	// �X�^�[�g�\���̃p�X
#define START_WIDTH	(200.0f)	// �X�^�[�g�\���̕�
#define START_HEIGHT	(50.0f)	// �X�^�[�g�\���̍���
#define DEST_WIDTH	(500.0f)	// �X�^�[�g�\���̕�
#define CHANGE_FACT	(0.1f)	// �ω�����W��
#define ALPHA_CHANGE	(0.05f)	// ���l�̕ω���

//=====================================================
// �R���X�g���N�^
//=====================================================
CTitle::CTitle()
{
	m_pStart = nullptr;
	m_state = STATE_NONE;
	m_pMotion = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CTitle::Init(void)
{
	// ���S�̐���
	CObject2D *pObject2D = CObject2D::Create(7);
	pObject2D->SetSize(875.0f * 0.45f, 320.0f * 0.45f);
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.7f, 200.0f, 0.0f));

	int nIdx = CManager::GetTexture()->Regist(LOGO_PATH);
	pObject2D->SetIdxTexture(nIdx);
	pObject2D->SetVtx();

	// �X�^�[�g�\���̐���
	m_pStart = CObject2D::Create(7);

	if (m_pStart != nullptr)
	{
		m_pStart->SetSize(START_WIDTH, START_HEIGHT);
		m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f));

		int nIdx = CManager::GetTexture()->Regist(START_PATH);
		m_pStart->SetIdxTexture(nIdx);
		m_pStart->SetVtx();
	}

	// �X�J�C�{�b�N�X�̐���
	CSkybox::Create();

	// �u���b�N�z�u�Ǎ�
	CBlock::Load("data\\MAP\\map00.bin");

	m_pMotion = CMotion::Create("data\\MOTION\\rayleigh.txt");

	if (m_pMotion != nullptr)
	{
		m_pMotion->SetPosition(D3DXVECTOR3(10.0f, 35.0f, 460.0f));
		m_pMotion->SetRot(D3DXVECTOR3(0.0f, 0.7f, 0.0f));
		m_pMotion->SetMotion(9);
		m_pMotion->InitPose(9);
		m_pMotion->SetMatrix();
	}

	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetTitle();
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CTitle::Update(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	// �V�[���̍X�V
	CScene::Update();
	
	CFade *pFade = CManager::GetFade();

	if (m_state == STATE_NONE)
	{
		if (pInputManager != nullptr)
		{
			if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
			{// �t�F�[�h
				if (m_pMotion != nullptr)
				{
					if (m_pMotion->GetMotion() != 2)
					{
						m_pMotion->SetMotion(2);

						m_state = STATE_MOTION;
					}
				}
			}
		}
	}
	else if(m_state == STATE_OUT)
	{
		// �X�^�[�g�\���̊Ǘ�
		ManageStart();
	}

	if (m_state == STATE_MOTION)
	{
		if (m_pMotion != nullptr)
		{
			if (m_pMotion->IsFinish())
			{
				if (pFade != nullptr)
				{
					CGame::SetProgress(0);

					pFade->SetFade(CScene::MODE_GAME);
				}
			}
		}
	}
}

//=====================================================
// �X�^�[�g�\���̊Ǘ�
//=====================================================
void CTitle::ManageStart(void)
{
	if (m_pStart == nullptr)
	{
		return;
	}

	float fWidth = m_pStart->GetWidth();
	float fHeight = m_pStart->GetHeight();
	float fDiffWidth;
	float fDiffHeight;

	// �������̌v�Z
	fDiffWidth = (DEST_WIDTH - fWidth) * CHANGE_FACT;
	fDiffHeight = (0.0f - fHeight) * CHANGE_FACT;

	// �����ɂ���
	D3DXCOLOR col = m_pStart->GetCol();

	col.a -= ALPHA_CHANGE;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	m_pStart->SetCol(col);

	// �T�C�Y�ݒ�
	m_pStart->SetSize(fWidth + fDiffWidth, fHeight + fDiffHeight);
	m_pStart->SetVtx();
}

//=====================================================
// �`�揈��
//=====================================================
void CTitle::Draw(void)
{

}