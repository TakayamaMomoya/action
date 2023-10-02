//*****************************************************
//
// �w�i�̏���[bg.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "bg.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
LPDIRECT3DTEXTURE9 CBg::m_pTexture = nullptr;	// �e�N�X�`���̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	m_fSpeedU = 0.0f;
	m_fSpeedV = 0.0f;
	m_texLeftUp = { 0.0f,0.0f };
	m_texRightDown = { 0.0f,0.0f };
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBg::~CBg()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CBg::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �p���N���X�̏�����
	CObject2D::Init();

	m_texLeftUp = { 0.0f,0.0f };
	m_texRightDown = { 1.0f,1.0f };

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBg::Uninit(void)
{
	// �p���N���X�̏I��
	CObject2D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CBg::Update(void)
{
	m_texLeftUp.x += m_fSpeedU;
	m_texLeftUp.y += m_fSpeedV;
	m_texRightDown.x += m_fSpeedU;
	m_texRightDown.y += m_fSpeedV;

	if (m_texLeftUp.x > 1.0f)
	{
		m_texLeftUp.x -= 1.0f;
		m_texRightDown.x -= 1.0f;
	}

	if (m_texLeftUp.y > 1.0f)
	{
		m_texLeftUp.y -= 1.0f;
		m_texRightDown.y -= 1.0f;
	}

	// �p���N���X�̍X�V
	CObject2D::Update();

	// ���_���ݒ�
	SetVtx();

	// �e�N�X�`�����W�X�V
	SetTex(m_texLeftUp, m_texRightDown);
}

//=====================================================
// �`�揈��
//=====================================================
void CBg::Draw(void)
{
	// �p���N���X�̕`��
	CObject2D::Draw();
}

//=====================================================
// �Ǎ�����
//=====================================================
HRESULT CBg::Load(void)
{
	if (m_pTexture == nullptr)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		D3DXCreateTextureFromFile
		(
			pDevice,
			"data\\TEXTURE\\BG\\bg101.jpg",
			&m_pTexture
		);
	}

	return S_OK;
}

//=====================================================
// �j������
//=====================================================
void CBg::Unload(void)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//=====================================================
// �X�N���[�����x�ݒ菈��
//=====================================================
void CBg::SetScroll(float fSpeedV, float fSpeedU)
{
	m_fSpeedV = fSpeedV;
	m_fSpeedU = fSpeedU;
}

//=====================================================
// ��������
//=====================================================
CBg *CBg::Create(void)
{
	CBg *pBg = nullptr;

	if (pBg == nullptr)
	{// �C���X�^���X����
		pBg = new CBg;

		// ����������
		pBg->Init();
		pBg->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	return pBg;
}
