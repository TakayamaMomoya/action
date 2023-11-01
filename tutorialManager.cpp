//*****************************************************
//
// �`���[�g���A���}�l�[�W���[[tutorialManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "tutorialManager.h"
#include "manager.h"
#include "animation2D.h"
#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
#define FILE_PATH	"data\\MAP\\enemies.txt"	// �z�u�f�[�^�̃p�X

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CTutorialManager *CTutorialManager::m_pTutorialManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CTutorialManager::CTutorialManager()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTutorialManager::~CTutorialManager()
{

}

//=====================================================
// ��������
//=====================================================
CTutorialManager *CTutorialManager::Create(void)
{
	if (m_pTutorialManager == nullptr)
	{// �C���X�^���X����
		m_pTutorialManager = new CTutorialManager;

		// ����������
		m_pTutorialManager->Init();
	}

	return m_pTutorialManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTutorialManager::Init(void)
{
	// �Ǎ�����
	Load();

	return S_OK;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CTutorialManager::Load(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntAttack = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

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
void CTutorialManager::Uninit(void)
{
	m_pTutorialManager = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CTutorialManager::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CTutorialManager::Draw(void)
{
#ifdef _DEBUG
	//CDebugProc::GetInstance()->Print("\n�G�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
#endif
}