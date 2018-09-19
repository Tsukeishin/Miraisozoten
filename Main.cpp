//=============================================================================
//
// メイン処理 [main.cpp]
//
//=============================================================================
#include "main.h"
#include "Library/Common.h"
#include "Library/TsuLibSystem.h"
#include "Library/WindowClass.h"
#include "Library/Direct3D.h"
#include "Library/FPSManager.h"
#include "Library/Input.h"
#include "Library/Sound.h"
#include "Library/Fade.h"
#include "Library/Camera.h"
#include "Library/Light.h"
#include "Result.h"
#include "Title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"ShirabeniProject"	// ウインドウのクラス名
#define WINDOW_NAME		"白紅プロジェクト"	// ウインドウのキャプション名


/* ゲーム状態の種類 */
typedef enum
{
	SCENE_TITLE = 0,	// タイトル画面
	SCENE_GAME,			// メインゲーム
	SCENE_RESULT,		// リザルト画面
	SCENE_MAX,
	SCENE_END,	// アプリ終了
} GAMESCENE;


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Init();
void Uninit(void);
void Update(void);
void Draw(void);
GAMESCENE SetGameScene(GAMESCENE scene);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
bool		g_bDispDebug = true;	// デバッグ表示ON/OFF
GAMESCENE	g_GameScene = SCENE_MAX;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// TSUシステムを初期化
	if (FAILED(TsuSystem::Initialize(hInstance)))
		return -1;

	// その他初期化
	if (FAILED(Init()))
		return -1;

	//フレームカウント初期化
	timeBeginPeriod(1);	// 分解能設定
	FPSManager::Init();	// FPS制御

	InitCamera();
	Dx9Light Light;
	//Light.SetLight();
	// ラインティングを無効にする
	//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	/* メッセージループ */
	while (1)
	{
		if (WindowClass::CheckMessage())
			break;

		if (FPSManager::FramerateControl())
		{
			PrintDebugProcess("FPS : %f\n", FPSManager::DisplayFPS(FPS_NORMAL));

			//Update();	// 更新処理
			UpdateCamera(D3DXVECTOR3(0, 0, 0));
			Draw();		// 描画処理
		}
	}

	TsuSystem::Uninitialize();	// TSUシステムを初期化
	Uninit();					// その他終了処理


	timeEndPeriod(1);	// 分解能を戻す

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init()
{
	InitCamera();

	// フェード
	CSFade::MakeVertex();

	// タイトルシーンにセット
	SetGameScene(SCENE_GAME);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	SetGameScene(SCENE_END);

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	if (GetKeyboardTrigger(DIK_F3))
	{// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}

	// 入力の更新処理
	UpdateInput();

	switch (g_GameScene)
	{
	case SCENE_TITLE:

		// タイトルシーンの更新処理
		UpdateTitle();

		break;

	case SCENE_GAME:

		// ゲームシーンの更新
		g_GameScene = SCENE_RESULT;

		break;

	case SCENE_RESULT:

		// リザルトシーンの更新処理
		UpdateResult();

		break;

	default:
		break;
	}

	// フェード処理の更新
	CSFade::Update();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	Direct3D::GetD3DDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(Direct3D::GetD3DDevice()->BeginScene()))
	{
		switch (g_GameScene)
		{
		case SCENE_TITLE:

			// タイトルシーンの描画処理
			DrawTitle();

			break;

		case SCENE_GAME:

			// ゲームシーンの描画処理
			SetCamera();

			break;

		case SCENE_RESULT:

			// リザルトの描画処理
			DrawResult();

			break;

		default:
			break;
		}

		// フェード描画
		CSFade::Draw();

		// デバッグ表示の描画処理
		if (g_bDispDebug)
		{
			DrawDebugProcess();
		}

		// Direct3Dによる描画の終了
		Direct3D::GetD3DDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	Direct3D::GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// ゲームシーンの更新・取得
//=============================================================================
GAMESCENE SetGameScene(GAMESCENE scene)
{
	/* 指定シーンが同じ場合は戻る */
	if (scene == SCENE_MAX)
	{
		return g_GameScene;
	}

	/* 現在のシーンのお片付け */
	switch (g_GameScene)
	{
	case SCENE_TITLE:

		// タイトルシーンの終了処理
		UninitTitle();

		break;

	case SCENE_GAME:

		// ゲームシーンの終了処理 リザルトに統一
		//UninitGame();

		// ポーズシーンの終了処理

		// カットインシーンの終了処理

		break;

	case SCENE_RESULT:

		// リザルトシーンの終了処理
		UninitResult();

		// ゲームシーンの終了処理


		break;

	default:
		break;
	}

	/* 次のシーンの準備 */
	switch (scene)
	{
	case SCENE_TITLE:

		// タイトルシーンの初期化
		InitTitle();

		g_GameScene = SCENE_TITLE;

		break;

	case SCENE_GAME:

		// ゲームシーンの初期化


		g_GameScene = SCENE_GAME;

		break;

	case SCENE_RESULT:

		// リザルトシーンの初期化
		InitResult();

		g_GameScene = SCENE_RESULT;

		break;

	default:
		return g_GameScene;
		break;
	}

	g_GameScene = scene;

	return g_GameScene;
}

