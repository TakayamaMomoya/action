//*****************************************************
//
// �Q�[������[game.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "score.h"
#include "timer.h"
#include "object.h"
#include "universal.h"
#include "particle.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "fade.h"
#include "camera.h"
#include "effect3D.h"
#include "objectmanager.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "field.h"
#include "block.h"
#include "edit.h"
#include "enemy.h"
#include "skybox.h"
#include "enemyManager.h"
#include "animEffect3D.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TRANS_TIME	(60)	// �I���܂ł̗]�C�̃t���[����
#define LIMIT_LENGTH	(10000)	// �ړ������̋���
#define LIMIT_WIDTH	(100)	// ����v���C���[�̕�
#define LIMIT_HEIGHT	(2000)	// �������x
#define BONUS_TIME	(40)	// �{�[�i�X���t�^�����Œ���̃^�C��
#define RATE_BONUS	(0.015f)	// 1�b������̃^�C���{�[�i�X
#define RESULT_TIME	(5)	// ���U���g��ʕ\���܂ł̃��O

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CScore *CGame::m_pScore = nullptr;	// �X�R�A�̃|�C���^
CTimer *CGame::m_pTimer = nullptr;	// �^�C�}�[�̃|�C���^
CGame::STATE CGame::m_state = STATE_NONE;

//=====================================================
// �R���X�g���N�^
//=====================================================
CGame::CGame()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGame::~CGame()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CGame::Init(void)
{
	m_state = STATE_NORMAL;

	CObjectManager *pObjManager = CManager::GetObjectManager();

	if (m_pScore == nullptr)
	{// �X�R�A����
		m_pScore = CScore::Create();
	}

	if (m_pScore != nullptr)
	{// �X�R�A������
		m_pScore->Init();
	}

	if (m_pTimer == nullptr)
	{// �^�C�}�[����
		m_pTimer = CTimer::Create();
	}

	// �J���������̐ݒ�
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetDist(180.0f);
	}

	// �v���C���[����
	CPlayer::Create();

	// �X�J�C�{�b�N�X
	CSkybox::Create();

	// �u���b�N�z�u�Ǎ�
	CBlock::Load();

	// �G�}�l�[�W���[����
	CEnemyManager::Create();

	// �RD�G�t�F�N�g�Ǘ�����
	CAnimEffect3D::Create();

#ifdef _DEBUG
	CEdit::Create();
#endif

	m_bStop = false;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGame::Uninit(void)
{
	if (m_pScore != nullptr)
	{// �X�R�A�̏I���E�j��
		m_pScore->Uninit();

		m_pScore = nullptr;
	}

	if (m_pTimer != nullptr)
	{// �^�C�}�[�̏I���E�j��
		m_pTimer->Uninit();

		m_pTimer = nullptr;
	}

	// �u���b�N���폜
	CBlock::DeleteAll();

	// �I�u�W�F�N�g�S��
	CObject::ReleaseAll();
}

//=====================================================
// �X�R�A�I������
//=====================================================
void CGame::ReleaseScore(void)
{
	if (m_pScore != nullptr)
	{// �X�R�A�̏I���E�j��
		m_pScore = nullptr;
	}
}

//=====================================================
// �^�C�}�[�I������
//=====================================================
void CGame::ReleaseTimer(void)
{
	if (m_pTimer != nullptr)
	{// �X�R�A�̏I���E�j��
		m_pTimer = nullptr;
	}
}

//=====================================================
// �X�V����
//=====================================================
void CGame::Update(void)
{
	// ���͎擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad *pJoypad = CManager::GetJoypad();

	CFade *pFade = CManager::GetFade();

	if (m_bStop == false)
	{
		// �V�[���̍X�V
		CScene::Update();
	}
	else
	{
		CEdit *pEdit = CEdit::GetInstatnce();

		if (pEdit != nullptr)
		{
			pEdit->Update();
		}
	}

	// �J�����X�V
	UpdateCamera();

	// ��ԊǗ�
	ManageState();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			if (pFade != nullptr)
			{
				//pFade->SetFade(CScene::MODE_RANKING);
			}
		}
	}

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// �J�����̍X�V
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_bStop == false)
	{
		// �v���C���[�̒Ǐ]
		pCamera->FollowPlayer();
	}
	else
	{
		// ����
		pCamera->Control();
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CManager::GetFade();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
		break;
	case CGame::STATE_RESULT:
		break;
	case CGame::STATE_END:
		
		if(pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CGame::Debug(void)
{
	// ���͎擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_F))
	{
		m_bStop = m_bStop ? false : true;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CGame::Draw(void)
{

}