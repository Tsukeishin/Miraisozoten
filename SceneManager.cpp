#include "SceneManager.h"
#include "Library\Input.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"


SCENE SceneManager::GameScene = SCENE_MAX;


//----�X�V--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̍X�V
		UpdateTitle();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			Scene::SetScene(SCENE_GAME);
		}
		break;

	case SCENE_GAME:
		// �Q�[���V�[���̍X�V
		UpdateGame();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			Scene::SetScene(SCENE_RESULT);
		}
		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̍X�V
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			Scene::SetScene(SCENE_TITLE);
		}
		break;
	}

	return 0;
}

//----�`��--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̕`�揈��
		DrawTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̕`�揈��
		DrawGame();

		break;

	case SCENE_RESULT:
		// ���U���g�̕`�揈��
		DrawResult();

		break;
	}
}

//----�Q�[���V�[���̍X�V�E�擾--------
SCENE SceneManager::SetScene(SCENE scene)
{
	/* �w��V�[���������ꍇ�͖߂� */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* ���݂̃V�[���̂��Еt�� */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏I��
		UninitTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏I��
		UninitGame();

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏I��
		UninitResult();

		break;
	}

	/* ���̃V�[���̏��� */
	switch (scene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏�����
		InitTitle();

		GameScene = SCENE_TITLE;
		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏�����
		InitGame();

		GameScene = SCENE_GAME;
		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏�����
		InitResult();

		GameScene = SCENE_RESULT;
		break;

	default:
		return GameScene;
		break;
	}

	/* �V�[���̐؂�ւ� */
	GameScene = scene;

	return GameScene;
}


