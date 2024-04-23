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
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class Cuniversal;
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
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_mode; }
	static void SetScore(int nScore) { m_nScore = nScore; }
	static int GetScore(void) { return m_nScore; }

private:
	static CCamera *m_pCamera;	// �J�����̃|�C���^
	static CLight *m_pLight;	// ���C�g�̃|�C���^
	static CScene *m_pScene;	// ���݂̃V�[��
	static CScene::MODE m_mode;	// ���݂̃��[�h
	static int m_nScore;	// �X�R�A
};

#endif