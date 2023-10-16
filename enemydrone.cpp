//*****************************************************
//
// �����G�̏���[enemyshot.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemydrone.h"
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

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyDrone::CEnemyDrone()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyDrone::~CEnemyDrone()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyDrone::Init(void)
{
	// �p���N���X�̏�����
	CEnemy::Init();

	// �����̗̑͐ݒ�
	SetLife(INITIAL_LIFE);

	// �X�R�A�ݒ�
	SetScore(INITIAL_SCORE);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyDrone::Uninit(void)
{
	// �p���N���X�̏I��
	CEnemy::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyDrone::Update(void)
{
	// �ʒu��ۑ�
	SetPositionOld(GetPosition());

	// �p���N���X�̍X�V
	CEnemy::Update();
	
	// �U���̊Ǘ�
	ManageAttack();

	// �ڕW����������
	RotDest();
}

//=====================================================
// �U���Ǘ�
//=====================================================
void CEnemyDrone::ManageAttack(void)
{

}

//=====================================================
// �ڕW��������������
//=====================================================
void CEnemyDrone::RotDest(void)
{
	// �ڕW�擾
	CPlayer *pPlayer;
	if (CPlayer::GetInstance() != nullptr)
	{
		pPlayer = CPlayer::GetInstance();
	}
	else
	{
		return;
	}

	D3DXVECTOR3 posTarget = pPlayer->GetPosition();
	D3DXVECTOR3 pos = GetPosition();
	float fRot = 0.0f;

	if (posTarget.x <= pos.x)
	{// �E��
		fRot = D3DX_PI * 0.5f;
	}
	else
	{// ����
		fRot = -D3DX_PI * 0.5f;
	}

	// �ϐ��錾
	D3DXVECTOR3 vecDest;
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = fRot - rot.y;

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
// �`�揈��
//=====================================================
void CEnemyDrone::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();
}