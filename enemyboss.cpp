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
#include "missile.h"
#include "effect3D.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define INITIAL_LIFE	(50.0f)	// �����̗�
#define INITIAL_SCORE	(500)	// �����X�R�A
#define TIME_SHOT	(240)	// �ˌ��܂ł̃J�E���^�[
#define ROLL_FACT	(0.1f)	// ��]�W��
#define BULLET_SPEED	(2.0f)	// �e�̑��x
#define BULLET_SIZE	(2.5f)	// �e�̑傫��
#define GRAVITY	(0.3f)	// �d��
#define TIME_MISSILE	(20)	// �~�T�C�����˕p�x
#define MISSILE_UP	(3.0f)	// �~�T�C���̏���
#define NUM_MISSILE	(3)	// �~�T�C���̔��ː�
#define MOVE_FACT	(0.04f)	// �ړ��W��
#define LINE_END	(5.0f)	// �ړ��I���̂������l
#define MID_POINT	(2740.0f)	// �^�񒆂̒l
#define WIDTH_STAGE	(160.0f)	// �X�e�[�W�̕�
#define DAMAGE_FRAME	(20)	// �_���[�W��Ԃ̎���
#define FLOAT_HEIGTH	(180.0f)	// ����
#define SHOT_TIME	(3)	// �ˌ��̕p�x

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBoss::CEnemyBoss()
{
	// ���g�̏����N���A
	ZeroMemory(&m_info,sizeof(Sinfo));
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
	m_info.state = STATE_APPER;

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

	// ��ԊǗ�
	ManageState();

	// �������Ƃ̍X�V
	UpdateState();
	
	// �����蔻��Ǘ�
	ManageCollision();

	// �U���̊Ǘ�
	ManageAttack();

	if (CEnemy::GetState() == STATE_DEATH)
	{
		Death();
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemyBoss::ManageState(void)
{
	CEnemy::STATE state = CEnemy::GetState();

	int nTimer = GetCntState();

	switch (state)
	{
	case CEnemy::STATE_NORMAL:
		break;
	case CEnemy::STATE_DAMAGE:

		nTimer++;

		SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (nTimer > DAMAGE_FRAME)
		{// �ʏ��Ԃɖ߂�
			nTimer = 0;
			state = CEnemy::STATE_NORMAL;

			ResetAllCol();
		}
		break;
	case CEnemy::STATE_DEATH:

		Uninit();

		break;
	default:
		break;
	}

	CEnemy::SetState(state);

	SetCntState(nTimer);
}

//=====================================================
// ��Ԃ��Ƃ̍X�V����
//=====================================================
void CEnemyBoss::UpdateState(void)
{
	switch (m_info.state)
	{
	case STATE_APPER:
		UpdateApper();
		break;
	case STATE_BATTLE:
		UpdateAttackState();
		break;
	default:
		break;
	}
}

//=====================================================
// �o����Ԃ̍X�V
//=====================================================
void CEnemyBoss::UpdateApper(void)
{
	bool bFinish = IsFinish();

	if (bFinish)
	{// ��Ԑ؂�ւ�
		SwitchState();

		m_info.state = STATE_BATTLE;
		SwitchState();
	}
}

//=====================================================
// �퓬��Ԃ̍X�V
//=====================================================
void CEnemyBoss::UpdateAttackState(void)
{
	switch (m_info.attackState)
	{
	case ATTACK_MISSILE:
		UpdateMissile();
		break;
	case ATTACK_DASH:
		UpdateDash();
		break;
	case ATTACK_SHOT_UNDER:
		UpdateShotUnder();
		break;
	default:
		break;
	}
}

//=====================================================
// �~�T�C���U���̍X�V
//=====================================================
void CEnemyBoss::UpdateMissile(void)
{
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�̕�����������
	RotDest();

	if (pos.x < MID_POINT)
	{// ���ɂ����ꍇ
		m_info.posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGTH, 0.0f };
	}
	else
	{
		m_info.posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGTH, 0.0f };
	}


	// �ڕW�ʒu�Ǐ]
	bool bEnd = FollowDest();

	if (bEnd)
	{
		// �~�T�C���U��
		m_info.nCntAttack++;

		if (TIME_MISSILE <= m_info.nCntAttack)
		{// �~�T�C������
			D3DXVECTOR3 posMissile = GetMtxPos(IDX_SHOULDER_L);

			CMissile *pMissile = CMissile::Create(posMissile);

			if (pMissile != nullptr)
			{
				pMissile->SetMove(D3DXVECTOR3(0.0f, MISSILE_UP, 0.0f));
			}

			m_info.nCntAttack = 0;

			// �U���񐔉��Z
			m_info.nNumAttack++;

			if (m_info.nNumAttack >= NUM_MISSILE)
			{
				SwitchState();
			}
		}
	}
}

//=====================================================
// �ːi�U���̍X�V
//=====================================================
void CEnemyBoss::UpdateDash(void)
{
	bool bFinish = IsFinish();

	if (bFinish)
	{// ��Ԑ؂�ւ�
		// �ڕW�ʒu�Ǐ]
		bool bEnd = FollowDest();

		if (bEnd)
		{
			SwitchState();
		}
	}
	else
	{
		RotDest();
	}
}

//=====================================================
// ������ˌ��U���̍X�V
//=====================================================
void CEnemyBoss::UpdateShotUnder(void)
{
	// �ėp�����擾
	CUniversal *pUniversal = CManager::GetUniversal();

	RotDest();

	bool bFinish = IsFinish();
	int nKey = GetKey();

	if (nKey == 3)
	{
		m_info.nCntAttack++;

		if (m_info.nCntAttack >= SHOT_TIME)
		{
			D3DXMATRIX mtxWeapon = *GetParts(IDX_WEAPON)->m_pParts->GetMatrix();
			D3DXMATRIX mtxMazzle;
			D3DXMATRIX mtxMazzleVec;

			// �I�t�Z�b�g�̈ʒu�ݒ�
			pUniversal->SetOffSet(&mtxMazzle, mtxWeapon, D3DXVECTOR3(5.0f, -30.0f, 0.0f));
			pUniversal->SetOffSet(&mtxMazzleVec, mtxMazzle,D3DXVECTOR3(0.0f,-1.0f,0.0f));

			// �����̃x�N�g�����擾
			D3DXVECTOR3 posMazzle =
			{
				mtxMazzle._41,
				mtxMazzle._42,
				mtxMazzle._43,
			};
			D3DXVECTOR3 posBullet =
			{
				mtxMazzleVec._41,
				mtxMazzleVec._42,
				mtxMazzleVec._43,
			};
			D3DXVECTOR3 vecBullet = posBullet - posMazzle;

			D3DXVec3Normalize(&vecBullet, &vecBullet);

			vecBullet *= BULLET_SPEED;

			CBullet::Create(posMazzle, vecBullet, 400, CBullet::TYPE_ENEMY);

			m_info.nCntAttack = 0;
		}
	}

	if (bFinish)
	{// ��Ԑ؂�ւ�
		// �ڕW�ʒu�Ǐ]
		SwitchState();
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
// �����蔻��̒Ǐ]
//=====================================================
void CEnemyBoss::FollowCollision(void)
{
	CCollisionSphere *pCollision = GetClsnSphere();

	if (pCollision != nullptr)
	{
		D3DXVECTOR3 pos = GetMtxPos(IDX_WAIST);

#ifdef _DEBUG
		//dCEffect3D::Create(pos, pCollision->GetRadius(), 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif

		pCollision->SetPositionOld(pCollision->GetPosition());
		pCollision->SetPosition(pos);
		pCollision->SetRadius(35.0f);
	}
}

//=====================================================
// �ڕW�ʒu�ւ̈ړ�
//=====================================================
bool CEnemyBoss::FollowDest(void)
{
	bool bEnd = false;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 vecDiff = m_info.posDest - pos;

	// ���������̎擾
	float fLength = D3DXVec3Length(&vecDiff);

	if (LINE_END > fLength)
	{
		bEnd = true;
	}

	vecDiff *= MOVE_FACT;

	pos += vecDiff;

	SetPosition(pos);

	return bEnd;
}

//=====================================================
// ��Ԃ̐؂�ւ�
//=====================================================
void CEnemyBoss::SwitchState(void)
{
	m_info.nNumAttack = 0;

	// ��Ԃ�U��
	m_info.attackState = (ATTACKSTATE)(rand() % (ATTACK_MAX));

	switch (m_info.attackState)
	{
	case ATTACK_MISSILE:

		SetMotion(MOTION_MISSILE);

		break;
	case ATTACK_DASH:
	{
		SetMotion(MOTION_DASH);

		D3DXVECTOR3 pos = GetPosition();

		if (pos.x < MID_POINT)
		{// ���ɂ����ꍇ
			m_info.posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGTH, 0.0f };
		}
		else
		{
			m_info.posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGTH, 0.0f };
		}
	}
		break;
	case ATTACK_SHOT_UNDER:
	{
		int nRand = rand() % 2;

		if (nRand == 1)
		{
			SetMotion(MOTION_SHOT_UPPER);
		}
		else
		{
			SetMotion(MOTION_SHOT_UNDER);
		}
	}
		break;
	default:
		break;
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
	CManager::GetDebugProc()->Print("\n�{�X�ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetDebugProc()->Print("\n�{�X�̗́F[%f]", GetLife());
	CManager::GetDebugProc()->Print("\n�{�X��ԁF[%d]",CEnemy::GetState());
	CManager::GetDebugProc()->Print("\n�{�X���[�V�����F[%d]", GetMotion());
	CManager::GetDebugProc()->Print("\n�L�[�F[%d]", GetKey());
	CManager::GetDebugProc()->Print("\n�t���[���F[%d]", GetFrame());
	CManager::GetDebugProc()->Print("\nIsFinish�F[%d]", IsFinish());
#endif
}