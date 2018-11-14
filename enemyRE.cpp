//=============================================================================
//
// enemy処理・改 [enemyRE.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "enemyRE.h"

#include "Library/ObjectBase3D.h"
#include "HitCheck.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY EnemyREWk[ENEMY_MAX];		// ワーク

char *FileEnemy[] =
{
	"data/作業/boss.png",
	"data/作業/tttt.png",
};

C3DPolygonObject EnemyRE[ENEMY_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	// 初期化用変数
	const Vector2 size = Vector2(48, 48);

	// 全パラメータ初期化
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		(e + i)->use = FALSE;
		(e + i)->pos = Vector3(0.0f, 0.0f, 0.0f);
		(e + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(e + i)->timer = 0;
		(e + i)->ptn = 0;

		(e + i)->hp = 0;

		EnemyRE[i].Init((e + i)->pos, size);
		EnemyRE[i].LoadTexture(FileEnemy[0]);

	}

	// 個別パラメータ設定
	(e + 0)->use = TRUE;
	(e + 0)->pos = Vector3(-300.0f, 100.0f, 0.0f);

	(e + 1)->use = TRUE;
	(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	EnemyRE[1].LoadTexture(FileEnemy[1]);

	(e + 2)->use = TRUE;
	(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);
	EnemyRE[2].LoadTexture(FileEnemy[1]);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyRE(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyRE[i].Release();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			// 衝突判定

			
			// 更新処理（位置、回転）
			EnemyRE[i].LoadObjectStatus((e + i)->pos, (e + i)->rot);

			// タイマーカウントアップ
			(e + i)->timer++;

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			EnemyRE[i].Draw();
		}

	}
}

//=============================================================================
// 取得
//=============================================================================
ENEMY *GetEnemyRE(int no)
{
	return (&EnemyREWk[no]);
}

