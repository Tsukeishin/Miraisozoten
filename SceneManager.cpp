#include "SceneManager.h"
#include "Library\Input.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Ranking.h"


SCENE SceneManager::GameScene = SCENE_MAX;

//----更新--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの更新
		UpdateTitle();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//SetScene(SCENE_GAME);
		}
		break;

	case SCENE_GAME:
		// ゲームシーンの更新
		UpdateGame();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_RESULT);
		}
		break;

	case SCENE_RESULT:
		// リザルトシーンの更新
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_RANKING);
		}
		break;

	case SCENE_RANKING:
		// ランキングシーンの更新
		UpdateRanking();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
		break;

	}

	return 0;
}

//----描画--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの描画処理
		DrawTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの描画処理
		DrawGame();

		break;

	case SCENE_RESULT:
		// リザルトの描画処理
		DrawResult();

		break;

	case SCENE_RANKING:
		// ランキングの描画処理
		DrawRanking();

		break;
	}
}

//----ゲームシーンの更新・取得--------
SCENE SceneManager::SetScene(SCENE scene)
{
	/* 指定シーンが同じ場合は戻る */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* 現在のシーンのお片付け */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの終了
		UninitTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの終了
		UninitGame();

		break;

	case SCENE_RESULT:
		// リザルトシーンの終了
		UninitResult();

		break;

	case SCENE_RANKING:
		// ランキングシーンの終了
		UninitRanking();

		break;
	}

	/* シーンの切り替え */
	GameScene = scene;

	/* 次のシーンの準備 */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの初期化
		InitTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの初期化
		InitGame();

		break;

	case SCENE_RESULT:
		// リザルトシーンの初期化
		InitResult();

		break;

	case SCENE_RANKING:
		// ランキングシーンの初期化
		InitRanking();

		break;

	default:
		return GameScene;
		break;
	}

	return GameScene;
}

//----ランキングの更新・取得--------
//SCENE SceneManager::SetScene(SCENE scene)
//{
//	/* 指定シーンが同じ場合は戻る */
//	if (scene == SCENE_MAX)
//	{
//		return GameScene;
//	}
//
//	/* 現在のシーンのお片付け */
//	switch (GameScene)
//	{
//	case SCENE_TITLE:
//		// タイトルシーンの終了
//		UninitTitle();
//
//		break;
//
//	case SCENE_GAME:
//		// ゲームシーンの終了
//		UninitGame();
//
//		break;
//
//	case SCENE_RESULT:
//		// リザルトシーンの終了
//		UninitResult();
//
//		break;
//	}
//
//	/* シーンの切り替え */
//	GameScene = scene;
//
//	/* 次のシーンの準備 */
//	switch (GameScene)
//	{
//	case SCENE_TITLE:
//		// タイトルシーンの初期化
//		InitTitle();
//
//		break;
//
//	case SCENE_GAME:
//		// ゲームシーンの初期化
//		InitGame();
//
//		break;
//
//	case SCENE_RESULT:
//		// リザルトシーンの初期化
//		InitResult();
//
//		break;
//
//	default:
//		return GameScene;
//		break;
//	}
//
//	return GameScene;
//}


