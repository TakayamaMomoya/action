//*****************************************************
//
// �e�N�X�`���̊Ǘ�[texture.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include <string.h>

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CTexture::m_nNumAll = 0;	// ����
CTexture *CTexture::m_pTexture = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CTexture::CTexture()
{
	m_pTexture = this;

	ZeroMemory(&m_apFilename[0], sizeof(m_apFilename));
	ZeroMemory(&m_apTexture[0], sizeof(m_apTexture));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTexture::~CTexture()
{
	m_pTexture = nullptr;
}

//=====================================================
// ��������
//=====================================================
CTexture *CTexture::Create(void)
{
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != nullptr)
		{
			m_pTexture->Load();
		}
	}

	return m_pTexture;
}

//=====================================================
// �Ǎ�����
//=====================================================
HRESULT CTexture::Load(void)
{
	// �t�@�C�����̐ݒ�
	char *apFileName[MAX_TEX] = 
	{
	};

	for ( int nCntTex = 0;nCntTex < MAX_TEX;nCntTex++)
	{
		if (apFileName[nCntTex] != nullptr)
		{// �t�@�C��������������e�N�X�`���̓Ǎ�
			// �f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

			// �e�N�X�`���̓Ǎ�
			D3DXCreateTextureFromFile
			(pDevice, apFileName[nCntTex],&m_apTexture[nCntTex]);

			// �t�@�C�����ۑ�
			m_apFilename[nCntTex] = apFileName[nCntTex];

			// �����J�E���g�A�b�v
			m_nNumAll++;
		}
	}

	return S_OK;
}

//=====================================================
// �S�j������
//=====================================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != nullptr)
		{
			if (m_apTexture[nCntTex] != nullptr)
			{
				m_apTexture[nCntTex]->Release();
				m_apTexture[nCntTex] = nullptr;
				m_nNumAll--;
			}
		}
	}
}

//=====================================================
// �ʓǍ�
//=====================================================
int CTexture::Regist(const char *pFileName)
{
	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (m_apFilename[nCntTex] != nullptr)
		{
			if (strcmp(&m_apFilename[nCntTex][0], &pFileName[0]) == 0)
			{// �t�@�C�����������ꍇ�A���݂̔ԍ���Ԃ�
 				return nCntTex;
			}
		}
	}

	// �V�����e�N�X�`����ǂݍ��ޏꍇ��

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile
	(pDevice, pFileName, &m_apTexture[m_nNumAll]);

	m_apFilename[m_nNumAll] = new char[MAX_STRING];

	// �t�@�C�����̕ۑ�
	strcpy(m_apFilename[m_nNumAll], "\0");
	strcpy(m_apFilename[m_nNumAll], pFileName);

	// ���݂̔ԍ���ۑ�
	int nIdx = m_nNumAll;

	// �����J�E���g�A�b�v
	m_nNumAll++;

	return nIdx;
}

//=====================================================
// �A�h���X�擾����
//=====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx == -1)
	{
		return nullptr;
	}
	else
	{
		return m_apTexture[nIdx];
	}
}