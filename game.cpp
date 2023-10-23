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
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"

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
#define BOSS_LINE	(2737.0f)	// �{�X��ɓ˓����郉�C��
#define CHECKPOINT_PATH "data\\MAP\\checkpoint.txt"	// �`�F�b�N�|�C���g�f�[�^�̃p�X

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CScore *CGame::m_pScore = nullptr;	// �X�R�A�̃|�C���^
CTimer *CGame::m_pTimer = nullptr;	// �^�C�}�[�̃|�C���^
CGame::STATE CGame::m_state = STATE_NONE;
int CGame::m_nProgress = 0;

//=====================================================
// �R���X�g���N�^
//=====================================================
CGame::CGame()
{
	m_pPosCheckPoint = nullptr;
	m_nNumCheckPoint = 0;
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

	// ���X�|�[���n�_�ݒ�
	LoadCheckPoint();

	// �v���C���[����
	CPlayer *pPlayer = CPlayer::Create();

	if (pPlayer != nullptr && m_pPosCheckPoint != nullptr)
	{// �X�|�[���n�_�̐ݒ�
		pPlayer->SetPosition(m_pPosCheckPoint[m_nProgress]);
	}

	// �X�J�C�{�b�N�X
	CSkybox::Create();

	// �u���b�N�z�u�Ǎ�
	CBlock::Load();

	// �G�}�l�[�W���[����
	CEnemyManager::Create();

	// �RD�G�t�F�N�g�Ǘ�����
	CAnimEffect3D::Create();

	// UI�}�l�[�W���[
	CUIManager::Create();

#ifdef _DEBUG
	//CEdit::Create();
#endif

	m_bStop = false;

	return S_OK;
}

//=====================================================
// �`�F�b�N�|�C���g�̓Ǎ�
//=====================================================
void CGame::LoadCheckPoint(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntPos = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen(CHECKPOINT_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_CHECKPOINT") == 0)
			{// �`�F�b�N�|�C���g���Ǎ�
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumCheckPoint);

				if (m_pPosCheckPoint == nullptr)
				{// ������̐���
					m_pPosCheckPoint = new D3DXVECTOR3[m_nNumCheckPoint];

					for (int i = 0; i < m_nNumCheckPoint; i++)
					{// ���̃N���A
						ZeroMemory(&m_pPosCheckPoint[i], sizeof(D3DXVECTOR3));
					}
				}
				else
				{
					break;
				}

				if (m_pPosCheckPoint == nullptr)
				{// �����ł��Ȃ������ꍇ
					break;
				}

				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "CHECKPOINTSET") == 0)
					{// �p�����[�^�[�Ǎ��J�n
						while (true)
						{
							// �����ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								for (int i = 0; i < 3; i++)
								{
									fscanf(pFile, "%f", &m_pPosCheckPoint[nCntPos][i]);
								}
							}

							if (strcmp(cTemp, "END_CHECKPOINTSET") == 0)
							{// �p�����[�^�[�Ǎ��I��
								nCntPos++;

								break;
							}
						}
					}

					if (m_nNumCheckPoint <= nCntPos)
					{
						break;
					}
				}
			}
			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �I������
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
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

	if (m_pPosCheckPoint != nullptr)
	{
		delete[] m_pPosCheckPoint;
		m_pPosCheckPoint = nullptr;
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
	//CInputKeyboard *pKeyboard = CManager::GetKeyboard();

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

	//if (pKeyboard != nullptr)
	//{
	//	if (pKeyboard->GetTrigger(DIK_RETURN))
	//	{
	//		if (pFade != nullptr)
	//		{
	//			//pFade->SetFade(CScene::MODE_RANKING);
	//		}
	//	}
	//}

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
		if (m_state == STATE_NORMAL)
		{
			// �v���C���[�̒Ǐ]
			pCamera->FollowPlayer();
		}
		else if (m_state == STATE_BOSS)
		{
			// �{�X��̓���
			pCamera->BossBattle();
		}
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
	{
		// �v���C���[�擾
		CPlayer *pPlayer = nullptr;
		pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 pos = pPlayer->GetPosition();

			if (pos.x >= BOSS_LINE)
			{// �{�X��ֈڍs
				CEnemyManager *pEnemyManager = nullptr;

				pEnemyManager = CEnemyManager::GetInstance();

				if (pEnemyManager != nullptr)
				{
					pEnemyManager->CreateEnemy(D3DXVECTOR3(BOSS_LINE,190.0f,0.0f), CEnemy::TYPE_BOSS);
				}

				m_state = STATE_BOSS;
			}

			if (m_nProgress < m_nNumCheckPoint - 1)
			{
				if (pos.x >= m_pPosCheckPoint[m_nProgress + 1].x)
				{// �`�F�b�N�|�C���g�̐ݒ�
					m_nProgress++;
				}
			}
		}
	}
		break;
	case CGame::STATE_BOSS:
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
	//CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//if (pKeyboard == nullptr)
	//{
	//	return;
	//}

	//if (pKeyboard->GetTrigger(DIK_F))
	//{
	//	m_bStop = m_bStop ? false : true;
	//}
}

//=====================================================
// �`�揈��
//=====================================================
void CGame::Draw(void)
{
	CManager::GetDebugProc()->Print("\n�i�s�󋵁F[%d]", m_nProgress);
}