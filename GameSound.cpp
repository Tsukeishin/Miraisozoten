//===============================================================
//�Q�[���T�E���h����
//==============================================================
#include "GameSound.h"
#include "Library\Sound.h"
#include "SceneManager.h"
#include "Library\DebugProcess.h"

class BGM : public DirectSound
{
public:
	void FadeVolume(bool flag);
};

BGM SoundBGM[BGM_MAX];
DirectSound SoundSE[SE_MAX];

//�t�@�C���z��̍쐬�@���w�b�_�[��enum�Ə��Ԃ����킹�邱�ƁiPlay��Stop�ɉe�����o��j
const char *BGMFile[BGM_MAX]=
{
	"data/BGM/�^�C�g���E���U���g�E�����L���O��ʉ��� (2).wav",
	"data/BGM/�H�t���X�e�[�W����.wav",
	"data/BGM/�F���X�e�[�W����.wav",
	"data/BGM/���C�u�n�E�X�X�e�[�W�����i�{�[�i�X�j.wav",
	"data/BGM/�^�C�g���E���U���g�E�����L���O��ʉ��� (2).wav",
};

const char *SEFile[SE_MAX] =
{
	"data/SE/�I���J�[�\���ړ����i���j���[�I���E���O����etc�j.wav",
	"data/SE/����{�^�����i�^�C�g����ʁE���j���[��ʁE���O�ŏI���莞�E���ǂ�A��߂Ƃ����������Ƃ����j.wav",
	"data/SE/�Q�[���X�^�[�g��.wav",
	"data/SE/�J�E���g��_1.wav",
	"data/SE/�J�E���g��_2.wav",
	"data/SE/�J�E���g��_3.wav",
	"data/SE/�Q�[���Z�b�g��.wav",
	"data/SE/�{�C�X�e�����ˉ�.wav",
	"data/SE/���U���g�X�R�A�W�v���i�������Ђ����獂���œ����Ă鎞�̉��j.wav",
	"data/SE/���U���g�X�R�A�m�艹�i�������S�Ċm�肵���������̉��j.wav",
	"data/SE/�I�i�l�K�e�B�u�Ȑl�j�����C�ɂȂ�����_�ʏ�_.wav",
	"data/SE/�^�C�g����ʂ��烁�j���[��ʂɂ������Ƃ��i���[�h��I��łˁI���j.wav",
	"data/SE/�J�[�e��.wav",
	"data/SE/�{�[�i�X�Q�[�W�����܂������i1�i�K�E2�i�K�ځj.wav",
	"data/SE/�{�[�i�X�Q�[�W��MAX�ɂȂ������̉�.wav",
	"data/SE/�^�C�g���ɖ߂�Ƃ��̉��i�����L���O�̌�E�I�v�V��������^�C�g�����ǂ�I����j.wav",
	"data/SE/�����L���O���܎��i���߂łƂ��I���j.wav",
	"data/SE/1�����Ƃ̃X�R�A�m�艹.wav",
};

//=============================================================================
//������
//=============================================================================

HRESULT InitGameSound(void)
{


	for (int i = 0; i < BGM_MAX; i++)
	{
		SoundBGM[i].Volume = BGM_VOLUME_MIN;
		SoundBGM[i].LoadSound(BGMFile[i]);
	}
	PlayBGM(TITLE);
	PlayBGM(GAME_AKIBA);
	PlayBGM(RESULT);

	for (int i = 0; i < SE_MAX; i++)
	{
		SoundSE[i].LoadSound(SEFile[i]);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================

void UninitGameSound(void)
{
	for (int i = 0; i < BGM_MAX; i++)
	{
		SoundBGM[i].Release();
	}


	for (int i = 0; i < SE_MAX; i++)
	{
		SoundSE[i].Release();
	}

}

//=============================================================================
//SE�Đ�
//=============================================================================
void PlaySE(int no)
{
	SoundSE[no].Play(E_DS8_FLAG_NONE, 0);
}
//=============================================================================
//BGM�Đ�
//=============================================================================
void PlayBGM(int no)
{
	SoundBGM[no].Play(E_DS8_FLAG_LOOP, 0);
}


//=============================================================================
//SE��~
//=============================================================================
void StopSE(int no)
{
	SoundSE[no].Stop();
}
//=============================================================================
//BGM��~
//=============================================================================
void StopBGM(int no)
{
	SoundBGM[no].Stop();
}


//=============================================================================
//SE�Đ��m�F
//=============================================================================
bool PlayCheckSE(int no)
{
	return SoundSE[no].CheckPlaying();
}

//=============================================================================
//BGM�Đ��m�F
//=============================================================================
bool PlayCheckBGM(int no)
{
	return SoundBGM[no].CheckPlaying();
}

//=============================================================================
//BGM�t�F�[�h����
//=============================================================================
void BGM::FadeVolume(bool flag)
{
	//true=�t�F�[�h�C���@false=�t�F�[�h�A�E�g
	switch (flag)
	{
	case true:
		if (this->Volume < BGM_VOLUME_MAX)
		{
			this->Volume += VOLUME_CONTROL_UP;
			if (this->Volume >= BGM_VOLUME_MAX)
			{
				this->Volume = BGM_VOLUME_MAX;
			}
		}

		break;

	case false:
		if (this->Volume > BGM_VOLUME_MIN)
		{
			this->Volume -= VOLUME_CONTROL_DOWN;
			if (this->Volume <= BGM_VOLUME_MIN)
			{
				this->Volume = BGM_VOLUME_MIN;
			}
		}

		break;

	}
	this->SetVolume();
}

//=============================================================================
//BGM�A�b�v�f�[�g����
//=============================================================================
void UpdateGameSound(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE:
		SoundBGM[TITLE].FadeVolume(true);
		SoundBGM[GAME_AKIBA].FadeVolume(false);
		SoundBGM[RESULT].FadeVolume(false);
		break;

	case SCENE_GAME:
		SoundBGM[TITLE].FadeVolume(false);
		SoundBGM[GAME_AKIBA].FadeVolume(true);
		SoundBGM[RESULT].FadeVolume(false);
		break;

	case SCENE_RESULT:
		SoundBGM[TITLE].FadeVolume(false);
		SoundBGM[GAME_AKIBA].FadeVolume(false);
		SoundBGM[RESULT].FadeVolume(true);
		break;
	}
	PrintDebugProcess("\nTITLE%d\n", SoundBGM[TITLE].Volume);
	PrintDebugProcess("GAME%d\n", SoundBGM[GAME_AKIBA].Volume);
	PrintDebugProcess("RESULT%d\n", SoundBGM[RESULT].Volume);

}