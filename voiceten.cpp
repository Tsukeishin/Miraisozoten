//=============================================================================
//
// voiceten処理 [voiceten.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "voiceten.h"

#include "Library/ObjectBase3D.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MoveVoiceten(void);
float DirectionCalc(D3DXVECTOR3 Self, D3DXVECTOR3 Tgt);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VOICETEN VoicetenWk[VOICETEN_MAX];		// ワーク

char *FileVoiceten[] =
{
	"data/TEXTURE/voiceten00.png",
};

C3DPolygonObject Voiceten[VOICETEN_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void InitVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);
	//Voiceten.Init(Vector3(200, 0, 200), Vector2(50, 50));
	//Voiceten.LoadTexture(FileVoiceten[0]);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitVoiceten(void)
{
	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		Voiceten[i].Release();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	MoveVoiceten();

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		Voiceten[i].LoadObjectStatus((v + i)->pos, (v + i)->rot);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if (v->use == TRUE)
		{
			Voiceten[i].Draw();
		}

	}

}

//=============================================================================
// 取得
//=============================================================================
VOICETEN *GetVoiceten(int no)
{
	return (&VoicetenWk[no]);
}

//=============================================================================
// 移動
//=============================================================================
void MoveVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if (v->use == TRUE)
		{
			(v + i)->pos.x -= sinf((v + i)->rot.y) * (v + i)->vel;
			(v + i)->pos.z -= cosf((v + i)->rot.y) * (v + i)->vel;
		}

	}

}