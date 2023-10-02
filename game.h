//*****************************************************
//
// �Q�[������[game.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CScore;
class CTimer;
class CGame;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGame : public CScene
{
public:
	enum STATE
	{// ���
		STATE_NONE,	// �������Ă��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_RESULT,	// ���U���g���
		STATE_END,	// �I�����
		STATE_MAX
	};

	CGame();	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();
	static CScore *GetScore(void) { return m_pScore; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static void ReleaseScore(void);
	static void ReleaseTimer(void);
	static void SetState(STATE state) { m_state = state; }
	static STATE GetState(void) { return m_state; }

private:
	static CScore *m_pScore;	// �X�R�A�̃|�C���^
	static CTimer *m_pTimer;	// �^�C�}�[�̃|�C���^
	static STATE m_state;	// ���
};

#endif