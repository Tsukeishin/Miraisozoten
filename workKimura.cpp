//=============================================================================
//
//木村担当分　workKimura.cpp
//
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workKimura.h"
#include "SceneManager.h"


//木村担当分インクルード


//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit

		break;


	case SCENE_GAME://ゲームで使いたいソースのInit

		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit

		break;
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitWorkKimura(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit

		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit

		break;
	}


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate

		break;


	case SCENE_GAME://ゲームで使うソースのUpdate

		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;
	}


}

//=============================================================================
//描画処理
//=============================================================================
void DrawWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw

		break;


	case SCENE_GAME://ゲームで使うソースのDraw

		break;


	case SCENE_RESULT://リザルトで使うソースのDraw

		break;
	}


}