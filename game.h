//=============================================================================
//
// リザルト画面処理 [Game.h]
//
//=============================================================================
#ifndef _GAME_INCLUDE_H_
#define _GAME_INCLUDE_H_


#include <Windows.h>


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);


void LoadTexture(void);
void ReleaseTexture(void);

#endif
