//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "debugproc.h"
#include "particle.h"
#include "sound.h"
#include "collision.h"
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "collision.h"
#include "universal.h"
#include "game.h"
#include <stdio.h>
#include "motion.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define BODY_PATH	"data\\MOTION\\motionArms00.txt"	// �����ڂ̃p�X
#define SPEED_MOVE	(2.0f)	// �ړ����x
#define GRAVITY	(0.98f)	// �d��
#define JUMP_POW	(1.2f)	// �W�����v��
#define MOVE_FACT	(0.8f)	// �ړ��ʌ���
#define ROLL_FACT	(0.2f)	// ��]�W��

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	m_nLife = 0;
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_rotDest = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_bSprint = false;
	m_pBody = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CPlayer::Init(void)
{
	// �l�̏�����
	m_nLife = INITIAL_LIFE_PLAYER;
	
	if (m_pBody == nullptr)
	{// �̂̐���
		m_pBody = CMotion::Create(BODY_PATH);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPlayer::Uninit(void)
{
	if (m_pBody != nullptr)
	{// �̂̔j��
		m_pBody->Uninit();
		m_pBody = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// �O��̈ʒu��ۑ�
	m_posOld = m_pos;

	// ���쏈��
	Input();

	// �ڕW��������������
	RotDest();

	// �ʒu�Ɉړ��ʂ𔽉f
	m_pos += m_move;

	if (m_pBody != nullptr)
	{// �̂̒Ǐ]
		m_pBody->SetPosition(m_pos);
		m_pBody->SetRot(m_rot);
	}

	// �ړ��ʌ���
	m_move *= MOVE_FACT;
}

//=====================================================
// ���쏈��
//=====================================================
void CPlayer::Input(void)
{
	// ���͏�����
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �ړ�����
	InputMove();

	// �J��������
	InputCamera();
}

//=====================================================
// �ړ�����
//=====================================================
void CPlayer::InputMove(void)
{
	// ������
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputMouse *pMouse = CManager::GetMouse();
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// �ϐ��錾
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecStick;

	if (pKeyboard->GetPress(DIK_A))
	{// ���ړ�
		move.x -= SPEED_MOVE;
		m_rotDest.y = D3DX_PI * 0.5f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{// �E�ړ�
		move.x += SPEED_MOVE;
		m_rotDest.y = -D3DX_PI * 0.5f;
	}

	// �ړ��ʉ��Z
	SetMove(GetMove() + move);
}

//=====================================================
// �ڕW��������������
//=====================================================
void CPlayer::RotDest(void)
{
	// �ϐ��錾
	D3DXVECTOR3 vecDest;
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = m_rotDest.y - rot.y;

	// �p�x�̏C��
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	// �p�x�␳
	SetRot(D3DXVECTOR3(rot.x, rot.y + fRotDiff * ROLL_FACT, rot.z));

	// �p�x�̏C��
	rot = GetRot();

	if (GetRot().y > D3DX_PI)
	{
		// �p�x�␳
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y - 6.28f, GetRot().z));
	}
	if (GetRot().y < -D3DX_PI)
	{
		// �p�x�␳
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y + 6.28f, GetRot().z));
	}
}

//=====================================================
// �J��������
//=====================================================
void CPlayer::InputCamera(void)
{

}

//=====================================================
// �q�b�g����
//=====================================================
void CPlayer::Hit(float fDamage)
{
	m_nLife -= (int)fDamage;

	if (m_nLife <= 0)
	{// ���S����
		m_nLife = 0;

		Uninit();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CPlayer::Draw(void)
{
	if (m_pBody != nullptr)
	{
		m_pBody->SetMatrix();
	}

#ifdef _DEBUG
	CManager::GetDebugProc()->Print("\n�v���C���[�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetDebugProc()->Print("\n�v���C���[�̗�[%d]", m_nLife);
	CManager::GetDebugProc()->Print("\n���Z�b�g[F3]");
#else
	CManager::GetDebugProc()->Print("\n\n\n\n\n\n\n\n\n\n\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("// �v���C���[��{����\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("[WASD]�ړ�\n");
	CManager::GetDebugProc()->Print("[LSHIFT + �ړ�]�_�b�V��\n");
	CManager::GetDebugProc()->Print("[SPACE]�W�����v\n");
	CManager::GetDebugProc()->Print("[LMB]�ˌ�\n");
	CManager::GetDebugProc()->Print("[RMB]�Y�[��\n");
	CManager::GetDebugProc()->Print("\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("// �ˌ��̎��\n");
	CManager::GetDebugProc()->Print("//----------------------------\n");
	CManager::GetDebugProc()->Print("[�Z����]�P������\n");
	CManager::GetDebugProc()->Print("[������]�`���[�W�V���b�g\n");
	CManager::GetDebugProc()->Print("[�_�u���N���b�N��������]�A��\n");
#endif
}

//=====================================================
// ��������
//=====================================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{// �C���X�^���X����
		pPlayer = new CPlayer;

		// ����������
		pPlayer->Init();
	}

	return pPlayer;
}

//=====================================================
// �e�N�X�`���j��
//=====================================================
void CPlayer::Unload(void)
{

}