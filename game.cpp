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
#include "score.h"
#include "timer.h"
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

//*****************************************************
// }Nè`
//*****************************************************
#define TRANS_TIME	(60)	// I¹ÜÅÌ]CÌt[
#define LIMIT_LENGTH	(10000)	// Ú®§ÀÌ£
#define LIMIT_WIDTH	(100)	// èvC[Ì
#define LIMIT_HEIGHT	(2000)	// §Àx
#define BONUS_TIME	(40)	// {[iXªt^³êéÅáÀÌ^C
#define RATE_BONUS	(0.015f)	// 1b½èÌ^C{[iX
#define RESULT_TIME	(5)	// UgæÊ\¦ÜÅÌO
#define BOSS_LINE	(2737.0f)	// {XíÉËü·éC
#define CHECKPOINT_PATH "data\\MAP\\checkpoint.txt"	// `FbN|Cgf[^ÌpX

//*****************************************************
// ÃIoÏé¾
//*****************************************************
CScore *CGame::m_pScore = nullptr;	// XRAÌ|C^
CTimer *CGame::m_pTimer = nullptr;	// ^C}[Ì|C^
CGame::STATE CGame::m_state = STATE_NONE;
int CGame::m_nProgress = 0;

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
	m_state = STATE_NORMAL;

	CObjectManager *pObjManager = CManager::GetObjectManager();

	if (m_pScore == nullptr)
	{// XRA¶¬
		m_pScore = CScore::Create();
	}

	if (m_pScore != nullptr)
	{// XRAú»
		m_pScore->Init();
	}

	if (m_pTimer == nullptr)
	{// ^C}[¶¬
		m_pTimer = CTimer::Create();
	}

	// J£ÌÝè
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetDist(180.0f);
	}

	// X|[n_Ýè
	LoadCheckPoint();

	// vC[¶¬
	CPlayer *pPlayer = CPlayer::Create();

	if (pPlayer != nullptr && m_pPosCheckPoint != nullptr)
	{// X|[n_ÌÝè
		pPlayer->SetPosition(m_pPosCheckPoint[m_nProgress]);
	}

	// XJC{bNX
	CSkybox::Create();

	// ubNzuÇ
	CBlock::Load();

	// G}l[W[¶¬
	CEnemyManager::Create();

	// RDGtFNgÇ¶¬
	CAnimEffect3D::Create();

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
						ZeroMemory(&m_pPosCheckPoint[i], sizeof(D3DXVECTOR3));
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
// I¹
//=====================================================
void CGame::Uninit(void)
{
	if (m_pScore != nullptr)
	{// XRAÌI¹Ejü
		m_pScore->Uninit();

		m_pScore = nullptr;
	}

	if (m_pTimer != nullptr)
	{// ^C}[ÌI¹Ejü
		m_pTimer->Uninit();

		m_pTimer = nullptr;
	}

	if (m_pPosCheckPoint != nullptr)
	{
		delete[] m_pPosCheckPoint;
		m_pPosCheckPoint = nullptr;
	}

	// ubNîñí
	CBlock::DeleteAll();

	// IuWFNgSü
	CObject::ReleaseAll();
}

//=====================================================
// XRAI¹
//=====================================================
void CGame::ReleaseScore(void)
{
	if (m_pScore != nullptr)
	{// XRAÌI¹Ejü
		m_pScore = nullptr;
	}
}

//=====================================================
// ^C}[I¹
//=====================================================
void CGame::ReleaseTimer(void)
{
	if (m_pTimer != nullptr)
	{// XRAÌI¹Ejü
		m_pTimer = nullptr;
	}
}

//=====================================================
// XV
//=====================================================
void CGame::Update(void)
{
	// üÍæ¾
	//CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	CFade *pFade = CManager::GetFade();

	if (m_bStop == false)
	{
		// V[ÌXV
		CScene::Update();
	}
	else
	{
		CEdit *pEdit = CEdit::GetInstatnce();

		if (pEdit != nullptr)
		{
			pEdit->Update();
		}
	}

	// JXV
	UpdateCamera();

	// óÔÇ
	ManageState();

	//if (pKeyboard != nullptr)
	//{
	//	if (pKeyboard->GetTrigger(DIK_RETURN))
	//	{
	//		if (pFade != nullptr)
	//		{
	//			//pFade->SetFade(CScene::MODE_RANKING);
	//		}
	//	}
	//}

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
	//CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//if (pKeyboard == nullptr)
	//{
	//	return;
	//}

	//if (pKeyboard->GetTrigger(DIK_F))
	//{
	//	m_bStop = m_bStop ? false : true;
	//}
}

//=====================================================
// `æ
//=====================================================
void CGame::Draw(void)
{
	CManager::GetDebugProc()->Print("\nisóµF[%d]", m_nProgress);
}