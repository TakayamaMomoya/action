//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "score.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyshot.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(1.0f)	// �ړ����x
#define RATE_RADIUS	(1.5f)	// �����蔻��̑傫���̔{��
#define INITIAL_LIFE	(1.0f)	// �����̗�
#define DAMAGE_FRAME	(10)	// �_���[�W��Ԃ̌p���t���[����
#define INITIAL_SCORE	(1000)	// �����X�R�A

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CEnemy::m_nNumAll = 0;	// ����
CEnemy *CEnemy::m_pHead = nullptr;	// �擪�̃A�h���X
CEnemy *CEnemy::m_pTail = nullptr;	// �Ō���̃A�h���X

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemy::CEnemy()
{
	// �����J�E���g�A�b�v
	m_nNumAll++;

	m_fLife = 0;
	m_nScore = 0;
	m_nTimerState = 0;
	m_pCollisionSphere = nullptr;
	m_state = STATE_NORMAL;

	// �l�̃N���A
	m_pPrev = nullptr;
	m_pNext = nullptr;

	if (m_pHead == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		m_pHead = this;
		m_pTail = this;

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = m_pTail;

	// �Ō���̃A�h���X�������ɂ���
	m_pTail = this;

	// �O�̃I�u�W�F�N�g�̎��̃A�h���X�������ɂ���
	m_pPrev->m_pNext = this;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemy::~CEnemy()
{
	if (m_state != STATE_DEATH)
	{
		m_nNumAll--;
	}

	if (m_pHead == this)
	{// �擪�A�h���X�̔j��
	 //if (m_pNext != nullptr)
		{// �擪�A�h���X�����̃A�h���X�Ɉ����p��
			m_pHead = m_pNext;

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}
	else if (m_pTail == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
			m_pTail = m_pPrev;

			m_pPrev->m_pNext = nullptr;
		}
	}
	else
	{// �^�񒆂̃A�h���X�̔j��
	 // �O�̃A�h���X���玟�̃A�h���X���Ȃ�
		m_pPrev->m_pNext = m_pNext;

		// ���̃A�h���X����O�̃A�h���X���Ȃ�
		m_pNext->m_pPrev = m_pPrev;
	}
}

//=====================================================
// ��������
//=====================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// �C���X�^���X����
		switch (type)
		{
		case TYPE_SHOT:

			pEnemy = new CEnemyShot;

			pEnemy->CMotion::Load("data\\MOTION\\robot00.txt");

			pEnemy->SetMotion(0);

			break;
		default:
			break;
		}

		// �ʒu�ݒ�
		pEnemy->SetPosition(pos);

		// ����������
		pEnemy->Init();
	}

	return pEnemy;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemy::Init(void)
{
	// �ł��傫���p�[�c�̔��a�擾
	float fRadius = GetRadiusMax();

	// �p���N���X�̏�����
	CMotion::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	if (m_pCollisionSphere == nullptr)
	{// ���̓����蔻�萶��
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMY, CCollision::TYPE_SPHERE,this);

		if (m_pCollisionSphere != nullptr)
		{// ���̐ݒ�
			m_pCollisionSphere->SetPosition(GetPosition());
			m_pCollisionSphere->SetRadius(fRadius * RATE_RADIUS);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_ENEMY, this);

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,-fRadius,-fRadius };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	// �̗͂̏����ݒ�
	m_fLife = INITIAL_LIFE;

	// �ʏ��Ԃɂ���
	m_state = STATE_NORMAL;

	m_nScore = INITIAL_SCORE;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemy::Update(void)
{
	// �p���N���X�̍X�V
	CMotion::Update();

	// ��ԊǗ�����
	ManageState();

	// �ʒu�̍X�V
	SetPosition(GetPosition() + GetMove());

	// �����蔻��Ǘ�
	ManageCollision();
}

//=====================================================
// �����蔻��̊Ǘ�
//=====================================================
void CEnemy::ManageCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// ���̓����蔻��̊Ǘ�
		m_pCollisionSphere->SetPositionOld(m_pCollisionSphere->GetPosition());

		m_pCollisionSphere->SetPosition(GetPosition());
	}

	if (m_pCollisionCube != nullptr)
	{// �����̂̓����蔻��̊Ǘ�
	 // �p�[�c�̍ő唼�a�擾
		float fRadius = GetRadiusMax();

		// �����蔻��̈ʒu�ݒ�
		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,10.0f,-fRadius };

		D3DXVECTOR3 move = GetMove();

		// �����o���̓����蔻��
		m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemy::ManageState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		if (m_nTimerState > DAMAGE_FRAME)
		{// �ʏ��Ԃɖ߂�
			m_nTimerState = 0;
			m_state = STATE_NORMAL;
		}
		else
		{// �J�E���g�A�b�v
			m_nTimerState++;
		}

		break;
	case STATE_DEATH:



		break;
	default:
		break;
	}
}

//=====================================================
// �̗͐ݒ�
//=====================================================
void CEnemy::SetLife(float fLife)
{
	m_fLife = fLife;

	if (m_fLife < 0)
	{
		m_fLife = 0;
	}
}

//=====================================================
// �q�b�g����
//=====================================================
void CEnemy::Hit(float fDamage)
{
	Death();
}

//=====================================================
// ���S����
//=====================================================
void CEnemy::Death(void)
{
	// ���g�̏I��
	Uninit();
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �}�g���b�N�X�̐ݒ�
	SetMatrix();

	// �p���N���X�̕`��
	CMotion::Draw();

#ifdef _DEBUG
	CManager::GetDebugProc()->Print("\n�G�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetDebugProc()->Print("\n�G�̔��a�F[%f]", m_pCollisionSphere->GetRadius());
#endif
}

//=====================================================
// ���̓����蔻��̈ʒu�ݒ�
//=====================================================
void CEnemy::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{// �ʒu�ݒ�
		m_pCollisionSphere->SetPosition(pos);
	}
}

//=====================================================
// �Ǎ�����
//=====================================================
void CEnemy::Load(void)
{

}