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

//*****************************************************************************
// \’Μθ`
//*****************************************************************************
typedef struct
{
	int no;

	// Τ§δn
	int timer;
	int nextStage;
	int timeLimit[STAGE_MAX];

	// σΤ§δn
	bool freeze;
	bool end;

} STAGE;

//*****************************************************************************
// vg^CvιΎ
//*****************************************************************************
STAGE *GetStage(void);

void InitStage(void);
void UpdateStage(void);

void FreezeStage(void);
void UnFreezeStage(void);

#endif