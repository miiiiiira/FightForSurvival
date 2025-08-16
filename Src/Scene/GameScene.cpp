#include <DxLib.h>
#include "../Object/Grid/Grid.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
	grid_ = nullptr;
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// グリッド生成
	grid_ = new Grid();
	grid_->Init();

}

void GameScene::Update(void)
{

	// グリッド更新
	grid_->Update();

}

void GameScene::Draw(void)
{

	// グリッド描画
	grid_->Draw();

#ifdef _DEBUG
	DrawString(0, 0, "GameScene", 0xffffff);
#endif // _DEBUG

}

void GameScene::Release(void)
{

	// グリッドの解放
	if (grid_ != nullptr)
	{
		grid_->Release();
		delete grid_;
		grid_ = nullptr;
	}

}
