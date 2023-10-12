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
#include "afterimage.h"
#include "effect3D.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define BODY_PATH	"data\\MOTION\\rayleigh.txt"	// �����ڂ̃p�X
#define SPEED_MOVE	(0.3f)	// �ړ����x
#define GRAVITY	(0.09f)	// �d��
#define JUMP_POW	(2.5f)	// �W�����v��
#define MOVE_FACT	(0.8f)	// �ړ��ʌ���
#define ROLL_FACT	(0.2f)	// ��]�W��
#define LINE_STOP	(0.3f)	// �����Ă锻��̂������l
#define TIME_AFTERIMAGE	(4)	// �c�����o���p�x
#define ATTACK_JUMP	(2.8f)	// �󒆍U���̃W�����v��

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CPlayer *CPlayer::m_pPlayer = nullptr;	// ���g�̃|�C���^

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	m_nLife = 0;
	m_nCntAfterImage = 0;
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_rotDest = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_bJump = false;
	m_bSprint = false;
	m_bAttack = false;
	m_pBody = nullptr;
	m_pCollisionCube = nullptr;
	m_pClsnAttack = nullptr;
	m_pAttackInfo = nullptr;
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
	// ���̓Ǎ�
	Load();

	SetPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	// �l�̏�����
	m_nLife = INITIAL_LIFE_PLAYER;
	
	if (m_pBody == nullptr)
	{// �̂̐���
		m_pBody = CMotion::Create(BODY_PATH);
	}

	if (m_pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		D3DXVECTOR3 vtxMax = { 5.0f,20.0f,5.0f };
		D3DXVECTOR3 vtxMin = { -5.0f,0.0f,-5.0f };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	if (m_pClsnAttack == nullptr)
	{// ���̓����蔻�萶��
		m_pClsnAttack = CCollisionSphere::Create(CCollision::TAG_NONE, CCollision::TYPE_SPHERE, this);

		if (m_pClsnAttack != nullptr)
		{// ���̐ݒ�
			m_pClsnAttack->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_pClsnAttack->SetRadius(0.0f);
		}
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

	if (m_pCollisionCube != nullptr)
	{// �����蔻��j��
		m_pCollisionCube->Uninit();
		m_pCollisionCube = nullptr;
	}

	if (m_pClsnAttack != nullptr)
	{// �U�������蔻��j��
		m_pClsnAttack->Uninit();
		m_pClsnAttack = nullptr;
	}

	if (m_pPlayer != nullptr)
	{// ���g�̃|�C���^����ɂ���
		m_pPlayer = nullptr;
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

	// ���[�V�����̊Ǘ�
	ManageMotion();

	// �ڕW��������������
	RotDest();

	// �ʒu�Ɉړ��ʂ𔽉f
	m_pos += m_move;

	// �����蔻��Ǘ�
	ManageCollision();

	if (m_pBody != nullptr)
	{// �̂̒Ǐ]
		m_pBody->SetPosition(m_pos);
		m_pBody->SetRot(m_rot);
	}

	// �ړ��ʌ���
	m_move.x *= MOVE_FACT;
	m_move.y -= GRAVITY;
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

	// �U������
	InputAttack();

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

	if (pKeyboard == nullptr || pMouse == nullptr)
	{
		return;
	}

	// �ϐ��錾
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecStick;

	if (m_pBody->GetMotion() != MOTION_ATTACK)
	{
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

		// �W�����v����
		if (m_bJump == false)
		{
			if (pKeyboard->GetTrigger(DIK_SPACE))
			{// �E�ړ�
				move.y += JUMP_POW;

				m_bJump = true;

				SetMotion(MOTION_JUMP);
			}
		}

		// �ړ��ʉ��Z
		SetMove(GetMove() + move);
	}
}

//=====================================================
// �U������
//=====================================================
void CPlayer::InputAttack(void)
{
	// ������
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputMouse *pMouse = CManager::GetMouse();
	CInputJoypad *pJoypad = CManager::GetJoypad();

	if (pKeyboard == nullptr || pMouse == nullptr)
	{
		return;
	}

	if (pMouse->GetTrigger(CInputMouse::BUTTON_LMB))
	{// �U��
		if (m_bJump)
		{// �󒆍U��
			SetMotion(MOTION_AIRATTACK);

			D3DXVECTOR3 move = { GetMove().x,ATTACK_JUMP,GetMove().z };

			// �ړ��ʉ��Z
			SetMove(move);
		}
		else
		{// �n��U��
			if (m_pBody->GetMotion() == MOTION_ATTACK || m_pBody->GetMotion() == MOTION_ATTACKTURN)
			{
				m_bAttack = true;
			}
			else
			{
				SetMotion(MOTION_ATTACK);

				m_bAttack = true;
			}
		}
	}

	if (m_pBody != nullptr)
	{// �A���̏���
		if (m_pBody->IsFinish())
		{
			if (m_bAttack == true)
			{
				if (m_pBody->GetMotion() == MOTION_ATTACK)
				{
					SetMotion(MOTION_ATTACKTURN);

					m_bAttack = false;
				}
				else
				{
					SetMotion(MOTION_ATTACK);

					m_bAttack = false;
				}
			}
		}
	}
}

//=====================================================
// ���[�V�����̊Ǘ�
//=====================================================
void CPlayer::ManageMotion(void)
{
	if (m_pBody == nullptr)
	{
		return;
	}

	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	bool bFinish = m_pBody->IsFinish();
	int nMotion = m_pBody->GetMotion();

	if (m_bJump == false)
	{
		if (m_bAttack == false &&
			(m_pBody->GetMotion() != MOTION_ATTACK && m_pBody->GetMotion() != MOTION_ATTACKTURN))
		{// �ړ����[�V����
			if (move.x * move.x > LINE_STOP * LINE_STOP)
			{// ������x�����Ă���Ε������[�V����
				SetMotion(MOTION_MOVE);
			}
			else
			{// �ҋ@���[�V�����ֈڍs
				SetMotion(MOTION_NEUTRAL);

				m_nCntAfterImage = 0;
			}
		}
		else
		{// �U�����[�V�����Ǘ�
			if (bFinish == true)
			{
				SetMotion(MOTION_NEUTRAL);
			}
		}
	}
	else
	{
		if (
			move.y < 0.0f && 
			(nMotion == MOTION_AIRATTACK && bFinish == false) == false
			)
		{// �������[�V����
			SetMotion(MOTION_FALL);
		}
	}

	// �ړ��ʂ̌v�Z
	float fSpeed = D3DXVec3Length(&move);

	if (fSpeed * fSpeed > LINE_STOP * LINE_STOP)
	{
		m_nCntAfterImage++;

		if (m_nCntAfterImage >= TIME_AFTERIMAGE)
		{
			// �c���̐���
			m_pBody->SetAfterImage(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20);

			m_nCntAfterImage = 0;
		}
	}
}

//=====================================================
// �����蔻��̊Ǘ�
//=====================================================
void CPlayer::ManageCollision(void)
{
	bool bLandFloor = false;
	bool bLandBlock = false;

	if (m_pCollisionCube != nullptr)
	{// �����蔻��̊Ǘ�

		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// �����o���̓����蔻��
		bLandBlock = m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);
	}

	// ���̏�����=============
	if (m_pos.y <= -190.0f)
	{
		m_pos = 
		{
			0.0f,
			10.0f,
			0.0f
		};

		m_posOld = m_pos;

		m_move =
		{
			0.0f,
			0.0f,
			0.0f
		};
	}
	// =======================

	if (bLandBlock || bLandFloor)
	{
		m_bJump = false;
	}
	else
	{
		m_bJump = true;
	}

	// �U������̊Ǘ�
	ManageAttack();
}

//=====================================================
// �U������̊Ǘ�
//=====================================================
void CPlayer::ManageAttack(void)
{
	if (m_pClsnAttack == nullptr)
	{// ����̃G���[
		return;
	}

	if (m_pBody == nullptr)
	{// ���[�V�����̃G���[
		return;
	}

	CUniversal *pUniversal = CManager::GetUniversal();

	for (int i = 0; i < m_nNumAttack; i++)
	{
		if (m_pBody->GetMotion() == m_pAttackInfo[i].nIdxMotion)
		{// �U�����[�V�������̔���
			int nFrame = m_pBody->GetFrame();
			int nKey = m_pBody->GetKey();
			D3DXVECTOR3 pos;

			if (nFrame == m_pAttackInfo[i].nFrame && nKey == m_pAttackInfo[i].nKey)
			{// �����蔻��̐ݒ�
				bool bHit = false;
				D3DXMATRIX mtx;

				pUniversal->SetOffSet(&mtx, *m_pBody->GetMatrix(), m_pAttackInfo[i].pos);

				pos =
				{
					mtx._41,
					mtx._42,
					mtx._43
				};

				// �ʒu�ݒ�
				m_pClsnAttack->SetPosition(pos);
				
				// ���a�̐ݒ�
				m_pClsnAttack->SetRadius(m_pAttackInfo[i].fRadius);

				CEffect3D::Create(pos, m_pAttackInfo[i].fRadius, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// �����������̔���
				bHit = m_pClsnAttack->SphereCollision(CCollision::TAG_ENEMY);
				
				// ���������I�u�W�F�N�g�̎擾
				CObject *pObj = m_pClsnAttack->GetOther();

				if (bHit == true && pObj != nullptr)
				{// �������̃q�b�g����
					pObj->Hit(1.0f);
				}
			}
		}
	}
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
// ���[�V�����ݒ�
//=====================================================
void CPlayer::SetMotion(MOTION motion)
{
	if (m_pBody == nullptr)
	{
		return;
	}

	if (m_pBody->GetMotion() != motion)
	{
		// ���[�V�����ݒ�
		m_pBody->SetMotion(motion);
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
	CManager::GetDebugProc()->Print("\n���[�V����[%d]", m_pBody->GetMotion());
	CManager::GetDebugProc()->Print("\n�U��[%d]", m_bAttack);
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
	if (m_pPlayer == nullptr)
	{// �C���X�^���X����
		m_pPlayer = new CPlayer;

		// ����������
		m_pPlayer->Init();
	}

	return m_pPlayer;
}

//=====================================================
// ���Ǎ�
//=====================================================
void CPlayer::Load(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntAttack = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen("data\\player.txt", "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_ATTACK") == 0)
			{// �U������Ǎ��J�n
				// �U�����萔�Ǎ�
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumAttack);
				
				if (m_pAttackInfo == nullptr)
				{// ������̐���
					m_pAttackInfo = new AttackInfo[m_nNumAttack];

					for (int i = 0; i < m_nNumAttack; i++)
					{// ���̃N���A
						ZeroMemory(&m_pAttackInfo[i], sizeof(AttackInfo));
					}
				}
				else
				{
					break;
				}

				if (m_pAttackInfo == nullptr)
				{// �����ł��Ȃ������ꍇ
					break;
				}

				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "ATTACKSET") == 0)
					{// �p�����[�^�[�Ǎ��J�n
						while (true)
						{
							// �����ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "MOTION") == 0)
							{// ���[�V�����̎��
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_pAttackInfo[nCntAttack].nIdxMotion);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &m_pAttackInfo[nCntAttack].pos[nCntPos]);
								}
							}

							if (strcmp(cTemp, "KEY") == 0)
							{// �L�[�̔ԍ�
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_pAttackInfo[nCntAttack].nKey);
							}

							if (strcmp(cTemp, "FRAME") == 0)
							{// �t���[���ԍ�
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_pAttackInfo[nCntAttack].nFrame);
							}

							if (strcmp(cTemp, "RADIUS") == 0)
							{// ���a
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_pAttackInfo[nCntAttack].fRadius);
							}

							if (strcmp(cTemp, "END_ATTACKSET") == 0)
							{// �p�����[�^�[�Ǎ��I��
								nCntAttack++;

								break;
							}
						}
					}

					if (m_nNumAttack <= nCntAttack)
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