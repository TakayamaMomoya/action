//*****************************************************
//
// �I�u�W�F�N�g�̏���[object.h]
// Author:���R����
//
//*****************************************************

#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPlayer;
class CBlock;

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_OBJECT	(4096)	//	�I�u�W�F�N�g�̐�
#define NUM_PRIORITY	(8)	// �D�揇�ʂ̍ő吔

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,	// �G
		TYPE_BLOCK,	// �u���b�N
		TYPE_BULLET,	// �e
		TYPE_PARTICLE,	// �p�[�e�B�N��
		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 3);	// �R���X�g���N�^
	virtual ~CObject();	//	�f�X�g���N�^

	virtual HRESULT Init(void) = 0;	// ����������
	virtual void Uninit(void) = 0;	// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void) {};	// �`�揈��
	static void ReleaseAll(void);	// �S�ă����[�X
	static void UpdateAll(void);	// �S�čX�V
	static void DrawAll(void);	// �S�ĕ`��
	virtual void Hit(float fDamage){}	// �q�b�g����
	void SetType(TYPE type);
	TYPE GetType(void) { return m_type; }
	virtual void SetPosition(D3DXVECTOR3 pos) {};	// �ݒ菈��
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(); }	// �ʒu�擾����
	virtual D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); };	// �ʒu�擾����
	virtual float GetWidth(void) { return 0.0f; };	// �T�C�Y�擾
	virtual float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	void EnableWire(bool bWire) { m_bWire = bWire; }
	static int GetNumAll(void) { return m_nNumAll; }

protected:
	void Release(void);	// �ʃ����[�X����

private:
	void Delete(void);	// �ʃ����[�X����

	static int m_nNumAll;	// ����
	int m_nID;	// ������ID
	TYPE m_type;	// ���
	int m_nPriority;	// �`��̗D�揇��
	static CObject *m_apTop[NUM_PRIORITY];	// �擪�̃I�u�W�F�N�g�̃A�h���X
	static CObject *m_apCur[NUM_PRIORITY];	// �Ō���̃I�u�W�F�N�g�̃A�h���X
	CObject *m_pPrev;	// �O�̃I�u�W�F�N�g�̃A�h���X
	CObject *m_pNext;	// ���̃I�u�W�F�N�g�̃A�h���X
	bool m_bDeath;	// ���S�t���O
	bool m_bWire;	// ���C���[�t���[���ŕ\�����邩�ǂ���
};

#endif