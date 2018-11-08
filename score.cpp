//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "score.h"
#include "Library/ObjectBase2D.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI2DNumber score[SCORE_DIGIT];	//タイマー数字


int ScoreInter = SCORE_SIZE_X * 2;


int Score;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		score[i].Init((float)(SCORE_POS_X - ScoreInter*i), SCORE_POS_Y, SCORE_SIZE_X, SCORE_SIZE_Y, SCORE_TEX);
	}

	Score = 0;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		score[i].Release();
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		score[i].Draw();
	}

}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		int num;

		num = (Score / (int)(pow(10, i)));
		num %= 10;


		score[i].SetNumber(num);


	}

}


//========================================================================
//スコア加算関数
//========================================================================
void AddScore(int num)
{
	Score += num;

	if (Score > pow(10, SCORE_DIGIT))
	{
		Score = (int)pow(10, SCORE_DIGIT) - 1;
	}
}


//========================================================================
//スコア取得関数
//========================================================================
int GetScore(void)
{
	return Score;
}
