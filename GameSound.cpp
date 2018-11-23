//===============================================================
//ゲームサウンド処理
//==============================================================
#include "GameSound.h"
#include "Library\Sound.h"
#include "SceneManager.h"

class BGM : public DirectSound
{
public:
	long Volume;
	void FadeVolume(bool flag);
};

BGM SoundBGM[BGM_MAX];
DirectSound SoundSE[SE_MAX];


const char *BGMFile[BGM_MAX]=
{
	"data/BGM/タイトル・リザルト・ランキング画面音源 (2).wav",
	"data/BGM/秋葉原ステージ音源.wav",
	"data/BGM/宇宙ステージ音源.wav",
	"data/BGM/ライブハウスステージ音源（ボーナス）.wav",
	"data/BGM/タイトル・リザルト・ランキング画面音源 (2).wav",
};

const char *SEFile[SE_MAX] =
{
	"data/SE/選択カーソル移動音（メニュー選択・名前入力etc）.wav",
	"data/SE/決定ボタン音（タイトル画面・メニュー画面・名前最終決定時・もどる、やめとくを押したとき等）.wav",
	"data/SE/カウント音_1.wav",
	"data/SE/カウント音_2.wav",
	"data/SE/カウント音_3.wav",
	"data/SE/ゲームスタート音.wav",
	"data/SE/ゲームセット音.wav",
	"data/SE/ボイステン発射音.wav",
	"data/SE/リザルトスコア集計音（数字がひたすら高速で動いてる時の音）.wav",
	"data/SE/リザルトスコア確定音（数字が全て確定しきった時の音）.wav",
	"data/SE/的（ネガティブな人）が元気になった音_通常点.wav",
};


//=============================================================================
//初期化
//=============================================================================

HRESULT InitGameSound(void)
{


	for (int i = 0; i < BGM_MAX; i++)
	{
		SoundBGM[i].LoadSound(BGMFile[i]);
		SoundBGM[i].Volume = BGM_VOLUME_MIN;
	}
	SoundBGM[TITLE].Play(E_DS8_FLAG_LOOP, 0);
	SoundBGM[GAME_AKIBA].Play(E_DS8_FLAG_LOOP, 0);
	SoundBGM[RESULT].Play(E_DS8_FLAG_LOOP, 0);


	for (int i = 0; i < SE_MAX; i++)
	{
		SoundSE[i].LoadSound(SEFile[i]);
	}

	return S_OK;
}

//=============================================================================
//終了処理
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
//SE再生
//=============================================================================
void PlaySE(int no)
{
	SoundSE[no].Play(E_DS8_FLAG_NONE, 0);
}
//=============================================================================
//BGM再生
//=============================================================================
void PlayBGM(int no)
{
	SoundBGM[no].Play(E_DS8_FLAG_LOOP, 0);
}


//=============================================================================
//SE停止
//=============================================================================
void StopSE(int no)
{
	SoundSE[no].Stop();
}
//=============================================================================
//BGM停止
//=============================================================================
void StopBGM(int no)
{
	SoundBGM[no].Stop();
}


//=============================================================================
//SE再生確認
//=============================================================================
bool PlayCheckSE(int no)
{
	return SoundSE[no].CheckPlaying();
}

//=============================================================================
//BGM再生確認
//=============================================================================
bool PlayCheckBGM(int no)
{
	return SoundBGM[no].CheckPlaying();
}

//=============================================================================
//BGMフェード処理
//=============================================================================
void BGM::FadeVolume(bool flag)
{
	//true=フェードイン　false=フェードアウト
	switch (flag)
	{
	case true:
		if (this->Volume < BGM_VOLUME_MAX);
		{
			this->Volume += VOLUME_CONTROL_UP;
			if (this->Volume >= BGM_VOLUME_MAX)
			{
				this->Volume = BGM_VOLUME_MAX;
			}
		}

		break;

	case false:
		if (this->Volume > BGM_VOLUME_MIN);
		{
			this->Volume -= VOLUME_CONTROL_DOWN;
			if (this->Volume <= BGM_VOLUME_MIN)
			{
				this->Volume = BGM_VOLUME_MIN;
			}
		}

		break;

	}
	this->SetVolume(Volume);
}

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
}