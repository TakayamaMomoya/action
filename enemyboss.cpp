//*****************************************************
//
// �{�X�G�̏���[enemyboss.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemyboss.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "bullet.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define INITIAL_LIFE	(5)	// �����̗�
#define INITIAL_SCORE	(500)	// �����X�R�A
#define TIME_SHOT	(240)	// �ˌ��܂ł̃J�E���^�[
#define ROLL_FACT	(0.1f)	// ��]�W��
#define BULLET_SPEED	(2.0f)	// �e�̑��x
#define BULLET_SIZE	(2.5f)	// �e�̑傫��
#define GRAVITY	(0.3f)	// �d��

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBoss::CEnemyBoss()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBoss::~CEnemyBoss()
{

}

//=====================================================
// ��������
//=====================================================
CEnemyBoss *CEnemyBoss::Create(void)
{
	if (m_pEnemyBoss == nullptr)
	{
		m_pEnemyBoss = new CEnemyBoss;
	}

	return m_pEnemyBoss;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyBoss::Init(void)
{
	// �p���N���X�̏�����
	CEnemy::Init();

	// �����̗̑͐ݒ�
	SetLife(INITIAL_LIFE);

	// �X�R�A�ݒ�
	SetScore(INITIAL_SCORE);

	// ���[�V�����ݒ�
	SetMotion(MOTION_APPER);

	// �o���n�_���킹
	SetMatrix();
	CMotion::Update();
	CMotion::Update();

	FollowCollision();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyBoss::Uninit(void)
{
	CGame::SetState(CGame::STATE_END);

	m_pEnemyBoss = nullptr;

	// �p���N���X�̏I��
	CEnemy::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyBoss::Update(void)
{
	// �ʒu��ۑ�
	SetPositionOld(GetPosition());

	// �p���N���X�̍X�V
	CEnemy::Update();
	
	// �����蔻��Ǘ�
	ManageCollision();

	// �U���̊Ǘ�
	ManageAttack();

	// �d��
	D3DXVECTOR3 move = GetMove();

	move.y -= GRAVITY;

	SetMove(move);

	if (GetState() == STATE_DEATH)
	{
		Death();
	}
}

//=====================================================
// �����蔻��Ǘ�
//=====================================================
void CEnemyBoss::ManageCollision(void)
{
	// �����蔻��Ǐ]
	FollowCollision();
}

//=====================================================
// ������̒Ǐ]
//=====================================================
void CEnemyBoss::FollowCollision(void)
{
	CCollisionSphere *pCollision = GetClsnSphere();

	if (GetParts(0) != nullptr)
	{
		D3DXMATRIX mtx = *GetParts(0)->m_pParts->GetMatrix();
		D3DXVECTOR3 pos =
		{
			mtx._41,
			mtx._42,
			mtx._43,
		};

		pCollision->SetPositionOld(pCollision->GetPosition());
		pCollision->SetPosition(pos);
	}
}

//=====================================================
// �U���Ǘ�
//=====================================================
void CEnemyBoss::ManageAttack(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyBoss::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();

#ifdef _DEBUG
	CManager::GetDebugProc()->Print("\n�{�X���[�V�����F[%d]", GetMotion());
	CManager::GetDebugProc()->Print("\n�L�[�F[%d]", GetKey());
	CManager::GetDebugProc()->Print("\n�t���[���F[%d]", GetFrame());
	CManager::GetDebugProc()->Print("\nIsFinish�F[%d]", IsFinish());
#endif
}