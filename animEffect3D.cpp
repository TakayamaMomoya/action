//*****************************************************
//
// �RD�A�j���[�V�����G�t�F�N�g����[animEffect3D.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "animEffect3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "anim3D.h"
#include <stdio.h>

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CAnimEffect3D *CAnimEffect3D::m_pAnimEffect3D = nullptr;	// ���g�̃|�C���^

//*****************************************************
// �}�N����`
//*****************************************************
#define FILE_PATH	"data\\TEXT\\animEffect3D.txt"	// �t�@�C���̃p�X

//=====================================================
// �R���X�g���N�^
//=====================================================
CAnimEffect3D::CAnimEffect3D(int nPriority) : CObject(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CAnimEffect3D::~CAnimEffect3D()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CAnimEffect3D::Init(void)
{
	// �Ǎ�
	Load();

	return S_OK;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CAnimEffect3D::Load(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntEffect = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "EFFECTSET") == 0)
			{// �Ǎ��J�n
				if (m_apAnimEffect[nCntEffect] == nullptr)
				{
					// �C���X�^���X����
					m_apAnimEffect[nCntEffect] = new SInfoAnimEffect;
				}

				SInfoAnimEffect *pInfo = m_apAnimEffect[nCntEffect];

				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "END_EFFECTSET") == 0)
					{// �I������
						break;
					}

					if (strcmp(cTemp, "PATH") == 0)
					{// �p�X
						fscanf(pFile, "%s", &cTemp[0]);
						
						fscanf(pFile, "%s", &pInfo->acPath[0]);
					}

					if (strcmp(cTemp, "NUM_ANIM") == 0)
					{// �A�j���[�V������
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_apAnimEffect[nCntEffect]->nNumAnim);
					}

					if (strcmp(cTemp, "SPEED_ANIM") == 0)
					{// �A�j���[�V�������x
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_apAnimEffect[nCntEffect]->nSpeedAnim);
					}
				}

				// �p�[�e�B�N�������Z
				nCntEffect++;
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
void CAnimEffect3D::Uninit(void)
{
	m_pAnimEffect3D = nullptr;

	for (int i = 0; i < TYPE_MAX; i++)
	{
		if (m_apAnimEffect[i] != nullptr)
		{
			delete m_apAnimEffect[i];
			m_apAnimEffect[i] = nullptr;
		}
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CAnimEffect3D::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CAnimEffect3D::Draw(void)
{

}

//=====================================================
// ��������
//=====================================================
CAnimEffect3D *CAnimEffect3D::Create(void)
{
	if (m_pAnimEffect3D == nullptr)
	{
		m_pAnimEffect3D = new CAnimEffect3D;

		if (m_pAnimEffect3D != nullptr)
		{
			// ����������
			m_pAnimEffect3D->Init();
		}
	}

	return m_pAnimEffect3D;
}

//=====================================================
// �A�j���[�V�����̐���
//=====================================================
CAnim3D *CAnimEffect3D::CreateEffect(D3DXVECTOR3 pos, TYPE type)
{
	if ((type >= TYPE_MAX || type < 0 ) && 
		m_apAnimEffect[type] != nullptr)
	{// �G���[
		return nullptr;
	}

	CAnim3D *pAnim3D = nullptr;

	// �C���X�^���X����
	pAnim3D = CAnim3D::Create(pos, m_apAnimEffect[type]->nNumAnim, m_apAnimEffect[type]->nSpeedAnim);

	if (pAnim3D != nullptr)
	{
		CTexture *pTexture = CTexture::GetInstance();

		if (pTexture != nullptr)
		{// �e�N�X�`���̐ݒ�
			int nIdx = pTexture->Regist(&m_apAnimEffect[type]->acPath[0]);
			pAnim3D->SetIdxTexture(nIdx);
		}
	}

	return pAnim3D;
}