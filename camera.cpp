//*****************************************************
//
// �J�����̏���[camera.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "debugproc.h"
#include "game.h"
#include "objectmanager.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MOVE_SPEED					(3.0f)						//�ړ��X�s�[�h
#define ROLL_SPEED					(0.02f)						//��]�X�s�[�h
#define MOVE_FACT					(0.3f)						//�ړ������W��
#define LIMIT_HEIGHT	(50)	// �ʒu�𐧌����鍂��
#define INITIAL_ANGLE	(45.0f)	// �����̎���p

//====================================================
// ����������
//====================================================
HRESULT CCamera::Init(void)
{
	ZeroMemory(&m_camera,sizeof(Camera));

	m_camera.posV = D3DXVECTOR3(0.0f, 50.0f, -500.0f);
	m_camera.posVOld = D3DXVECTOR3(0.0f, 30.0f, -450.0f);
	m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.fLength = 0.0f;
	m_camera.fViewAngle = INITIAL_ANGLE;

	float fLength = sqrtf
	(//Y�ʂł̑Ίp��
		(m_camera.posV.x - m_camera.posR.x) * (m_camera.posV.x - m_camera.posR.x) + 
		(m_camera.posV.z - m_camera.posR.z) * (m_camera.posV.z - m_camera.posR.z)
	);

	m_camera.fLength = sqrtf
	(//�ڕW�܂ł̒�������
		fLength * fLength + (m_camera.posV.y - m_camera.posR.y) * (m_camera.posV.y - m_camera.posR.y)
	);

	m_camera.rot.x = atan2f(fLength, m_camera.posV.y - m_camera.posR.y);

	SetPosV();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CCamera::Uninit(void)
{

}

//====================================================
// �X�V����
//====================================================
void CCamera::Update(void)
{
	CScene::MODE mode;

	mode = CManager::GetMode();

	switch (mode)
	{
	case CScene::MODE_TITLE:
		UpdateTitle();
		break;
	case CScene::MODE_GAME:
		UpdateGame();
		break;
	case CScene::MODE_RANKING:
		break;
	default:
		break;
	}
}

//====================================================
// �f�o�b�O����
//====================================================
void CCamera::Debug(void)
{
	// ���擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetPress(DIK_UP))
	{
		m_camera.fViewAngle += 0.4f;
	}
	if (pKeyboard->GetPress(DIK_DOWN))
	{
		m_camera.fViewAngle -= 0.4f;
	}
}

//====================================================
// �^�C�g���X�V
//====================================================
void CCamera::UpdateTitle(void)
{
	TitleMove();
}

//====================================================
// �Q�[���X�V
//====================================================
void CCamera::UpdateGame(void)
{
#ifdef DEBUG
	CManager::GetDebugProc()->Print("\n���_�̈ʒu�F[%f,%f,%f]", m_camera.posV.x, m_camera.posV.y, m_camera.posV.z);
#endif
}

//====================================================
// �J�����̓���
//====================================================
void CCamera::TitleMove(void)
{
	//�ڕW�̒����_�ݒ�
	m_camera.posRDest =
	{
		0.0f,
		180.0f,
		0.0f
	};

	m_camera.fLength = 240;

	//�ڕW�̎��_�ݒ�
	m_camera.posVDest =
	{
		m_camera.posRDest.x + sinf(m_camera.rot.x) * sinf(m_camera.rot.y - D3DX_PI * 0.02f) * m_camera.fLength,
		m_camera.posRDest.y + cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posRDest.z + sinf(m_camera.rot.x) * cosf(m_camera.rot.y - D3DX_PI * 0.02f) * m_camera.fLength
	};

	//�����_�␳
	m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * MOVE_FACT;
	m_camera.posR.y += (m_camera.posRDest.y - m_camera.posR.y) * MOVE_FACT;
	m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * MOVE_FACT;

	//���݂̎��_�␳
	m_camera.posV.x += (m_camera.posVDest.x - m_camera.posV.x) * MOVE_FACT;
	m_camera.posV.y += (m_camera.posVDest.y - m_camera.posV.y) * MOVE_FACT;
	m_camera.posV.z += (m_camera.posVDest.z - m_camera.posV.z) * MOVE_FACT;

	m_camera.rot.y += 0.01f;
}

//====================================================
// ���쏈��
//====================================================
void CCamera::Control(void)
{
	// ���͏�����
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputMouse *pMouse = CManager::GetMouse();

	float fMove = MOVE_SPEED;

	//�}�E�X����======================================================
	if (pMouse->GetPress(CInputMouse::BUTTON_RMB) == true)
	{//�E�N���b�N���A���_����
		D3DXVECTOR3 rot;

		//�}�E�X�̈ړ��ʑ��
		rot = { (float)pMouse->GetMoveIX() * ROLL_SPEED, (float)pMouse->GetMoveIY() * ROLL_SPEED, 0.0f };

		D3DXVec3Normalize(&rot, &rot);

		//���_�̐���
		m_camera.rot.y += rot.x * ROLL_SPEED;
		m_camera.rot.x -= rot.y * ROLL_SPEED;

		//�����_�𑊑Έʒu�ɐݒ�
		SetPosR();

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{//����
			fMove *= 3;
		}

		//���_�ړ�===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{//���ړ�
			m_camera.posV.x -= sinf(m_camera.rot.y - D3DX_PI * 0.5f) * fMove;
			m_camera.posV.z -= cosf(m_camera.rot.y - D3DX_PI * 0.5f) * fMove;
			SetPosR();
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{//�E�ړ�
			m_camera.posV.x -= sinf(m_camera.rot.y - D3DX_PI * -0.5f) * fMove;
			m_camera.posV.z -= cosf(m_camera.rot.y - D3DX_PI * -0.5f) * fMove;
			SetPosR();
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{//�O�ړ�
			m_camera.posV.x += sinf(m_camera.rot.x + D3DX_PI) * sinf(m_camera.rot.y) * fMove;
			m_camera.posV.y += cosf(m_camera.rot.x + D3DX_PI) * MOVE_SPEED;
			m_camera.posV.z += sinf(m_camera.rot.x + D3DX_PI) * cosf(m_camera.rot.y) * fMove;
			SetPosR();
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{//��ړ�
			m_camera.posV.x += sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * fMove;
			m_camera.posV.y += cosf(m_camera.rot.x) * MOVE_SPEED;
			m_camera.posV.z += sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * fMove;
			SetPosR();
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{//�㏸
			m_camera.posV.y += fMove;
			SetPosR();
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{//���~
			m_camera.posV.y -= fMove;
			SetPosR();
		}
	}
}

//====================================================
// �Ǐ]����
//====================================================
void CCamera::FollowPlayer(void)
{

}

//====================================================
// ���U���g�̃J��������
//====================================================
void CCamera::UpdateResult(void)
{

}

//====================================================
// �U������
//====================================================
void CCamera::Quake(void)
{
	//��ʐU��
	if (m_camera.nTimerQuake > 0)
	{
		//���Ԃ����炷
		m_camera.nTimerQuake--;

		//���_�����_�𓮂����ăJ������h�炷
		m_camera.posV.x += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * sinf(m_camera.rot.y);
		m_camera.posV.y += (float)(rand() % 101 - 50) * m_camera.fQuakeSizeV;
		m_camera.posV.z += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * cosf(m_camera.rot.y);

		m_camera.posR.x += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * sinf(m_camera.rot.y);
		m_camera.posR.y += (float)(rand() % 101 - 50) * m_camera.fQuakeSizeV;
		m_camera.posR.z += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * cosf(m_camera.rot.y);

		//���X�ɗh��̃T�C�Y������������
		m_camera.fQuakeSizeH += (0.0f - m_camera.fQuakeSizeH) * 0.03f;
		m_camera.fQuakeSizeV += (0.0f - m_camera.fQuakeSizeV) * 0.03f;
	}
}

//====================================================
// �U���ݒ�
//====================================================
void CCamera::SetQuake(float fQuakeSizeH, float fQuakeSizeV, int nTime)
{
	if (fQuakeSizeH > 0.0f && fQuakeSizeV > 0.0f)
	{
		//�h��鎞�ԑ��
		m_camera.nTimerQuake = nTime;

		//�h��̑傫�����
		m_camera.fQuakeSizeH = fQuakeSizeH;
		m_camera.fQuakeSizeV = fQuakeSizeV;
	}
}

//====================================================
//���_�ݒ�
//====================================================
void CCamera::SetPosV(void)
{
	m_camera.posV =
	{
		m_camera.posR.x + sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * m_camera.fLength,
		m_camera.posR.y + cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posR.z + sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * m_camera.fLength
	};
}

//====================================================
//�����_�ݒ�
//====================================================
void CCamera::SetPosR(void)
{
	m_camera.posR =
	{
		m_camera.posV.x - sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * m_camera.fLength,
		m_camera.posV.y - cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posV.z - sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * m_camera.fLength
	};
}

//====================================================
//�ݒ菈��
//====================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X==================================================
	//�v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(m_camera.fViewAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		MIN_DRAW,
		MAX_DRAW);

	/*D3DXMatrixOrthoLH(&m_camera.mtxProjection,	// ���s���e�̂���
		720,	// ����
		1280,	// ��
		MIN_DRAW,
		MAX_DRAW);*/

	//�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&m_camera.mtxProjection);

	//�r���[�}�g���b�N�X============================================================
	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&m_camera.mtxView);

	//�r���[�}�g���b�N�X�쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.vecU);

	//�r���[�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

//====================================================
//���擾����
//====================================================
CCamera::Camera *CCamera::GetCamera(void)
{
	return &m_camera;
}