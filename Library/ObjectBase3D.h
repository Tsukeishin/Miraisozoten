#ifndef __CLASS_3D_OBJECT_BASE_H_INCLUDE__
#define __CLASS_3D_OBJECT_BASE_H_INCLUDE__


#include "Texture.h"
#include "Polygon.h"


#define DRAWSTATE_BILLBOARD     (0x00000001L)
#define DRAWSTATE_OFFLIGHTING   (0x00000002L)
#define DRAWSTATE_OFFALPHATEST  (0x00000004L)


/* 3Dオブジェクト基礎クラス */
class _ObjectBase3D
{
protected:
	Dx9Texture		Texture;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

public:
	_ObjectBase3D();

	virtual int  Init() { return 1; };
	virtual int  Update() { return 1; };
	virtual void Draw() {};
	virtual void Uninit() { this->Release(); };

	virtual void LoadTexture(const char *texture);			// 前テクスチャはクリア(開放あり)
	virtual void LoadTexture(LPDx3DTex9 texture);	// 前テクスチャはリリース(開放なし)
	virtual void Release();
	virtual void ReleaseVertex();
};


/* 3Dポリゴンオブジェクト */
class C3DPolygonObject : public _ObjectBase3D
{
protected:
	Vector3 Position;	// 位置座標
	Vector3 Rotation;	// 回転角度
	Vector2 Size;		// ポリゴンサイズ
	float   Scale;		// サイズ倍率

	int TexPattern_X;		// テクスチャパターン（横）
	int TexPattern_Y;		// テクスチャパターン（縦）
	int AnimeCount;			// アニメーションカウント
	int AnimePattern;		// 現在のアニメーションパターン番号
	int ChangeAnimeTime;	// アニメーション切り替え待時間

	virtual int  MakeVertex(void);

public:
	C3DPolygonObject();

	virtual void Init(float posX, float posY, float posZ, float sizX, float sizY);
	virtual void Init(Vector3 pos, Vector2 size);
	virtual void Init(Vector3 pos, Vector3 rot, Vector2 size);
	virtual void Draw(UINT state = 0x0L, const char* order = "SRT");

	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);
	virtual void LoadObjectStatus(Vector3 pos);
	virtual void LoadObjectStatus(Vector3 pos, Vector3 rot);


	virtual void SetVertex(void);				// 頂点座標設定@頂点位置のみ
	virtual void SetVertex(D3DXCOLOR color);	// 頂点座標設定@頂点色込み
	virtual void SetTexture(int num, int ix, int iy);
};


/* 3D六面体オブジェクト *///*
class C3DCubeObject
{
	Dx9Texture Texture;
	VERTEX_3D  Face[6][4];
	Vector3 Position;	// 位置座標
	Vector3 Rotation;	// 回転角度
	Vector3 Size;		// ポリゴンサイズ

public:
	C3DCubeObject();

	void LoadTexture(const char *texture);
	void Release();

	int  Init(Vector3 pos, Vector3 rot, Vector3 size);
	int  Init(Vector3 pos, Vector3 size);
	int  Init(Vector3 pos, Vector3 rot, float size);
	int  Init(Vector3 pos, float size);

	void Draw();

private:
	int  MakeVertex(void);

};


/* モデル読み込みテスト *///*
class C3DXModel
{
protected:
	LPDIRECT3DTEXTURE9	Texture;	// テクスチャへのポインタ
	LPD3DXMESH			Mesh;		// メッシュ情報へのポインタ
	LPD3DXBUFFER		BuffMat;	// マテリアル情報へのポインタ
	DWORD				NumMat;		// マテリアル情報の数

public:
	Vector3 Position;
	Vector3 Rotation;
	float   Scale;

public:
	C3DXModel();

	int  Init(const char *filePath);
	void Draw();
	void Uninit();

private:

};






#endif // !__CLASS_OBJECT_INCLUDE__

