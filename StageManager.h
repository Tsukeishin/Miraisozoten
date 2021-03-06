//=============================================================================
//
// Xe[WΗ [StageManager.h]
// Author : vFθΑ
//
//=============================================================================
#ifndef _STAGEMENEGER_INCLUDE_H_
#define _STAGEMENEGER_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// ρ^
//*****************************************************************************
enum EN_STAGE
{
	STAGE_01_AKIBA = 0,
	STAGE_02_USA,
	STAGE_03_SPACE,

	STAGE_MAX,
};

enum EN_STAGE_STATUS
{
	STAGE_STATUS_NULL = 0,
	STAGE_STATUS_NORMAL,
	STAGE_STATUS_CHANGING,
	STAGE_STATUS_END,

};

//*****************************************************************************
// \’Μθ`
//*****************************************************************************
typedef struct
{
	int no;

	// Τ§δn
	int timer;
	int timerEfx;
	int nextStage;

	// σΤ§δn
	int status;

} STAGE;

//*****************************************************************************
// vg^CvιΎ
//*****************************************************************************
STAGE *GetStage(void);

void InitStage(void);
void UpdateStage(void);

void GameStart(void);
void GameStop(void);

#endif