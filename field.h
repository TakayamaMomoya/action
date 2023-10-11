//*****************************************************
//
// �n�ʂ̏���[field.h]
// Author:���R����
//
//*****************************************************

#ifndef _FIELD_H_
#define _FIELD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject3D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CField : public CObject
{
public:
	CField(); // �R���X�g���N�^
	~CField();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CField *Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, float width = 3000.0f, float height = 3000.0f);

private:
	enum POLYGON
	{
		POLYGON_FRONT = 0,	// �O��
		POLYGON_RIGHT,	// �E
		POLYGON_LEFT,	// �E
		POLYGON_UNDER,	// ��
		POLYGON_MAX
	};

	CObject3D *m_pField;	// ���̃|���S��
	CObject3D *m_apPolygon[POLYGON_MAX];	// ���̃|���S��
};

#endif