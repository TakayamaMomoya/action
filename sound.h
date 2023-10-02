//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���R����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_BGM000 = 0,				// �^�C�g��BGM
		LABEL_MAX
	} LABEL;

	typedef enum
	{
		FADESTATE_NONE = 0,	//�������Ă��Ȃ����
		FADESTATE_IN,	//�t�F�[�h�C�����
		FADESTATE_OUT,	//�t�F�[�h�A�E�g���
		FADESTATE_MAX
	}FADESTATE;

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

	void SetVolume(LABEL label, float fVolume);
	void SetFade(LABEL LabelNow, LABEL LabelNext, float fSpeed);

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	FADESTATE m_fadeSound;								// �t�F�[�h���
	LABEL m_SoundLabelNow;								// ���݂̃T�E���h���x��
	LABEL m_SoundLabelNext;								// ���̃T�E���h���x��
	float m_fSpeedFadeSound;									// �T�E���h���t�F�[�h����X�s�[�h
	float m_fVolumeSound;										// �T�E���h�̃{�����[��

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },			// �^�C�g��	
	};
};

#endif