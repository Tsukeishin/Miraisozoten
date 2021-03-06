//=============================================================================
//
// カメラ処理 [Camera.cpp]
//
//=============================================================================
#include "Camera.h"
#include "Direct3D.h"
#include "Input.h"
#include "DebugProcess.h"

// マクロ定義
#define CtoA_INTERVAL_MAX	(640.0f)	// カメラと注視点間の最大距離
#define CtoA_INTERVAL_MIN	(320.0f)	// カメラと注視点間の最小距離
#define CAMERA_ANGLE		(10)


//----コンストラクタ--------
CCamera::CCamera()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----初期化--------
void CCamera::Init(void)
{
	// カメラの初期化
	Gaze = D3DXVECTOR3(0.0f, 200.0f, 0.0f);

	Interval = CtoA_INTERVAL_MAX;
	Sensitivity = GAZE_MOVE_VALUE;

	Position.x = 0.0f;
	Position.y = 200.0f;
	Position.z = -600.0f;
	//Position += Gaze;

	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(PI / 2, PI / 2, -PI / 2);
//	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);

}

//----前後移動--------
void CCamera::Scaling(float moveRate)
{
	D3DXVECTOR3 gazeVec = Gaze - Position;

	/* 拡大・縮小 */
	gazeVec *= moveRate * 0.001f;
	Gaze += gazeVec;

	Position.x = 0.0f;
	Position.y = 0.0f;
	Position.z = -500.0f;
	Position += Gaze;

	Interval -= moveRate;
}

//----旋回移動--------
void CCamera::Rotation(Vector2 moveRate)
{
	/* カメラ位置 */
	// 移動判定
	if (IsMouseLeftPressed())
	{
		Angle.x -= moveRate.y * Sensitivity;
		Angle.z -= moveRate.x * Sensitivity;
		Angle.y += moveRate.x * Sensitivity;
	}

	/* 移動範囲制限 */
	if (Angle.x > D3DXToRadian(179))
	{
		Angle.x = D3DXToRadian(179);
	}
	if (Angle.x < D3DXToRadian(1))
	{
		Angle.x = D3DXToRadian(1);
	}
	if (Angle.z > D3DX_PI)
	{
		Angle.z -= D3DX_PI * 2.0f;
		Angle.y += D3DX_PI * 2.0f;
	}
	if (Angle.z < -D3DX_PI)
	{
		Angle.z += D3DX_PI * 2.0f;
		Angle.y -= D3DX_PI * 2.0f;
	}

	/* 球体座標へ移動 */
	float sinTheta = sinf(Angle.x);
	Position.x = Interval * sinTheta * cosf(Angle.z);
	Position.y = Interval * cosf(Angle.x);
	Position.z = Interval * sinTheta * sinf(Angle.z);
	// 球体座標の反映
	Position += Gaze;
}

//----追尾--------
void CCamera::Translation(Vector2 moveRate)
{
	/* 十字ベクトル */
	D3DXVECTOR3 LeftVec, FrontVec;
	D3DXVECTOR3 gazeVec = Gaze - Position;
	D3DXVECTOR3 subVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVec3Cross(&LeftVec, &gazeVec, &subVec);
	D3DXVec3Normalize(&LeftVec, &LeftVec);
	D3DXVec3Cross(&FrontVec, &LeftVec, &gazeVec);
	D3DXVec3Normalize(&FrontVec, &FrontVec);
	D3DXVec3Normalize(&gazeVec, &gazeVec);

	/* 視点平行移動 */
	if (IsMouseCenterPressed())
	{
		Gaze += LeftVec *  moveRate.x * CAMERA_MOVE_VALUE;
		Gaze += FrontVec * moveRate.y * CAMERA_MOVE_VALUE;
	}
}

//----取得--------
D3DXVECTOR3 CCamera::GetPosition()
{
	return Position;
}
D3DXVECTOR3 CCamera::GetGazeVector()
{
	return Gaze - Position;
}

//----マトリックス生成--------
void CCamera::CreateMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	/* ビューマトリックス */
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&ViewMatrix);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&ViewMatrix,
		&Position,		// カメラの視点
		&Gaze,			// 視線先
		&UpVector);		// 上方向

						// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);


	/* プロジェクションマトリックス */
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&ProjectionMatrix);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix,
		VIEW_ANGLE,		// ビュー平面の視野角
		VIEW_ASPECT,	// ビュー平面のアスペクト比
		VIEW_NEAR_Z,	// ビュー平面のNearZ値
		VIEW_FAR_Z);	// ビュー平面のFarZ値

						// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

//----マトリックス取得----
D3DXMATRIX CCamera::GetViewMatrix(void)
{
	return this->ViewMatrix;
}

D3DXMATRIX CCamera::GetProjMatrix(void)
{
	return this->ProjectionMatrix;
}


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CCamera GameCamera;

#if _DEBUG
CCamera DebugCamera;
bool DebugCameraFlag = false;
#endif // _DEBUG


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	// ゲームカメラ
	GameCamera.Init();

#if _DEBUG
	// デバックカメラ
	DebugCamera.Init();
#endif // _DEBUG


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(Vector3 target)
{
#if _DEBUG
	if (GetKeyboardTrigger(DIK_C))
	{
		DebugCameraFlag = DebugCameraFlag ? false : true;
	}

	Vector3 MouseMovement = Vector3((float)GetMouseX(), (float)GetMouseY(), (float)GetMouseZ());
	DebugCamera.Translation(Vector2(MouseMovement.x, MouseMovement.y));
	DebugCamera.Scaling(MouseMovement.z);
	DebugCamera.Rotation(Vector2(MouseMovement.x, MouseMovement.y));
#endif // _DEBUG

}

//=============================================================================
// 描画処理
//=============================================================================
void SetCamera(void)
{
#if _DEBUG
	if (DebugCameraFlag)
	{
		// デバックカメラ
		DebugCamera.CreateMatrix();
	}
	else
	{
		// ゲームカメラ
		GameCamera.CreateMatrix();
	}
#else
	// ゲームカメラ
	GameCamera.CreateMatrix();
#endif // _DEBUG

}

//=============================================================================
// ビューマトリックス取得関数
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return GameCamera.GetViewMatrix();
}

D3DXMATRIX GetMtxProj(void)
{
	return GameCamera.GetProjMatrix();
}

#if _DEBUG
CCamera *GetCamera()
{
	return &GameCamera;
}
#endif // _DEBUG

