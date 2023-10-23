//*****************************************************
//
// UIÌ[UI.h]
// Author:ûüRç
//
//*****************************************************

#ifndef _UI_H_
#define _UI_H_

//*****************************************************
// CN[h
//*****************************************************
#include "main.h"
#include "object2D.h"

//*****************************************************
// NXÌè`
//*****************************************************
class CUI	: public CObject2D
{
public:
	CUI(int nPriority = 3);
	~CUI();	//	fXgN^

	static CUI *Create(void);	// ¶¬
	HRESULT Init(void);	// ú»
	void Uninit(void);	// I¹
	void Update(void);	// XV
	void Draw(void);	// `æ
	void EnableDisp(bool bDisp) { m_bDisp = bDisp; }	// \¦ØèÖ¦

private:
	bool m_bDisp;	// \¦Å«é©Ç¤©
};

#endif