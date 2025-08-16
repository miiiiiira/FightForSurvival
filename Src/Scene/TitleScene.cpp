#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	
}

void TitleScene::Update(void)
{

	if (InputManager::GetInstance().PushStartKey())
	{
		// スタートキーが押されたらゲームシーンへ移る
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{
#ifdef _DEBUG
	DrawString(0, 0, "Title", 0xffffff);
#endif // _DEBUG

}

void TitleScene::Release(void)
{
}
