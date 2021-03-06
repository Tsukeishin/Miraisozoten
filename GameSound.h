//=============================================================================
//
// タイトル処理 [title.h]
//
//=============================================================================
#ifndef _GAME_SOUND_H_
#define _GAME_SOUND_H_

#include <Windows.h>

#define BGM_VOLUME_MIN		(-9000)
#define BGM_VOLUME_MAX		(-1000)
#define BGM_VOLUME_HALF		(-3000)

#define SE_VOLUME_MAX		(0)
#define SE_VOLUME_MIN		(-10000)

#define VOLUME_CONTROL_DOWN	(50)
#define VOLUME_CONTROL_UP	(300)

enum BGM_NO
{
	TITLE,
	GAME_AKIBA,
	GAME_AMERICA,
	GAME_SPACE,
	GAME_BONUS,
	RESULT,
	BGM_MAX
};

enum SE_NO
{
	CURSOL,
	DECIDE,
	START,
	COUNT_1,
	COUNT_2,
	COUNT_3,
	FINISH,
	SHOOT_BULLET,
	SCORE_SLOT,
	SCORE_DECISION,
	VIGOR,
	MODE,
	CURTAIN,
	GAGE_1ST2ND,
	GAGE_LAST,
	THANKYOU,
	EXCELLENT,
	SLOT_STOP,
	FINISH_COUNT,
	AORI,
	SE_MAX
};

enum Fade
{
	SOUND_FADE_IN,
	SOUND_FADE_OUT,
	SOUND_FADE_HALF,
};
//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitGameSound(void);
void UninitGameSound(void);

void PlaySE(int no);
void PlayBGM(int no);
void StopSE(int no);
void StopBGM(int no);
long VolumeCheckSE(void);
long VolumeCheckBGM(void);
bool PlayCheckSE(int no);
bool PlayCheckBGM(int no);

void UpdateGameSound(void);

void SEVolumeTurning(void);
void BGMVolumeTurning(void);


#endif
