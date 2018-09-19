//=============================================================================
//
// �t�F�[�h���� <Fade.cpp>
//
//=============================================================================
#include "Fade.h"
#include "Common.h"
#include "Direct3D.h"

/* �}�N����` */
#define	FADE_RATE		(0.1f)		// �t�F�[�h�W��


/* �O���[�o���ϐ� */
VERTEX_2D	CSFade::Vertex[RECT_NUM_VERTEX];
D3DXCOLOR	CSFade::Color     = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//GAMESCENE	CSFade::GameScene = SCENE_MAX;
FADE		CSFade::Fade      = FADE_IN;
float		CSFade::Speed     = FADE_RATE;

//----�X�V--------
void CSFade::Update(void)
{
	if(Fade != FADE_NONE)
	{// �t�F�[�h������
		if(Fade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			Color.a += Speed;		// ���l�����Z���ĉ�ʂ������Ă���
			if(Color.a > 1.1f)
			{
				// ���[�h��ݒ�
//				SetGameScene(GameScene);

				// �t�F�[�h�C�������ɐ؂�ւ�
				Color.a = 1.0f;
//				SetFade(FADE_IN, SCENE_MAX, Speed);
			}

			// �F��ݒ�
			SetColor();
		}
		else if(Fade == FADE_IN)
		{// �t�F�[�h�C������
			Color.a -= Speed;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if(Color.a < 0.0f)
			{
				// �t�F�[�h�����I��
				Color.a = 0.0f;
//				SetFade(FADE_NONE, SCENE_MAX, Speed);
			}

			// �F��ݒ�
			SetColor();
		}
	}
}

//----�`��--------
void CSFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//----���_�쐬--------
void CSFade::MakeVertex(void)
{
	// ���_���W�̐ݒ�
	Vertex[0].coord = Vector3(        0.0f,          0.0f, 0.0f);
	Vertex[1].coord = Vector3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].coord = Vector3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].coord = Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;

	// �e�N�X�`�����W�̐ݒ�
	Vertex[0].uv = Vector2(0.0f, 0.0f);
	Vertex[1].uv = Vector2(1.0f, 0.0f);
	Vertex[2].uv = Vector2(0.0f, 1.0f);
	Vertex[3].uv = Vector2(1.0f, 1.0f);
}

//----�F��ݒ�--------
void CSFade::SetColor(D3DCOLOR col)
{
	Color = col;
}
void CSFade::SetColor(void)
{
	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//----�t�F�[�h�̐ݒ�--------
void CSFade::SetFade(float spd)
{
	Fade = FADE_OUT;
//	GameScene = SCENE_MAX;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(float spd, D3DCOLOR col)
{
	Fade = FADE_OUT;
//	GameScene = SCENE_MAX;
	Speed = spd;
	Color = col;
}
//void CSFade::SetFade(GAMESCENE scene)
//{
//	Fade = FADE_OUT;
//	GameScene = scene;
//	Speed = FADE_RATE;
//	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//}
//void CSFade::SetFade(GAMESCENE scene, float spd)
//{
//	Fade = FADE_OUT;
//	GameScene = scene;
//	Speed = spd;
//	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//}
//void CSFade::SetFade(FADE fade, GAMESCENE scene, float spd)
//{
//	Fade = fade;
//	GameScene = scene;
//	Speed = spd;
//	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//}

//----�t�F�[�h�̏�Ԏ擾--------
FADE CSFade::GetFade(void)
{
	return Fade;
}
