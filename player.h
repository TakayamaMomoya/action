//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;
class CCollisionSphere;

//*****************************************************
// �}�N����`
//*****************************************************
#define INITIAL_LIFE_PLAYER	(100)	// �����̗�

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);
	void Hit(float fDamage);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	static CPlayer *GetInstance(void) { return m_pPlayer; }

private:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// �ҋ@���
		MOTION_MOVE,	// �ړ����[�V����
		MOTION_JUMP,	// �W�����v���[�V����
		MOTION_FALL,	// �������[�V����
		MOTION_ATTACK,	// �U�����[�V����
		MOTION_ATTACKTURN,	// ���]�U�����[�V����
		MOTION_AIRATTACK,	// �󒆍U�����[�V����
		MOTION_MAX
	};
	struct AttackInfo
	{// �U���̏��
		int nIdxMotion;	// ���[�V�����ԍ�
		int nIdxParent;	// �e�p�[�c�ԍ�
		D3DXVECTOR3 pos;	// �I�t�Z�b�g�ʒu
		int nKey;	// �L�[�ԍ�
		int nFrame;	// ��������t���[��
		float fRadius;	// ���a
	};
	enum JUMPSTATE
	{// �W�����v���
		JUMPSTATE_NONE = 0,
		JUMPSTATE_NORMAL,
		JUMPSTATE_ATTACK,
		JUMPSTATE_MAX
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void InputCamera(void);
	void ManageMotion(void);
	void ManageCollision(void);
	void RotDest(void);
	void SetMotion(MOTION motion);
	void ManageAttack(void);

	int m_nLife;	// �̗�
	int m_nCntAfterImage;	// �c�����o���J�E���^�[
	bool m_bSprint;	// �_�b�V����Ԃ��ǂ���
	bool m_bAttack;	// �U���t���O
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_rotDest;	// �ڕW�̌���
	CMotion *m_pBody;	// �̂̃|�C���^
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	CCollisionSphere *m_pClsnAttack;	// �U���̓����蔻��
	CCollisionSphere *m_pClsnHit;	// ��e�����蔻��
	int m_nNumAttack;	// �U������̐�
	AttackInfo *m_pAttackInfo;	// �U���̏��|�C���^
	JUMPSTATE m_jump;	// �W�����v���

	static CPlayer *m_pPlayer;	// ���g�̃|�C���^
};

#endif
