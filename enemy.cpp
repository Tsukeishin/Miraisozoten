<<<<<<< HEAD
//=============================================================================
//
//木村担当分　workenemy.cpp
//　一年の時にやったmain.cppと同じやり方で
//=============================================================================

//必須インクルード
#include <windows.h>
#include "Library\ObjectBase3D.h"
#include "enemy.h"


//木村担当分インクルード

//グローバル宣言
=======
//=============================================================================
//
//木村担当分　workenemy.cpp
//　一年の時にやったmain.cppと同じやり方で
//=============================================================================

//必須インクルード
#include <windows.h>
#include "Library\ObjectBase3D.h"
#include "enemy.h"


//木村担当分インクルード

//グローバル宣言
>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
C3DPolygonObject ENEMY3D;//エネミー1
C3DPolygonObject ENEMY3D2;//エネミー2
C3DPolygonObject ENEMY3D3;//エネミー3

<<<<<<< HEAD

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitENEMY(void)
{
	//エネミー1
=======

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitENEMY(void)
{
	//エネミー1
>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
	ENEMY3D.Init(Vector3(0, 200, 200), Vector2(300, 300));
				//ポジション設定		//サイズ設定

	ENEMY3D.LoadTexture("data/MODEL/カービー.dds");
<<<<<<< HEAD
			//テクスチャの読み込み

	//エネミー2
=======
			//テクスチャの読み込み

	//エネミー2
>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
	ENEMY3D2.Init(Vector3(100, 0, 200), Vector2(300, 300));
	//ポジション設定		//サイズ設定

	ENEMY3D2.LoadTexture("data/MODEL/すたふぃー.dds");
<<<<<<< HEAD


	//エネミー3
=======


	//エネミー3
>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
	ENEMY3D3.Init(Vector3(500, 500, 200), Vector2(300, 300));
	//ポジション設定		//サイズ設定

	ENEMY3D3.LoadTexture("data/TEXTURE/toumeienemy.png");
<<<<<<< HEAD

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitENEMY(void)
{
	//エネミー1
=======

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitENEMY(void)
{
	//エネミー1
>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
	ENEMY3D.Release();
	//エネミー2
	ENEMY3D2.Release();
	//エネミー3
	ENEMY3D3.Release();

<<<<<<< HEAD


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateENEMY(void)
{


}

//=============================================================================
//描画処理
//=============================================================================
void DrawENEMY(void)
{
	//エネミー1
	ENEMY3D.Draw();
	//エネミー2
	ENEMY3D2.Draw();
	//エネミー3
	ENEMY3D3.Draw();

=======


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateENEMY(void)
{


}

//=============================================================================
//描画処理
//=============================================================================
void DrawENEMY(void)
{
	//エネミー1
	ENEMY3D.Draw();
	//エネミー2
	ENEMY3D2.Draw();
	//エネミー3
	ENEMY3D3.Draw();

>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
}