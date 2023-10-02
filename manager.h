//*****************************************************
//
// �}�l�[�W���[����[manager.h]
// Author:���R����
//
//*****************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputJoypad;
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CUniversal;
class CFade;
class CObjectManager;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CManager
{
public:
	CManager();	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit(void);
	void Update();
	void Draw();
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetKeyboard(void) { return m_pKeyboard; }
	static CInputMouse *GetMouse(void) { return m_pMouse; }
	static CInputJoypad *GetJoypad(void) { return m_pJoypad; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static CSound *GetSound(void) { return m_pSound; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CTexture *GetTexture(void) { return m_pTexture; }
	static CObjectManager *GetObjectManager(void) { return m_pObjectManager; }
	static CUniversal *GetUniversal(void) { return m_pUniversal; }
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_mode; }
	static CFade *GetFade(void) { return m_pFade; }
	static void SetScore(int nScore) { m_nScore = nScore; }
	static int GetScore(void) { return m_nScore; }

private:
	static CRenderer *m_pRenderer;	// �����_���[�̃N���X
	static CInputKeyboard *m_pKeyboard;	// �L�[�{�[�h�̃N���X
	static CInputMouse *m_pMouse;	// �}�E�X�̃N���X
	static CInputJoypad *m_pJoypad;	// �}�E�X�̃N���X
	static CDebugProc *m_pDebugProc;	// �f�o�b�O�v���V�[�W���̃N���X
	static CSound *m_pSound;	// �T�E���h�̃N���X
	static CCamera *m_pCamera;	// �J�����̃|�C���^
	static CLight *m_pLight;	// ���C�g�̃|�C���^
	static CTexture *m_pTexture;	// �e�N�X�`���Ǘ��ւ̃|�C���^
	static CUniversal *m_pUniversal;	// �ėp�����̃|�C���^
	static CScene *m_pScene;	// ���݂̃V�[��
	static CScene::MODE m_mode;	// ���݂̃��[�h
	static CFade *m_pFade;	// �t�F�[�h�̃|�C���^
	static CObjectManager *m_pObjectManager;	// �I�u�W�F�N�g�Ǘ��̃|�C���^
	static int m_nScore;	// �X�R�A
};

#endif