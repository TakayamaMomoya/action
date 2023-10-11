//*****************************************************
//
// �u���b�N�̏���[block.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "ObjectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBlock : public CObjectX
{
public:
	typedef enum
	{// ���
		TYPE_FLOOR,	// ��
		TYPE_CHAIR,	// �֎q
		TYPE_DESK,	// ��
		TYPE_DOCUMENT,	// ����
		TYPE_FUN,	// ���C��
		TYPE_LOCKER,	// ���b�J�[
		TYPE_WINDOW,	// ��
		TYPE_FLOORBIG,	// �ł���
		TYPE_WINDOWBIG,	// �ł���
		TYPE_MAX
	}TYPE;

	typedef struct
	{// �ۑ�����Ƃ��̏��
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		TYPE type;
	}MemBlock;

	CBlock(int nPriority = 3);	// �R���X�g���N�^
	~CBlock();	// �f�X�g���N�^

	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);	// �Ǎ�
	static void Save(void);	// �ۑ�
	static void Delete(int nIdx);	// �����폜����
	static void DeleteAll(void);	// �S�폜����
	static int GetNumAll(void) { return m_nNumAll; }
	static CBlock **GetBlock(void) { return &m_apBlock[0]; }
	static void LoadModel(void);
	static void DeleteIdx(void);
	static int *GetIndex(void) { return m_pIdxObject; }
	//void Hit(float fDamage);

private:
	TYPE m_type;
	static int *m_pIdxObject;	// ���f���̃^�C�v�ԍ��̃|�C���^
	static CBlock *m_apBlock[NUM_OBJECT];	// �u���b�N�̔z��
	static int m_nNumAll;	// ����
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	int m_nLife;	// �̗�
};

#endif
