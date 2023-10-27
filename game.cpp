//*****************************************************
//
// Q[[game.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "object.h"
#include "universal.h"
#include "particle.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "fade.h"
#include "camera.h"
#include "effect3D.h"
#include "objectmanager.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "field.h"
#include "block.h"
#include "edit.h"
#include "enemy.h"
#include "skybox.h"
#include "enemyManager.h"
#include "animEffect3D.h"
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"
#include "anim3D.h"
#include "texture.h"
#include "timer.h"
#include "pause.h"

//*****************************************************
// }Nè`
//*****************************************************
#define TRANS_TIME	(60)	// I¹ÜÅÌ]CÌt[
#define RESULT_TIME	(5)	// UgæÊ\¦ÜÅÌO
#define BOSS_LINE	(2737.0f)	// {XíÉËü·éC
#define CHECKPOINT_PATH "data\\MAP\\checkpoint.txt"	// `FbN|Cgf[^ÌpX

//*****************************************************
// ÃIoÏé¾
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// óÔ
int CGame::m_nProgress = 0;	// isóµ
CGame *CGame::m_pGame = nullptr;	// ©gÌ|C^

//=====================================================
// RXgN^
//=====================================================
CGame::CGame()
{
	m_pPosCheckPoint = nullptr;
	m_nNumCheckPoint = 0;
}

//=====================================================
// fXgN^
//=====================================================
CGame::~CGame()
{

}

//=====================================================
// ú»
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;

	CObjectManager *pObjManager = CManager::GetObjectManager();

	// J£ÌÝè
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetDist(180.0f);
	}

	// X|[n_Ýè
	LoadCheckPoint();

	// XJC{bNX
	CSkybox *pSkybox = CSkybox::Create();
	pSkybox->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// ubNzuÇ
	CBlock::Load("data\\MAP\\map01.bin");

	// UI}l[W[
	CUIManager::Create();

	// vC[¶¬
	CPlayer *pPlayer = CPlayer::Create();

	if (pPlayer != nullptr && m_pPosCheckPoint != nullptr)
	{// X|[n_ÌÝè
		pPlayer->SetPosition(m_pPosCheckPoint[m_nProgress]);
	}

	// G}l[W[¶¬
	CEnemyManager::Create();

	// RDGtFNgÇ¶¬
	CAnimEffect3D::Create();

	// `[gAÌ¶¬
	CreateTutorial();

#ifdef _DEBUG
	//CEdit::Create();
#endif

	m_bStop = false;

	return S_OK;
}

//=====================================================
// `FbN|CgÌÇ
//=====================================================
void CGame::LoadCheckPoint(void)
{
	// Ïé¾
	char cTemp[256];
	int nCntPos = 0;

	// t@C©çÇÝÞ
	FILE *pFile = fopen(CHECKPOINT_PATH, "r");

	if (pFile != nullptr)
	{// t@CªJ¯½ê
		while (true)
		{
			// ¶ÇÝÝ
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_CHECKPOINT") == 0)
			{// `FbN|CgÇ
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumCheckPoint);

				if (m_pPosCheckPoint == nullptr)
				{// »èîñÌ¶¬
					m_pPosCheckPoint = new D3DXVECTOR3[m_nNumCheckPoint];

					for (int i = 0; i < m_nNumCheckPoint; i++)
					{// îñÌNA
						m_pPosCheckPoint[i] = { 0.0f,0.0f,0.0f };
					}
				}
				else
				{
					break;
				}

				if (m_pPosCheckPoint == nullptr)
				{// ¶¬Å«È©Á½ê
					break;
				}

				while (true)
				{
					// ¶ÇÝÝ
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "CHECKPOINTSET") == 0)
					{// p[^[ÇJn
						while (true)
						{
							// ¶ÇÝÝ
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "POS") == 0)
							{//ÊuÇÝÝ
								fscanf(pFile, "%s", &cTemp[0]);

								for (int i = 0; i < 3; i++)
								{
									fscanf(pFile, "%f", &m_pPosCheckPoint[nCntPos][i]);
								}
							}

							if (strcmp(cTemp, "END_CHECKPOINTSET") == 0)
							{// p[^[ÇI¹
								nCntPos++;

								break;
							}
						}
					}

					if (m_nNumCheckPoint <= nCntPos)
					{
						break;
					}
				}
			}
			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// I¹ð
				break;
			}
		}

		// t@CðÂ¶é
		fclose(pFile);
	}
}

//=====================================================
// `[gA\LÌ¶¬
//=====================================================
void CGame::CreateTutorial(void)
{
	D3DXVECTOR3 aPos[5] =
	{
		{ 161.0f, 15.0f, 20.0f },
		{ 300.0f, 15.0f, 20.0f },
		{ 526.0f, 11.0f, 20.0f },
		{ 631.0f, 80.0f, 20.0f },
		{ 842.0f, 80.0f, 20.0f },
	};

	char *apPath[5] = 
	{
		"data\\TEXTURE\\UI\\tutorial00.png",
		"data\\TEXTURE\\UI\\tutorial01.png",
		"data\\TEXTURE\\UI\\tutorial02.png",
		"data\\TEXTURE\\UI\\tutorial03.png",
		"data\\TEXTURE\\UI\\tutorial04.png",
	};

	for (int i = 0; i < 5; i++)
	{
		// CX^X¶¬
		CAnim3D *pAnim3D = CAnim3D::Create(aPos[i], 2, 40, true);

		if (pAnim3D != nullptr)
		{
			// FÌÝè
			CTexture *pTexture = CTexture::GetInstance();

			if (pTexture != nullptr)
			{// eNX`ÌÝè
				int nIdx = pTexture->Regist(apPath[i]);
				pAnim3D->SetIdxTexture(nIdx);
				pAnim3D->SetSize(35.0f, 25.0f);
			}
		}
	}
}

//=====================================================
// I¹
//=====================================================
void CGame::Uninit(void)
{
	if (m_pPosCheckPoint != nullptr)
	{
		delete[] m_pPosCheckPoint;
		m_pPosCheckPoint = nullptr;
	}

	// ubNîñí
	CBlock::DeleteAll();

	// IuWFNgSü
	CObject::ReleaseAll();

	m_pGame = nullptr;
}

//=====================================================
// XV
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (m_bStop == false)
	{
		// V[ÌXV
		CScene::Update();

		if (pKeyboard != nullptr)
		{
			if (pKeyboard->GetTrigger(DIK_P))
			{
				CPause::Create();
			}
		}
	}
	else
	{
#ifdef DEBUG
		CEdit *pEdit = CEdit::GetInstatnce();

		if (pEdit != nullptr)
		{
			pEdit->Update();
		}
#endif // DEBUG

		CPause *pPause = CPause::GetInstance();

		if (pPause != nullptr)
		{
			pPause->Update();
		}
	}

	// JXV
	UpdateCamera();

	// óÔÇ
	ManageState();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// JÌXV
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_bStop == false)
	{
		if (m_state == STATE_NORMAL)
		{
			// vC[ÌÇ]
			pCamera->FollowPlayer();
		}
		else if (m_state == STATE_BOSS)
		{
			// {XíÌ®«
			pCamera->BossBattle();
		}
	}
	else
	{
		// ì
		pCamera->Control();
	}
}

//=====================================================
// óÔÇ
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CManager::GetFade();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
	{
		// vC[æ¾
		CPlayer *pPlayer = nullptr;
		pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 pos = pPlayer->GetPosition();

			if (pos.x >= BOSS_LINE)
			{// {XíÖÚs
				CEnemyManager *pEnemyManager = nullptr;

				pEnemyManager = CEnemyManager::GetInstance();

				if (pEnemyManager != nullptr)
				{
					pEnemyManager->CreateEnemy(D3DXVECTOR3(BOSS_LINE,190.0f,0.0f), CEnemy::TYPE_BOSS);
				}

				m_state = STATE_BOSS;
			}

			if (m_nProgress < m_nNumCheckPoint - 1)
			{
				if (pos.x >= m_pPosCheckPoint[m_nProgress + 1].x)
				{// `FbN|CgÌÝè
					m_nProgress++;
				}
			}
		}
	}
		break;
	case CGame::STATE_BOSS:
		break;
	case CGame::STATE_RESULT:
		break;
	case CGame::STATE_END:
		
		if(pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// fobO
//=====================================================
void CGame::Debug(void)
{
	// üÍæ¾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_F))
	{
		m_bStop = m_bStop ? false : true;
	}
}

//=====================================================
// `æ
//=====================================================
void CGame::Draw(void)
{
	CManager::GetDebugProc()->Print("\nisóµF[%d]", m_nProgress);
}